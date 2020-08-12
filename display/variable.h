#ifndef VARIABLE_H
#define VARIABLE_H
#include <vector>
#include <string>

extern int click,int_key;
extern double zl,zr,zt,zb,zf,xr,yr,pxw;
extern double mx,my,mz; //mouse cad
extern double mx_snap,my_snap,mz_snap; //mouse cad snap
extern double aspect;
extern double segments;

//lcnc status channel
extern double tx,ty,tz;
extern int emcStatus_task_currentLine;
extern int emcStatus_task_motionLine;
extern int emcStatus_task_mode;
extern int emcStatus_motion_status;
extern int emcStatus_active_gcode_at0;
extern char task_active_gcodes_string[256];
extern char task_active_mcodes_string[256];
extern char task_active_fcodes_string[256];
extern char task_active_scodes_string[256];

extern int emcStatus_motion_spindle_speed;
extern int emcStatus_motion_traj_current_vel_mm_sec;
extern int emcStatus_motion_traj_maxVelocity_mm_sec;

extern int emcStatus_motion_spindle_direction;
extern int emcStatus_motion_spindle_brake;
extern int emcStatus_motion_spindle_increasing;
extern int emcStatus_motion_spindle_enabled;
extern int emcStatus_motion_spindle_homed;
extern int emcStatus_motion_spindle_enabled_scale;

extern std::string error_message;

struct POINT {
    double x=0,y=0,z=0;
};
extern POINT toolpos;

struct OBJECT { //can be line or arc
    std::string type;
    double xs=0,ys=0,zs=0,xe=0,ye=0,ze=0; //xyz start, end
    double xcon=0,ycon=0,zcon=0; //xyz control
    double xc=0,yc=0,zc=0; //center xy
    double d=0; //determinant
    double red=0,green=0,blue=0,alpha=0;
};
extern OBJECT object;
extern std::vector<OBJECT> objects;

extern std::vector<POINT> toolpath;

extern std::string nmlfile;
extern std::string filename;

class variable
{
public:
    variable();
};

#endif // VARIABLE_H
