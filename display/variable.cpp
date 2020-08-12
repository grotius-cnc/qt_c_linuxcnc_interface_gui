#include <string>
#include <vector>
#include <iostream>
#include <display/variable.h>

int click,int_key=0;
double zl,zr,zt,zb,zf,xr,yr,pxw;
double mx,my,mz; //mouse cad
double mx_snap,my_snap,mz_snap; //mouse cad snap
double aspect;
double segments=25;

//lcnc status channel
double tx,ty,tz;
int emcStatus_task_currentLine;
int emcStatus_task_motionLine;
int emcStatus_task_mode;
int emcStatus_motion_status;
int emcStatus_active_gcode_at0;
char task_active_gcodes_string[256];
char task_active_mcodes_string[256];
char task_active_fcodes_string[256];
char task_active_scodes_string[256];

int emcStatus_motion_spindle_speed;
int emcStatus_motion_traj_current_vel_mm_sec;
int emcStatus_motion_traj_maxVelocity_mm_sec;

int emcStatus_motion_spindle_direction;
int emcStatus_motion_spindle_brake;
int emcStatus_motion_spindle_increasing;
int emcStatus_motion_spindle_enabled;
int emcStatus_motion_spindle_homed;
int emcStatus_motion_spindle_enabled_scale;

std::string error_message;


POINT toolpos;
OBJECT object;
std::vector<OBJECT> objects;

std::vector<POINT> toolpath;

std::string nmlfile="/home/user/linuxcnc/configs/common/linuxcnc.nml";
std::string filename; //gcode program filename

variable::variable()
{

}
