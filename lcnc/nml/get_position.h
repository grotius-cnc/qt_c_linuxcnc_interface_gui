#ifndef GET_POSITION_H
#define GET_POSITION_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

POINT get_position(){
    std::string nmlfile="/home/user/linuxcnc/configs/common/linuxcnc.nml";
    const char *cstr = nmlfile.c_str();
    POINT t;
    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", cstr);

    for(int i=0; i<1; i++){
        usleep(100);
        if(!stat->valid()) continue;
        if(stat->peek() != EMC_STAT_TYPE) continue;
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

        t.x=emcStatus->motion.traj.position.tran.x;
        t.y=emcStatus->motion.traj.position.tran.y;
        t.z=emcStatus->motion.traj.position.tran.z;

        emcStatus_task_currentLine=emcStatus->task.currentLine;
        emcStatus_task_motionLine=emcStatus->task.motionLine;
        emcStatus_task_mode=emcStatus->task.mode;  //1=manual 2=auto 3=mdi
        emcStatus_motion_status=emcStatus->motion.status; //2=auto running

        //std::cout<<"motion status: "<<isrunning<<std::endl;

        //std::string c=emcStatus->task.activeGCodes;
        //int d=emcStatus->task.activeGCodes;




    }
    return t;
}

#endif // GET_POSITION_H
