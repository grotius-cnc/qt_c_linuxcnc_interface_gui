#ifndef SET_LUBE_OFF_H
#define SET_LUBE_OFF_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_lube_off(){
    char value[] = "0";
    char name[] = "halui.lube.on";
    do_setp_cmd(name,value);

    char value1[] = "1";
    char name1[] = "halui.lube.off";
    do_setp_cmd(name1,value1);
}

#endif // SET_LUBE_OFF_H
