#ifndef UPDATE_STATUS_H
#define UPDATE_STATUS_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <display/variable.h>

void update_status(){ //function used in display/display.h

    const char *cstr = nmlfile.c_str();
    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", cstr);

    for(int i=0; i<1; i++){
        usleep(1);
        if(!stat->valid()) continue;
        if(stat->peek() != EMC_STAT_TYPE) continue;
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

        emcStatus_task_currentLine=emcStatus->task.currentLine;
        emcStatus_task_motionLine=emcStatus->task.motionLine; //current executed gcode line
        emcStatus_task_mode=emcStatus->task.mode;  //1=manual 2=auto 3=mdi
        emcStatus_motion_status=emcStatus->motion.status; //2=auto running


        emcStatus_motion_spindle_speed=emcStatus->motion.spindle->speed; //current rpm
        emcStatus_motion_traj_current_vel_mm_sec=emcStatus->motion.traj.current_vel; //current velocity
        emcStatus_motion_traj_maxVelocity_mm_sec=emcStatus->motion.traj.maxVelocity; //value in units/sec, from ini.

        //so far unused
        emcStatus_motion_spindle_direction=emcStatus->motion.spindle->direction;
        emcStatus_motion_spindle_brake=emcStatus->motion.spindle->brake;
        emcStatus_motion_spindle_increasing=emcStatus->motion.spindle->increasing;
        emcStatus_motion_spindle_enabled=emcStatus->motion.spindle->enabled;
        emcStatus_motion_spindle_homed=emcStatus->motion.spindle->homed;
        emcStatus_motion_spindle_enabled_scale=emcStatus->motion.spindle->spindle_scale;
        //int state = emcStatus->task.state;
        //int emcStatus_lube_level=emcStatus->io.lube.level;
        //int emcStatus_coolant.flood=emcStatus->io.coolant.flood;
        //int emcStatus_auz_estop=emcStatus->io.aux.estop;
        //int emcStatus_mist=emcStatus->io.coolant.mist;
        //int emcStatus_lube=emcStatus->io.lube.on;

        //from file emcsh.cc we get the active gcode and mcode, feedrate and spindlespeed values.
        char string[256];
        int t;
        int code;

        // fill in the active G codes
        task_active_gcodes_string[0] = 0;
        for (t = 1; t < ACTIVE_G_CODES; t++) {
            code = emcStatus->task.activeGCodes[t];
            if (code == -1) {
                continue;
            }
            if (code % 10) {
                sprintf(string, "G%.1f ", (double) code / 10.0);
            } else {
                sprintf(string, "G%d ", code / 10);
            }
            strcat(task_active_gcodes_string, string);
        }

        // fill in the active M codes, settings too
        task_active_mcodes_string[0] = 0;
        for (t = 1; t < ACTIVE_M_CODES; t++) {
            code = emcStatus->task.activeMCodes[t];
            if (code == -1) {
                continue;
            }
            sprintf(string, "M%d ", code);
            strcat(task_active_mcodes_string, string);
        }

        // fill in F and S codes also
        sprintf(string, "F%.0f ", emcStatus->task.activeSettings[1]);
        task_active_fcodes_string[0] = 0;
        strcat(task_active_fcodes_string, string);
        sprintf(string, "S%.0f", fabs(emcStatus->task.activeSettings[2]));
        task_active_scodes_string[0] = 0;
        strcat(task_active_scodes_string, string);

    }
}

#endif // UPDATE_STATUS_H






















