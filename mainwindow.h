#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void init_once();

private slots:

    void on_toolButton_estop_toggled(bool checked);

    void on_toolButton_state_toggled(bool checked);

    void on_pushButton_home_pressed();

    void on_pushButton_x_min_pressed();

    void on_pushButton_x_plus_pressed();

    void on_pushButton_x_min_released();

    void on_pushButton_x_plus_released();

    void on_pushButton_y_plus_pressed();

    void on_pushButton_y_plus_released();

    void on_pushButton_y_min_pressed();

    void on_pushButton_y_min_released();

    void on_pushButton_z_plus_pressed();

    void on_pushButton_z_plus_released();

    void on_pushButton_z_min_pressed();

    void on_pushButton_z_min_released();

    void on_pushButton_run_forward_pressed();

    void on_pushButton_backward_pressed();

    void on_pushButton_pause_pressed();

    void on_pushButton_resume_pressed();

    void on_pushButton_step_pressed();

    void on_pushButton_stop_pressed();

    void on_pushButton_mode_auto_pressed();

    void on_pushButton_mode_manual_pressed();

    void on_pushButton_mode_mdi_pressed();

    void on_pushButton_mdi_go_pressed();

    void on_pushButton_spindle_ccw_toggled(bool checked);

    void on_pushButton_spindle_cw_toggled(bool checked);

    void on_pushButton_open_file_pressed();

    void on_pushButton_unhome_pressed();

    void on_pushButton_spindle_stop_pressed();

    void on_pushButton_clear_toolpath_pressed();

    void on_pushButton_halshow_pressed();

    void on_pushButton_flood_on_off_toggled(bool checked);

    void on_pushButton_lube_on_off_toggled(bool checked);

    void on_horizontalScrollBar_rapid_override_sliderMoved(int position);

    void on_horizontalScrollBar_spindle_override_sliderMoved(int position);

    void on_horizontalScrollBar_feed_override_sliderMoved(int position);

    void on_horizontalScrollBar_jog_speed_sliderMoved(int position);

    void on_horizontalScrollBar_max_velocity_sliderMoved(int position);

    void on_horizontalScrollBar_adaptive_feed_sliderMoved(int position);

    void on_pushButton_spindle_decrease_pressed();

    void on_pushButton_spindle_increase_pressed();

    void on_pushButton_spindle_decrease_released();

    void on_pushButton_spindle_increase_released();

    void on_pushButton_mode_joint_pressed();

    void on_pushButton_mode_teleop_pressed();

    void on_pushButton_reload_file_pressed();

    void on_pushButton_start_debug_pressed();

private:
    Ui::MainWindow *ui;
     int timerId;

protected:

    void timerEvent(QTimerEvent *);

};
#endif // MAINWINDOW_H
