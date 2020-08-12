#ifndef SET_FEED_OVERRIDE_H
#define SET_FEED_OVERRIDE_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_feed_override(int value){
    char sz[32]; //lcnc input is format:U32, this is a int.
    sprintf(sz,"%i",value); //convert value to char.
    char name[] = "halui.feed-override.counts";
    do_setp_cmd(name,sz);
}

#endif // SET_FEED_OVERRIDE_H
