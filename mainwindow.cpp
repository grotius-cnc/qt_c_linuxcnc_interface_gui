#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <display/variable.h>
#include <display/opengl.h>
#include <qfiledialog.h>
#include <qstring.h>
#include <cstdlib>

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>

//// nml set commands
#include <lcnc/nml/home_all.h>
#include <lcnc/nml/home_x.h>
#include <lcnc/nml/unhome.h>
#include <lcnc/nml/estop.h>
#include <lcnc/nml/estop_reset.h>
#include <lcnc/nml/state_on.h>
#include <lcnc/nml/state_off.h>
#include <lcnc/nml/jog.h>
#include <lcnc/nml/run_forward.h>
#include <lcnc/nml/run_backward.h>
#include <lcnc/nml/pause.h>
#include <lcnc/nml/resume.h>
#include <lcnc/nml/step.h>
#include <lcnc/nml/stop.h>
#include <lcnc/nml/mode_auto.h>
#include <lcnc/nml/mode_manual.h>
#include <lcnc/nml/mode_mdi.h>

#include <lcnc/nml/mdi.h>
#include <lcnc/nml/maxvel.h>
#include <lcnc/nml/spindle_on.h>
#include <lcnc/nml/spindle_off.h>
#include <lcnc/nml/spindle_stop.h>
#include <lcnc/nml/open_file.h>
#include <lcnc/nml/reload_file.h>
#include <lcnc/nml/enable_adaptive_feed.h>
#include <lcnc/nml/disable_adaptive_feed.h>
#include <lcnc/nml/reset_interpreter.h>
#include <hal/halsection.h>

//// nml get commands
#include <lcnc/nml/status/update_status.h>
#include <lcnc/nml/status/get_message_status.h>

//// halcommand set commands
#include <lcnc/halcommand/set_adaptive_feed.h>
#include <lcnc/halcommand/set_max_velocity.h>
#include <lcnc/halcommand/set_scale_max_velocity.h>
#include <lcnc/halcommand/set_jog_speed.h>
#include <lcnc/halcommand/set_feed_override.h>
#include <lcnc/halcommand/set_rapid_override.h>
#include <lcnc/halcommand/set_spindle_override.h>
#include <lcnc/halcommand/set_lube_on.h>
#include <lcnc/halcommand/set_lube_off.h>
#include <lcnc/halcommand/set_flood_on.h>
#include <lcnc/halcommand/set_flood_off.h>
#include <lcnc/halcommand/set_spindle_increase.h>
#include <lcnc/halcommand/set_spindle_decrease.h>
#include <lcnc/halcommand/set_mode_teleop.h>
#include <lcnc/halcommand/set_mode_joint.h>

//// halcommand get commands
#include <lcnc/halcommand/get_command.h>

//test
//#include <rs274ngc.hh>

int oldline=0;
int init=0;

//setup a stylesheet to colorize buttons and labels later on.
QString grey="background-color: rgb(242, 242, 242)";
QString darkgrey="background-color: rgb(149, 149, 149)";
QString green="background-color: rgb(170, 255, 0);";
QString red="background-color: rgb(242, 0, 0);";
QString orange="background-color: rgb(255, 170, 0)";

//////// START SETUP APP SECTION /////////
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timerId = startTimer(100);

    ui->toolButton_estop->setChecked(true);
    estop();

    ui->pushButton_spindle_cw->setEnabled(0);
    ui->pushButton_spindle_ccw->setEnabled(0);

    //startup sequence, set some parameters.
    hal_connection(); //set some hal memory for this app.
    enable_adaptive_feed(); //set active at nml level, without using mdi command: "M52 P1"

    //set halui max velocity scale to 1, without initialisation the scale is set at 0;
    set_scale_max_velocity(1);
}
//////// END SETUP APP SECTION /////////

MainWindow::~MainWindow() //destructor for closing app
{
    system("exit"); //exit log
    killTimer(timerId);
    delete ui;
}


