#ifndef RELOAD_FILE_H
#define RELOAD_FILE_H

#include <emc.hh>
#include <emc_nml.hh>
#include <iostream>
#include <fstream>
#include <string.h>
#include <QFileDialog>
#include <display/variable.h>
#include <gcode/parse_gcode.h>

std::string reload_file(){

    objects.clear();

    const char *char_filename;
    char_filename = filename.c_str(); //filename in orange is already in memory as external variable, so no magic happens over here.

    const char *cstr = nmlfile.c_str();
    RCS_CMD_CHANNEL *c = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", cstr);

    EMC_TASK_SET_MODE a;
    a.mode=EMC_TASK_MODE_AUTO;
    c->write(&a);

    //first close current loaded ngc file
    EMC_TASK_PLAN_CLOSE close;
    c->write(&close);

    //load new ngc file
    EMC_TASK_PLAN_OPEN open;
    strcpy(open.file, char_filename);
    c->write(&open);

    //load file line by line to display in gui preview
    std::string text;
    std::vector<std::string> gcode;
    char count[200];
    FILE *file=fopen(char_filename, "r"); //convert std::string to std::char
    while(file && fgets(count, sizeof(count), file)){
        text+=count;
        gcode.push_back(count);
    }
    fcloseall();
    parse_gcode(gcode);
    return text;
}

#endif // RELOAD_FILE_H
