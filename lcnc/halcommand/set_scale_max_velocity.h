#ifndef SET_SCALE_MAX_VELOCITY_H
#define SET_SCALE_MAX_VELOCITY_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_scale_max_velocity(float value){
    char sz1[101]; //lcnc input is format:float
    sprintf(sz1,"%G",value); //copy float value to char container
    char name[] = "halui.max-velocity.scale"; //the pin to send the message to
    do_setp_cmd(name,sz1); //cal send_command.h
}

#endif // SET_SCALE_MAX_VELOCITY_H
