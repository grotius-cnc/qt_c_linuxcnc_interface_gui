#ifndef RUN_H
#define RUN_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void run_forward(int linenumber){ //not working yet
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    //EMC_TASK_PLAN_FORWARD

    EMC_TASK_PLAN_RUN run;
    run.line=linenumber;

    c->write(&run);
}

#endif // RUN_H
