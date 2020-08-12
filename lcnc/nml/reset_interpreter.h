#ifndef RESET_INTEPRETER_H
#define RESET_INTEPRETER_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void reset_interpreter(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_TASK_PLAN_INIT m;
    c->write(&m);
}

#endif // RESET_INTEPRETER_H