//////// START POLL EVENT SECTION /////////
void MainWindow::timerEvent(QTimerEvent *)
{
    update_status(); //get the current status via emc nml channel by lcnc/nml/status/update_status.h

    if(emcStatus_motion_traj_maxVelocity_mm_sec>0 && init==0){ //to do once at program startup, but after the first opengl loop, we look if one of the ini values is updated.
        init_once();
        init=1;
    }

    ///update machine e-stop and machine-on status
    //halui.estop.is-activated, bit out. must be off to move.
    bool estop_active=get_bool_command("halui.estop.is-activated");
    if(!estop_active){
        ui->toolButton_estop->setStyleSheet(grey);
    } else {
        ui->toolButton_estop->setStyleSheet(red);
        //reset focus for home xyz button.
        ui->pushButton_home->setStyleSheet(grey);
    }

    bool machine_on=get_bool_command("halui.machine.is-on");
    if(!machine_on){
        ui->toolButton_state->setStyleSheet(grey);
    } else {
        ui->toolButton_state->setStyleSheet(green);
        //if machine is on. give home button focus
        ui->pushButton_home->setStyleSheet(darkgrey);
    }

    get_message_status();
    ui->label_system_message->setText(QString::fromStdString(error_message));

    ///update labels if joints are homed.
    bool x_homed = get_bool_command("joint.0.homed");
    bool y_homed = get_bool_command("joint.1.homed");
    bool z_homed = get_bool_command("joint.2.homed");

    //colorize home labels
    if(!x_homed){
        ui->label_status_homed_x->setStyleSheet(grey);
    } else {
        ui->label_status_homed_x->setStyleSheet(green);
    }
    if(!y_homed){
        ui->label_status_homed_y->setStyleSheet(grey);
    } else {
        ui->label_status_homed_y->setStyleSheet(green);
    }
    if(!z_homed){
        ui->label_status_homed_z->setStyleSheet(grey);
    } else {
        ui->label_status_homed_z->setStyleSheet(green);
    }

    if(x_homed && y_homed && z_homed){
        ui->pushButton_home->setStyleSheet(grey);
        //give open file button focus.
    }

    ///update program status, pause, run
    bool program_running=get_bool_command("halui.program.is-running");
    bool program_paused=get_bool_command("halui.program.is-paused");
    bool program_idle=get_bool_command("halui.program.is-idle");
    if(program_running){
        ui->pushButton_run_forward->setStyleSheet(green);
    } else {ui->pushButton_run_forward->setStyleSheet(grey);}

    if(program_paused){
        ui->pushButton_pause->setStyleSheet(orange);
        //when paused, user has to push resume button. give resume button more focus
        ui->pushButton_resume->setStyleSheet(darkgrey);
    } else {ui->pushButton_pause->setStyleSheet(grey);}

    if(program_idle){
        ui->label_status_program_idle->setStyleSheet(green);
    } else {ui->label_status_program_idle->setStyleSheet(grey);}


    ///set dro
    ui->lineEdit_x_pos->setText(QString::number(toolpos.x,'f',4));
    ui->lineEdit_y_pos->setText(QString::number(toolpos.y,'f',4));
    ui->lineEdit_z_pos->setText(QString::number(toolpos.z,'f',4));

    //set current executed program line number in gcode text editor when program is running.
    if(emcStatus_motion_status==2){ //lcnc program is running

        //colorize old line back into white.
        QTextBlockFormat format_white;
        format_white.setBackground(Qt::white);
        QTextCursor cursor_0(ui->textBrowser_gcode->document()->findBlockByLineNumber(oldline));
        cursor_0.select(QTextCursor::LineUnderCursor);
        cursor_0.setBlockFormat(format_white);

        //highlight current program line
        if(emcStatus_task_motionLine>0){ //don't colorize when homing is active.
            QTextCursor cursor_1(ui->textBrowser_gcode->document()->findBlockByLineNumber(emcStatus_task_motionLine-1));
            QTextBlockFormat format;
            format.setBackground(Qt::lightGray);
            cursor_1.select(QTextCursor::LineUnderCursor);
            cursor_1.setBlockFormat(format);
        }

        //update gui label
        ui->label_program_line_number->setText(QString::number(emcStatus_task_motionLine-1));

        oldline=emcStatus_task_motionLine-1;

        //set cursor a few lines further
        QTextCursor cursor_2(ui->textBrowser_gcode->document()->findBlockByLineNumber(emcStatus_task_motionLine+5));
        ui->textBrowser_gcode->setTextCursor(cursor_2);
    }

    ///update status for current gcode, mcode, feedrate and spindlespeed.
    ui->label_status_active_Gcode->setText(task_active_gcodes_string);
    ui->label_status_active_Mcode->setText(task_active_mcodes_string);
    ui->label_status_active_Fcode->setText(task_active_fcodes_string);
    ui->label_status_active_Scode->setText(task_active_scodes_string);


    ///update spindle speed status
    ui->label_status_spindlespeed->setText("status rpm-power "+ QString::number(emcStatus_motion_spindle_speed));


    ///update current velocity status, lcnc gives a value units/sec. This is mm/sec if ini file is set to mm. We translate this value to mm/min by *60sec.
    ui->label_status_current_velocity->setText("status current velocity [mm/min] "+ QString::number(emcStatus_motion_traj_current_vel_mm_sec*60));


    ///check status mode manual, auto or mdi etc.
    bool mode_is_auto = get_bool_command("halui.mode.is-auto");         //halui.mode.is-auto, bit out
    bool mode_is_joint = get_bool_command("halui.mode.is-joint");       //halui.mode.is-joint, bit out
    bool mode_is_manual = get_bool_command("halui.mode.is-manual");     //halui.mode.is-manual, bit out
    bool mode_is_mdi = get_bool_command("halui.mode.is-mdi");           //halui.mode.is-mdi, bit out
    bool mode_is_teleop = get_bool_command("halui.mode.is-teleop");     //halui.mode.is-teleop, bit out

    if(mode_is_auto){
        ui->pushButton_mode_auto->setStyleSheet(green);
    } else {ui->pushButton_mode_auto->setStyleSheet(grey);}
    if(mode_is_joint){
        ui->pushButton_mode_joint->setStyleSheet(green);
    } else {ui->pushButton_mode_joint->setStyleSheet(grey);}
    if(mode_is_manual){
        ui->pushButton_mode_manual->setStyleSheet(green);
    } else {ui->pushButton_mode_manual->setStyleSheet(grey);}
    if(mode_is_mdi){
        ui->pushButton_mode_mdi->setStyleSheet(green);
    } else {ui->pushButton_mode_mdi->setStyleSheet(grey);}
    if(mode_is_teleop){
        ui->pushButton_mode_teleop->setStyleSheet(green);
    } else {ui->pushButton_mode_teleop->setStyleSheet(grey);}


    ///check spindle status
    bool spindle_cw = get_bool_command("halui.spindle.0.runs-forward");
    bool spindle_ccw = get_bool_command("halui.spindle.0.runs-backward");
    if(spindle_cw){
        ui->pushButton_spindle_cw->setStyleSheet(green);
    } else {ui->pushButton_spindle_cw->setStyleSheet(grey);}
    if(spindle_ccw){
        ui->pushButton_spindle_ccw->setStyleSheet(green);
    } else {ui->pushButton_spindle_ccw->setStyleSheet(grey);}


    ///poll keyboard key events. key events are triggerd in the opengl class.
    if(int_key==16777234){ //left arrow
        on_pushButton_x_min_pressed(); //simulate a screen button if keyboard button is pressed
    }

    if(int_key==16777235){ //top arrow
        on_pushButton_y_plus_pressed();
    }

    if(int_key==16777236){ //right arrow
        on_pushButton_x_plus_pressed();
    }

    if(int_key==16777237){ //down arrow
        on_pushButton_y_min_pressed();
    }

    if(int_key==16777238){ //page up
        on_pushButton_z_plus_pressed();
    }

    if(int_key==16777239){ //page down
        on_pushButton_z_min_pressed();
    }

    if(int_key==16777232){ //home
        //a plus pressed
    }

    if(int_key==16777233){ //end
        //a min pressed
    }

    if(int_key==16777222){ //insert
        //b plus pressed
    }

    if(int_key==16777223){ //delete
        //b min pressed
    }

    if(int_key==-1){
        stop();
        int_key=0; //reset to do nothing.
    }
}


