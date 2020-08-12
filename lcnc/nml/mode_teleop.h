#ifndef MODE_TELEOP_H
#define MODE_TELEOP_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void mode_teleop(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    //EMC_TRAJ_SET_TELEOP_ENABLE m;
    //c->write(&m);
}

#endif // MODE_TELEOP_H
