#ifndef MODE_MDI_H
#define MODE_MDI_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void mode_mdi(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TASK_SET_MODE m;
    m.mode=EMC_TASK_MODE_MDI;
    c->write(&m);
}

#endif // MODE_MDI_H
