#ifndef GET_COMMAND_H
#define GET_COMMAND_H

// For user space HAL RTAPI
#ifdef RTAPI
#undef RTAPI
#endif
#ifndef ULAPI
#define ULAPI
#endif

#include <iostream>
#include <display/variable.h>
#include <QString>

#include <emc.hh>
#include <emc_nml.hh>

#include "hal.h"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "rtapi_string.h"
#include "rtapi_errno.h"

#include "config.h"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "hal.h"            /* HAL public API decls */
#include <rtapi_mutex.h>
#include <rtapi_string.h>

#include "config.h"
#include "rtapi.h"          /* RTAPI realtime OS API */
#include "hal.h"            /* HAL public API decls */
#include "../hal_priv.h"	/* private HAL decls */
#include "halcmd_commands.h"
#include <rtapi_mutex.h>
#include <rtapi_string.h>

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>
#include <fnmatch.h>
#include <sys/types.h>
#include <sys/wait.h>

float get_command(std::string name);
static char *data_value2(int type, void *valptr);

//void hal_command_test(){

//    std::string name= "ini.traj_default_velocity";
//    float result=get_command(name);
//    std::cout<<"result: "<<result<<std::endl;
//}

float get_command(std::string name){ ///../linuxcnc/src/hal/utils/halcmd_commands.c

    char text[265];
    sprintf(text,"%s",name.c_str()); //copy float value to char container

    hal_param_t *param;
    hal_pin_t *pin;
    hal_sig_t *sig = nullptr;
    hal_type_t type;
    void *d_ptr;

    rtapi_print_msg(RTAPI_MSG_DBG, "getting parameter '%s'\n", text);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search param list for name */
    param = halpr_find_param_by_name(text);
    if (param) {
        /* found it */
        type = param->type;
        d_ptr = SHMPTR(param->data_ptr);

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);
        std::string str(data);
        float value=std::stof(str);
        return value;
    }

    /* not found, search pin list for name */
    pin = halpr_find_pin_by_name(text);
    if(pin) {
        /* found it */
        type = pin->type;
        if (pin->signal != 0) {
            //sig = SHMPTR(pin->signal);
            d_ptr = SHMPTR(sig->data_ptr);
        } else {
            sig = 0;
            d_ptr = &(pin->dummysig);
        }

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);
        std::string str(data);
        float value=std::stof(str);
        return value;
    }

    rtapi_mutex_give(&(hal_data->mutex));
    //halcmd_error("pin or parameter '%s' not found\n", name);
    //return -EINVAL;
    return -1;
}

bool get_bool_command(std::string name){ ///../linuxcnc/src/hal/utils/halcmd_commands.c

    char text[1];
    sprintf(text,"%s",name.c_str()); //copy float value to char container

    hal_param_t *param;
    hal_pin_t *pin;
    hal_sig_t *sig = nullptr;
    hal_type_t type;
    void *d_ptr;

    rtapi_print_msg(RTAPI_MSG_DBG, "getting parameter '%s'\n", text);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search param list for name */
    param = halpr_find_param_by_name(text);
    if (param) {
        /* found it */
        type = param->type;
        d_ptr = SHMPTR(param->data_ptr);

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);

        if(strcmp(data,"TRUE")!=0){
            return 0;
        } else return 1;
    }

    /* not found, search pin list for name */
    pin = halpr_find_pin_by_name(text);
    if(pin) {
        /* found it */
        type = pin->type;
        if (pin->signal != 0) {
            //sig = SHMPTR(pin->signal);
            d_ptr = SHMPTR(sig->data_ptr);
        } else {
            sig = 0;
            d_ptr = &(pin->dummysig);
        }

        rtapi_mutex_give(&(hal_data->mutex));

        char *data= data_value2((int) type, d_ptr);

        if(strcmp(data,"TRUE")!=0){
            return 0;
        } else return 1;
    }

    rtapi_mutex_give(&(hal_data->mutex));
    //halcmd_error("pin or parameter '%s' not found\n", name);
    //return -EINVAL;
    return -1;
}

/* Switch function to return var value in string form  */
/* the value is printed as a packed string (no whitespace */
static char *data_value2(int type, void *valptr)
{
    char *value_str;
    static char buf[15];

    switch (type) {
    case HAL_BIT:
    if (*((char *) valptr) == 0)
        value_str = "FALSE";
    else
        value_str = "TRUE";
    break;
    case HAL_FLOAT:
    snprintf(buf, 14, "%.7g", (double)*((hal_float_t *) valptr));
    value_str = buf;
    break;
    case HAL_S32:
    snprintf(buf, 14, "%ld", (long)*((hal_s32_t *) valptr));
    value_str = buf;
    break;
    case HAL_U32:
    snprintf(buf, 14, "%ld", (unsigned long)*((hal_u32_t *) valptr));
    value_str = buf;
    break;
//    case HAL_PORT:
//    //snprintf(buf, 14, "%u", hal_port_buffer_size(*((hal_port_t*) valptr)));
//    value_str = buf;
//    break;

    default:
    /* Shouldn't get here, but just in case... */
    value_str = "unknown_type";
    }
    return value_str;
}

#endif // GET_COMMAND_H

























