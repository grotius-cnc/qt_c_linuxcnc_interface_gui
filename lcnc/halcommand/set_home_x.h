#ifndef SET_HOME_X_H
#define SET_HOME_X_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_home_x(){
    char value[] = "1";
    char name[] = "halui.joint.0.home";
    do_setp_cmd(name,value);
}

#endif // SET_HOME_X_H
