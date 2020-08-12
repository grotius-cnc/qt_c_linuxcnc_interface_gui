#ifndef PAUSE_H
#define PAUSE_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void pause_(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TASK_PLAN_PAUSE pause;
    c->write(&pause);
}

#endif // PAUSE_H
