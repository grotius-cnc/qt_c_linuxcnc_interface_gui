#ifndef HOME_X_H
#define HOME_X_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void home_x(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    //EMC_TRAJ_SET_MODE x;
    //x.
    //x.mode=EMC_TRAJ_MODE_TELEOP;
    //c->write(&x);

    EMC_JOINT_HOME m;
    m.joint=0; //x
    c->write(&m);
}

#endif // HOME_X_H
