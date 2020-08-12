#ifndef SET_MODE_TELEOP_H
#define SET_MODE_TELEOP_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_mode_teleop(){
    char value[] = "1";
    char name[] = "halui.mode.teleop";
    do_setp_cmd(name,value);
}

#endif // SET_MODE_TELEOP_H