void MainWindow::init_once(){

    //Some ini parameters to show where parameters stands for.
    //[TRAJ] MAX_LINEAIR_VELOCITY :
    //note: MAXV     max: 53.340 units/sec 3200.400 units/min

    //[TRAJ] DEFAULT_LINEAR_VELOCITY :
    //note: LJOG     max: 53.340 units/sec 3200.400 units/min
    //note: LJOG default: 30.480 units/sec 1828.800 units/min

    //initialisation that need to be done after opengl has done the update_status function to retrieve ini file values.

    //set default jog speed from ini file.
    int default_jog_speed=int(get_command("ini.traj_default_velocity"));//in mm/sec
    ui->horizontalScrollBar_jog_speed->setValue(default_jog_speed*60); //to mm/min
    ui->label_jog_speed_value->setText(QString::number(default_jog_speed*60));

    ////here we read in max velocity. We can get the data in multiple ways.
    /// 1 - hal
    /// 2 - emc nml status channel

    //set max velocity speed from ini file.
    int max_velocity=int(get_command("ini.traj_max_velocity"));//in mm/sec
    ui->horizontalScrollBar_max_velocity->setMaximum(max_velocity*60); //to mm/min
    ui->label_max_velocity_value->setText(QString::number(max_velocity*60));

    //set max velocity value from status channel
    //ui->horizontalScrollBar_max_velocity->setMaximum(emcStatus_motion_traj_maxVelocity_mm_sec*60);
    //ui->label_max_velocity_value->setText(QString::number(emcStatus_motion_traj_maxVelocity_mm_sec*60));

    ////get_command is a function in : lcnc/halcommand/get_command.h it returns a float value.
}

