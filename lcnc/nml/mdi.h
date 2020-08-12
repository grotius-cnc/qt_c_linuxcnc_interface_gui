#ifndef MDI_H
#define MDI_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <string.h>
#include <display/variable.h>

void mdi(std::string mdi_command){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    //set mode mdi
    EMC_TASK_SET_MODE m;
    m.mode=EMC_TASK_MODE_MDI;
    c->write(&m);

    //write mdi
    std::cout<<"mdi command: "<<mdi_command<<std::endl;
    EMC_TASK_PLAN_EXECUTE mdi;

    const char *chars = mdi_command.c_str();
    strcpy(mdi.command, chars);
    c->write(&mdi);
}

#endif // MDI_H
