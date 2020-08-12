#ifndef SET_MAX_VELOCITY_H
#define SET_MAX_VELOCITY_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_max_velocity(int value){
    char sz[32]; //lcnc input is format:U32, this is a int.
    sprintf(sz,"%i",value/60); //convert value to char, convert units from mm/min to mm/sec lcnc input
    char name1[] = "halui.max-velocity.counts"; //lcnc pin to sent message to
    do_setp_cmd(name1,sz); //call send_command.h
}

#endif // SET_MAX_VELOCITY_H
