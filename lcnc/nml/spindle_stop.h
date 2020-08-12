#ifndef SPINDLE_STOP_H
#define SPINDLE_STOP_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void spindle_stop(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_SPINDLE_OFF m;
    c->write(&m);
}

#endif // SPINDLE_STOP_H
