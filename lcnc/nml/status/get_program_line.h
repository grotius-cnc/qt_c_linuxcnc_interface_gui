#ifndef GET_PROGRAM_LINE_H
#define GET_PROGRAM_LINE_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <display/variable.h>
#include <stdlib.h> //system

#include <iostream>

void get_program_line(){

    std::string nmlfile="/home/user/linuxcnc/configs/common/linuxcnc.nml";
    const char *cstr = nmlfile.c_str();

    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", cstr);

    for(int i=0; i<1; i++){
        usleep(100);
        if(!stat->valid()) continue;
        if(stat->peek() != EMC_STAT_TYPE) continue;
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

        int programline=emcStatus->motion.line;
        std::cout<<"program line: "<<programline<<std::endl;


    }
}

#endif // GET_PROGRAM_LINE_H
