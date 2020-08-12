#ifndef MESSAGE_STATUS_H
#define MESSAGE_STATUS_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <display/variable.h>

void update_m(){ //function used in display/display.h

    const char *cstr = nmlfile.c_str();
    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", cstr);

    for(int i=0; i<1; i++){
        usleep(100*1000);
        if(!stat->valid()) continue;
        if(stat->peek() != EMC_STAT_TYPE) continue;
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

        EMC_OPERATOR_ERROR e;
        char *x=e.error;

        std::cout<<"error message: "<<x<<std::endl;


    }
}

#endif // MESSAGE_STATUS_H
