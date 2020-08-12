#ifndef SET_RAPID_OVERRIDE_H
#define SET_RAPID_OVERRIDE_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_rapid_override(int value){
    char sz[32]; //lcnc input is format:U32, this is a int.
    sprintf(sz,"%i",value); //copy int to char container
    char name[] = "halui.rapid-override.counts"; //pin to send command to
    do_setp_cmd(name,sz); //call send_command.h
}

#endif // SET_RAPID_OVERRIDE_H