//////// END POLL EVENT SECTION /////////

void MainWindow::on_toolButton_estop_toggled(bool checked)
{
    if(checked){
        estop();
        ui->toolButton_state->setChecked(false);
        state_off();
        //here the lube goes off automaticly by lcnc
        ui->pushButton_lube_on_off->setChecked(0);
        //release spindle buttons and disable spindle buttons
        ui->pushButton_spindle_cw->setChecked(0);
        ui->pushButton_spindle_ccw->setChecked(0);
        ui->pushButton_spindle_cw->setEnabled(0);
        ui->pushButton_spindle_ccw->setEnabled(0);

    } else {
        estop_reset();

    }
}

void MainWindow::on_toolButton_state_toggled(bool checked)
{
    if(checked){
        ui->toolButton_estop->setChecked(false);
        estop_reset();
        state_on();
        //here the lube goes on automaticly by lcnc
        ui->pushButton_lube_on_off->setChecked(1);
        //enable spindle buttons
        ui->pushButton_spindle_cw->setEnabled(1);
        ui->pushButton_spindle_ccw->setEnabled(1);
    } else {
        state_off();
        //release spindle buttons and disable spindle buttons
        ui->pushButton_spindle_cw->setChecked(0);
        ui->pushButton_spindle_ccw->setChecked(0);
        ui->pushButton_spindle_cw->setEnabled(0);
        ui->pushButton_spindle_ccw->setEnabled(0);
    }
}

void MainWindow::on_pushButton_home_pressed() //home all
{
    mode_manual();
    home_all();
}

//////// START KEY EVENT SECTION /////////
void MainWindow::on_pushButton_x_min_pressed()
{
    mode_manual();
    jog(0,-ui->horizontalScrollBar_jog_speed->value()/60,0);
}

