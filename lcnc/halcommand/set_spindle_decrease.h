#ifndef SET_SPINDLE_DECREASE_H
#define SET_SPINDLE_DECREASE_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_spindle_decrease(int value){
    char sz[32]; //lcnc input is format:U32, this is a int.
    sprintf(sz,"%i",value); //convert value to char.
    char name[] = "halui.spindle.0.decrease";
    do_setp_cmd(name,sz);
}

#endif // SET_SPINDLE_DECREASE_H
