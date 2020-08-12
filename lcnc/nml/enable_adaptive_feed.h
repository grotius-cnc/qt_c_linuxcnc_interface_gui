#ifndef ENABLE_ADAPTIVE_FEED_H
#define ENABLE_ADAPTIVE_FEED_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>
#include<stdlib.h> //system

void enable_adaptive_feed(){

    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);
    EMC_TASK_SET_STATE state;
    state.state=EMC_TASK_STATE_ENUM(EMC_TASK_STATE_ESTOP);
    c->write(&state);

    EMC_MOTION_ADAPTIVE m;
    m.status=1;
    c->write(&m);
}

#endif // ENABLE_ADAPTIVE_FEED_H