void MainWindow::on_pushButton_x_min_released()
{
    jog(0,0,0);
}

void MainWindow::on_pushButton_x_plus_pressed()
{
    mode_manual();
    jog(0,ui->horizontalScrollBar_jog_speed->value()/60,0);
}

void MainWindow::on_pushButton_x_plus_released()
{
    jog(0,0,0);
}

void MainWindow::on_pushButton_y_plus_pressed()
{
    mode_manual();
    jog(1,ui->horizontalScrollBar_jog_speed->value()/60,0);
}

void MainWindow::on_pushButton_y_plus_released()
{
    jog(1,0,0);
}

void MainWindow::on_pushButton_y_min_pressed()
{
    mode_manual();
    jog(1,-ui->horizontalScrollBar_jog_speed->value()/60,0);
}

void MainWindow::on_pushButton_y_min_released()
{
    jog(1,0,0);
}

void MainWindow::on_pushButton_z_plus_pressed()
{
    mode_manual();
    jog(2,ui->horizontalScrollBar_jog_speed->value()/60,0);
}

void MainWindow::on_pushButton_z_plus_released()
{
    jog(2,0,0);
}

void MainWindow::on_pushButton_z_min_pressed()
{
    mode_manual();
    jog(2,-ui->horizontalScrollBar_jog_speed->value()/60,0);
}

void MainWindow::on_pushButton_z_min_released()
{
    jog(2,0,0);
}
//////// END KEY EVENT SECTION /////////

//////// START PROGRAM CONTROL SECTION /////////
void MainWindow::on_pushButton_run_forward_pressed()
{
    mode_auto();
    run_forward(ui->lineEdit_run_from_line->text().toInt());
    //reset focus open file button to normal.
    ui->pushButton_open_file->setStyleSheet(grey);
}

void MainWindow::on_pushButton_backward_pressed()
{
    mode_auto();
    run_backward();
}

void MainWindow::on_pushButton_pause_pressed()
{
    pause_();
}

void MainWindow::on_pushButton_resume_pressed()
{
    resume();
    ui->pushButton_resume->setStyleSheet(grey);
}

void MainWindow::on_pushButton_step_pressed()
{
    step();
    //focus resume button.
    ui->pushButton_resume->setStyleSheet(darkgrey);
}

void MainWindow::on_pushButton_stop_pressed()
{
    stop();
}

void MainWindow::on_pushButton_mode_auto_pressed()
{
    mode_auto();
}

void MainWindow::on_pushButton_mode_manual_pressed()
{
    mode_manual();
}

void MainWindow::on_pushButton_mode_mdi_pressed()
{
    mode_mdi();
}

void MainWindow::on_pushButton_mode_joint_pressed()
{
    set_mode_joint();
}

void MainWindow::on_pushButton_mode_teleop_pressed()
{
    set_mode_teleop();
}


void MainWindow::on_pushButton_mdi_go_pressed()
{
    mdi(ui->lineEdit_mdi->text().toStdString());
}

void MainWindow::on_pushButton_open_file_pressed()
{
    std::string gcode_read_in=open_file();
    ui->textBrowser_gcode->clear();
    ui->textBrowser_gcode->setText(QString::fromStdString(gcode_read_in));
    ui->label_gcode_filename->setText(QString::fromStdString("gcode file:"+filename));
}

void MainWindow::on_pushButton_reload_file_pressed()
{
    std::string gcode_read_in=reload_file();
    ui->textBrowser_gcode->clear();
    ui->textBrowser_gcode->setText(QString::fromStdString(gcode_read_in));
    ui->label_gcode_filename->setText(QString::fromStdString("gcode file reloaded:"+filename));
    on_pushButton_clear_toolpath_pressed();
}

void MainWindow::on_pushButton_unhome_pressed()
{
    state_off();
    unhome();
}

void MainWindow::on_pushButton_clear_toolpath_pressed()
{
    toolpath.clear(); //clear screen gui toolpath
}

