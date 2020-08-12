#ifndef SET_ADAPTIVE_FEED_H
#define SET_ADAPTIVE_FEED_H

#include <iostream>
#include <lcnc/halcommand/send_command.h>

void set_adaptive_feed(float value){ //value = -1 to 1
    char sz[101]; //101 data places is for float value
    sprintf(sz,"%G",value); //copy float value to char container
    char name[] = "motion.adaptive-feed"; //name of halui pin
    do_setp_cmd(name,sz); //cal send_command.h
}

#endif // SET_ADAPTIVE_FEED_H
