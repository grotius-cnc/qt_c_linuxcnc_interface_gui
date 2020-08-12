#ifndef MODE_JOINT_H
#define MODE_JOINT_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void mode_joint(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TRAJ_MODE_FREE
    c->write(&m);
}

#endif // MODE_JOINT_H
