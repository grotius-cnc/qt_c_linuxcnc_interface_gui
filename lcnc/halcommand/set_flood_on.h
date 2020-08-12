#ifndef SET_FLOOD_ON_H
#define SET_FLOOD_ON_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_flood_on(){
    char value[] = "1";
    char name[] = "halui.flood.on";
    do_setp_cmd(name,value);

    char value1[] = "0";
    char name1[] = "halui.flood.off";
    do_setp_cmd(name1,value1);
}

#endif // SET_FLOOD_ON_H
