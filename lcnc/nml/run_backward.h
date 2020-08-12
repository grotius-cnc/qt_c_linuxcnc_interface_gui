#ifndef RUN_BACKWARD_H
#define RUN_BACKWARD_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void run_backward(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_TASK_PLAN_REVERSE reverse_run;
    c->write(&reverse_run);
}

#endif // RUN_BACKWARD_H
