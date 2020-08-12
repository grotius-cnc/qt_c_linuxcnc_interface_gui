#ifndef ERROR_MESSAGE_H
#define ERROR_MESSAGE_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <display/variable.h>

#include <rcs_print.hh>
#include "linklist.hh"


void error_message(){ ///for more into look at../linuxcnc/include/emc_nml.hh

//    const char *cstr = nmlfile.c_str();
//    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", cstr);

//    for(int i=0; i<1; i++){
//        usleep(1);
//        if(!stat->valid()) continue;
//        if(stat->peek() != EMC_STAT_TYPE) continue;
//        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

//        //problably this is not working at the moment :



//        EMC_OPERATOR_ERROR e;
//        char *error=e.error;

//        EMC_OPERATOR_TEXT t;
//        char *text=t.text;

//        EMC_OPERATOR_DISPLAY d;
//        char *display=d.display;

//        std::vector<std::string> str;
//        str.push_back(error);
//        str.push_back(text);
//        str.push_back(display);

//        return str;
//    }




}

void hal_command_test(){


}

#endif // ERROR_MESSAGE_H










