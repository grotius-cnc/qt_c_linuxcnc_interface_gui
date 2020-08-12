#ifndef STATE_ON_H
#define STATE_ON_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void state_on(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TASK_SET_STATE state;
    state.state=EMC_TASK_STATE_ENUM(EMC_TASK_STATE_ON);
    c->write(&state);
}

#endif // STATE_ON_H
