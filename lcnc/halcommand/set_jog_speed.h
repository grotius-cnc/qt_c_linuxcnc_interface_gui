#ifndef SET_JOG_SPEED_H
#define SET_JOG_SPEED_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_jog_speed(float value){
    char sz[101]; //101 char data places is a float
    sprintf(sz,"%G",value); //copy float value into char container
    char name[] = "halui.jog-speed"; //pin to send command to
    do_setp_cmd(name,sz); //call send_command.h
}

#endif // SET_JOG_SPEED_H
