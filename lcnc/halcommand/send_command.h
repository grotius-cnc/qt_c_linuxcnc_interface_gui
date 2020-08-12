#ifndef SEND_COMMAND_H
#define SEND_COMMAND_H

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

static int set_common(hal_type_t type, void *d_ptr, char *value);

void hal_connection(){
    //somehow we need this at the startup of lcnc, otherwise we get segmentation fault.
    int comp_id = hal_init("QT_C++_Interface");
    hal_comp_name(comp_id);
    hal_malloc(200);
    //int sigml= hal_signal_new("xxx", HAL_FLOAT );
    hal_ready(comp_id);
}

//void hal_command_test(){
//    //to test various hal commands quite easy.
//    char value[] = "12";
//    char name[] = "halui.feed-override.counts";
//    do_setp_cmd(name,value);
//}

int do_sets_cmd(char *name, char *value) ///../linuxcnc/src/hal/utils/halcmd_commands.c
{
    int retval;
    hal_sig_t *sig;
    hal_type_t type;
    void *d_ptr;

    rtapi_print_msg(RTAPI_MSG_DBG, "setting signal '%s'\n", name);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search signal list for name */
    sig = halpr_find_sig_by_name(name);
    if (sig == 0) {
    rtapi_mutex_give(&(hal_data->mutex));
    //halcmd_error("signal '%s' not found\n", name);
    return -EINVAL;
    }
    /* found it - it have a writer? if it is a port we can set its buffer size */
    if ((sig->type != HAL_PORT) && (sig->writers > 0)) {
    rtapi_mutex_give(&(hal_data->mutex));
    //halcmd_error("signal '%s' already has writer(s)\n", name);
    return -EINVAL;
    }
    /* no writer, so we can safely set it */
    type = sig->type;
    d_ptr = SHMPTR(sig->data_ptr);
    retval = set_common(type, d_ptr, value);
    rtapi_mutex_give(&(hal_data->mutex));
    if (retval == 0) {
    /* print success message */
   // halcmd_info("Signal '%s' set to %s\n", name, value);
    } else {
    //halcmd_error("sets failed\n");
    }
    return retval;
}

int do_setp_cmd(char *name, char *value)
{
    int retval;
    hal_param_t *param;
    hal_pin_t *pin;
    hal_type_t type;
    void *d_ptr;

    //halcmd_info("setting parameter '%s' to '%s'\n", name, value);
    /* get mutex before accessing shared data */
    rtapi_mutex_get(&(hal_data->mutex));
    /* search param list for name */
    param = halpr_find_param_by_name(name);
    if (param == 0) {
        pin = halpr_find_pin_by_name(name);
        if(pin == 0) {
            rtapi_mutex_give(&(hal_data->mutex));
            //halcmd_error("parameter or pin '%s' not found\n", name);
            return -EINVAL;
        } else {
            /* found it */
            type = pin->type;
            if(pin->dir == HAL_OUT) {
                rtapi_mutex_give(&(hal_data->mutex));
                //halcmd_error("pin '%s' is not writable\n", name);
                return -EINVAL;
            }
            if(pin->signal != 0) {
                rtapi_mutex_give(&(hal_data->mutex));
                //halcmd_error("pin '%s' is connected to a signal\n", name);
                return -EINVAL;
            }
            // d_ptr = (void*)SHMPTR(pin->dummysig);
            d_ptr = (void*)&pin->dummysig;
        }
    } else {
        /* found it */
        type = param->type;
        /* is it read only? */
        if (param->dir == HAL_RO) {
            rtapi_mutex_give(&(hal_data->mutex));
            //halcmd_error("param '%s' is not writable\n", name);
            return -EINVAL;
        }
        d_ptr = SHMPTR(param->data_ptr);
    }

    retval = set_common(type, d_ptr, value);

    rtapi_mutex_give(&(hal_data->mutex));
    if (retval == 0) {
    /* print success message */
        if(param) {
            //halcmd_info("Parameter '%s' set to %s\n", name, value);
        } else {
            //halcmd_info("Pin '%s' set to %s\n", name, value);
    }
    } else {
    //halcmd_error("setp failed\n");
    }
    return retval;

}

static int set_common(hal_type_t type, void *d_ptr, char *value) {
    // This function assumes that the mutex is held
     int retval = 0;
     double fval;
     long lval;
     unsigned long ulval;
     unsigned uval;
     char *cp = value;

     switch (type) {
     case HAL_BIT:
     if ((strcmp("1", value) == 0) || (strcasecmp("TRUE", value) == 0)) {
         *(hal_bit_t *) (d_ptr) = 1;
     } else if ((strcmp("0", value) == 0)
         || (strcasecmp("FALSE", value)) == 0) {
         *(hal_bit_t *) (d_ptr) = 0;
     } else {
         //halcmd_error("value '%s' invalid for bit\n", value);
         retval = -EINVAL;
     }
     break;
     case HAL_FLOAT:
     fval = strtod ( value, &cp );
     if ((*cp != '\0') && (!isspace(*cp))) {
         /* invalid character(s) in string */
         //halcmd_error("value '%s' invalid for float\n", value);
         retval = -EINVAL;
     } else {
         *((hal_float_t *) (d_ptr)) = fval;
     }
     break;
     case HAL_S32:
     lval = strtol(value, &cp, 0);
     if ((*cp != '\0') && (!isspace(*cp))) {
         /* invalid chars in string */
         //halcmd_error("value '%s' invalid for S32\n", value);
         retval = -EINVAL;
     } else {
         *((hal_s32_t *) (d_ptr)) = lval;
     }
     break;
     case HAL_U32:
     ulval = strtoul(value, &cp, 0);
     if ((*cp != '\0') && (!isspace(*cp))) {
         /* invalid chars in string */
         //halcmd_error("value '%s' invalid for U32\n", value);
         retval = -EINVAL;
     } else {
         *((hal_u32_t *) (d_ptr)) = ulval;
     }
     break;
//     case HAL_PORT:
//         uval = strtoul(value, &cp, 0);
//         if ((*cp != '\0') && (!isspace(*cp))) {
//             //halcmd_error("value '%s' invalid for PORT\n", value);
//             retval = -EINVAL;
//         } //else {
//           //  if((*((hal_port_t*)d_ptr) != 0) && (hal_port_buffer_size(*((hal_port_t*)d_ptr)) > 0)) {
//                 //halcmd_error("port is already allocated with %u bytes.\n", hal_port_buffer_size(*((hal_port_t*)d_ptr)));
//           //      retval = -EINVAL;
//       //  } else {
//             //*((hal_port_t*) (d_ptr)) = hal_port_alloc(uval);
//       //  }
//     }
//     break;
     default:
     /* Shouldn't get here, but just in case... */
     //halcmd_error("bad type %d\n", type);
     retval = -EINVAL;
     }
     return retval;
}

#endif // SEND_COMMAND_H
