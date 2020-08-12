#ifndef SET_FLOOD_OFF_H
#define SET_FLOOD_OFF_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_flood_off(){
    char value[] = "0";
    char name[] = "halui.flood.on";
    do_setp_cmd(name,value);

    char value1[] = "1";
    char name1[] = "halui.flood.off";
    do_setp_cmd(name1,value1);
}

#endif // SET_FLOOD_OFF_H
