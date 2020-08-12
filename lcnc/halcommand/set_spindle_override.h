#ifndef SET_SPINDLE_OVERRIDE_H
#define SET_SPINDLE_OVERRIDE_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_spindle_override(int value){
    char sz[32]; //lcnc input is format:U32, this is a int.
    sprintf(sz,"%i",value); //copy int to char container
    char name[] = "halui.spindle.0.override.counts"; //pin to send command to
    do_setp_cmd(name,sz); //call send_command.h
}

#endif // SET_SPINDLE_OVERRIDE_H
