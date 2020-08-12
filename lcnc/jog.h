#ifndef JOG_H
#define JOG_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void jog(int axis, double velocity, int jogmode){

    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_JOG_CONT cont;
    cont.joint_or_axis = axis;
    cont.vel = velocity;
    cont.jjogmode = 0; //1=teleop
    c->write(&cont);
}

#endif // JOG_H
