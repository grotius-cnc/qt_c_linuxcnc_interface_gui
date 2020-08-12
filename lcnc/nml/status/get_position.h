#ifndef GET_POSITION_H
#define GET_POSITION_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <display/variable.h>

#include "nml_oi.hh"            // nmlErrorFormat, NML_ERROR, etc

void get_position(){ //function used in display/display.h

    const char *cstr = nmlfile.c_str();
    RCS_STAT_CHANNEL *stat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", cstr);

    for(int i=0; i<1; i++){
        usleep(1);
        if(!stat->valid()) continue;
        if(stat->peek() != EMC_STAT_TYPE) continue;
        EMC_STAT *emcStatus = static_cast<EMC_STAT*>(stat->get_address());

        toolpos.x=emcStatus->motion.traj.position.tran.x;
        toolpos.y=emcStatus->motion.traj.position.tran.y;
        toolpos.z=emcStatus->motion.traj.position.tran.z;
    }


    RCS_STAT_CHANNEL *stat1 = new RCS_STAT_CHANNEL(emcFormat, "emcError", "xemc", cstr);

    for(int i=0; i<1; i++){
        usleep(1);
        if(!stat1->valid()) continue;
        if(stat1->peek() != EMC_STAT_TYPE) continue;
        NML *emcErrorBuffer = new NML(nmlErrorFormat, "emcError", "xemc", cstr);

        for(int i=0; i<1; i++){
            usleep(1);
            if(!emcErrorBuffer->valid()) continue;
            if(emcErrorBuffer->peek() != EMC_STAT_TYPE) continue;

            NMLTYPE type;

            if (0 == emcErrorBuffer || !emcErrorBuffer->valid()) {
                //return -1;
            }

            switch (type = emcErrorBuffer->read()) {
            case -1:
                    std::cout<<"error reading channel"<<std::endl;
                //return -1;
                break;

            case 0:
                // nothing new
                break;

            case EMC_OPERATOR_ERROR_TYPE:
                std::cout<<"error from grotius c++"<<std::endl;
                break;

            case EMC_OPERATOR_TEXT_TYPE:
                std::cout<<"error from grotius c++"<<std::endl;
                break;

            case EMC_OPERATOR_DISPLAY_TYPE:
                std::cout<<"error from grotius c++"<<std::endl;
                break;

            case NML_ERROR_TYPE:
                std::cout<<"error from grotius c++"<<std::endl;
                break;

            case NML_TEXT_TYPE:
                std::cout<<"error from grotius c++"<<std::endl;
                break;

            case NML_DISPLAY_TYPE:
                std::cout<<"error from grotius c++"<<std::endl;
                break;

            }
        }
    }
}

#endif // GET_POSITION_H
