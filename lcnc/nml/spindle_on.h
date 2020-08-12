#ifndef SPINDLE_ON_H
#define SPINDLE_ON_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void spindle_on(int direction, double rpm){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_SPINDLE_ON m;
    m.speed=rpm;
    m.spindle=direction;
    c->write(&m);
}

#endif // SPINDLE_ON_H
