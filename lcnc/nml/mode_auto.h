#ifndef MODE_AUTO_H
#define MODE_AUTO_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void mode_auto(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TASK_SET_MODE m;
    m.mode=EMC_TASK_MODE_AUTO;
    c->write(&m);
}

#endif // MODE_AUTO_H
