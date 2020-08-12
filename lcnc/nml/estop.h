#ifndef ESTOP_H
#define ESTOP_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void estop(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TASK_SET_STATE state;
    state.state=EMC_TASK_STATE_ENUM(EMC_TASK_STATE_ESTOP);
    c->write(&state);
}

#endif // ESTOP_H
