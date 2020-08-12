#ifndef SET_MODE_JOINT_H
#define SET_MODE_JOINT_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_mode_joint(){
    char value[] = "1";
    char name[] = "halui.mode.joint";
    do_setp_cmd(name,value);
}

#endif // SET_MODE_JOINT_H