void MainWindow::on_pushButton_halshow_pressed()
{
    system("halshow &"); //& sign is for not freezing the app if subprogram is loaded
}

//////// END PROGRAM CONTROL SECTION /////////

//////// START SPINDLE SECTION /////////
void MainWindow::on_pushButton_spindle_cw_toggled(bool checked)
{
    int rpm = abs(ui->lineEdit_rpm->text().toInt()); //abs is positive
    if(checked){
        ui->pushButton_spindle_ccw->setChecked(false);
        spindle_on(0,rpm);
    } else {
        spindle_off();
    }
}

void MainWindow::on_pushButton_spindle_ccw_toggled(bool checked)
{
    int rpm_neg = -abs(ui->lineEdit_rpm->text().toInt()); //-abs is negative
    if(checked){
        ui->pushButton_spindle_cw->setChecked(false);
        spindle_on(0,rpm_neg);
    } else {
        spindle_off();
    }
}

void MainWindow::on_pushButton_spindle_decrease_pressed()
{
    set_spindle_decrease(1);
}

void MainWindow::on_pushButton_spindle_decrease_released()
{
    set_spindle_decrease(0);
}


void MainWindow::on_pushButton_spindle_increase_pressed()
{
    set_spindle_increase(1);
}

void MainWindow::on_pushButton_spindle_increase_released()
{
    set_spindle_increase(0);
}


void MainWindow::on_pushButton_spindle_stop_pressed()
{
    spindle_stop();
    ui->pushButton_spindle_cw->setChecked(false);
    ui->pushButton_spindle_ccw->setChecked(false);
}
//////// END SPINDLE SECTION /////////

//////// START IO SECTION /////////
void MainWindow::on_pushButton_flood_on_off_toggled(bool checked)
{
    //flood is not involved by e-stop state or machine state.
    if(checked){
        set_flood_on();
    }
    if(!checked){
        set_flood_off();
    }
}

void MainWindow::on_pushButton_lube_on_off_toggled(bool checked)
{
    if(checked){
        set_lube_on();
    }
    if(!checked){
        set_lube_off();
    }
}

void MainWindow::on_horizontalScrollBar_spindle_override_sliderMoved(int position)
{
    // the max spindle override value is setted in the ini file. lcnc input value is scaled back /10
    // [DISPLAY] MAX_SPINDLE_OVERRIDE = 1.2
    int value=position/10;
    set_spindle_override(value);
    ui->label_spindle_override_value->setText(QString::number(position));
}

void MainWindow::on_horizontalScrollBar_rapid_override_sliderMoved(int position)
{
    set_rapid_override(position);
    ui->label_rapid_override_value->setText(QString::number(position));
}

void MainWindow::on_horizontalScrollBar_feed_override_sliderMoved(int position)
{
    // the max feed override value is set in the ini file. slider value is scaled back /10
    // [DISPLAY] MAX_FEED_OVERRIDE = 1.2
    int value=position/10;
    set_feed_override(value);
    ui->label_feed_override_value->setText(QString::number(value*10));
}

void MainWindow::on_horizontalScrollBar_jog_speed_sliderMoved(int position)
{
    //signal : halui.axis.jog-speed, float in, value mm/min
    float float_position=float(position); //convert int position to float position.
    set_jog_speed(float_position);
    ui->label_jog_speed_value->setText(QString::number(position));
}

void MainWindow::on_horizontalScrollBar_max_velocity_sliderMoved(int position)
{
    set_max_velocity(position);
    ui->label_max_velocity_value->setText(QString::number(position));
}

void MainWindow::on_horizontalScrollBar_adaptive_feed_sliderMoved(int position)
{
    //the adaptive feed value is between -1 and 1, the scrollbar resolution is factor 100.
    float value=float(position)/100;
    set_adaptive_feed(value);
    ui->label_adaptive_feed_value->setText(QString::number(value));
}
//////// END IO SECTION /////////


void MainWindow::on_pushButton_start_debug_pressed()
{


}






















