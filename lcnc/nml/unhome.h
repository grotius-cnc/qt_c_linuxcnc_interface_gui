#ifndef UNHOME_H
#define UNHOME_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>

void unhome(){
    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_JOINT_UNHOME m;
    m.joint=0; //x
    c->write(&m);

    m.joint=1; //y
    c->write(&m);

    m.joint=2; //z
    c->write(&m);
}

#endif // UNHOME_H
