#ifndef SET_LUBE_ON_H
#define SET_LUBE_ON_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_lube_on(){
    char value[] = "1";
    char name[] = "halui.lube.on";
    do_setp_cmd(name,value);

    char value1[] = "0";
    char name1[] = "halui.lube.off";
    do_setp_cmd(name1,value1);
}

#endif // SET_LUBE_ON_H
