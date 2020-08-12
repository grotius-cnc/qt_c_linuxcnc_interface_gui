#ifndef PARSE_GCODE_H
#define PARSE_GCODE_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <string.h>
#include <display/variable.h>

std::vector<std::string> split_line(std::string str);

void parse_gcode(std::vector<std::string> gcode){

    //gcode letters
    std::string g0="G0"; //rapid
    std::string g1="G1"; //lineair
    std::string g2="G2"; //cw
    std::string g3="G3"; //ccw

    //axis letters
    std::string x="X";
    std::string y="Y";
    std::string z="Z";
    std::string sci="I";
    std::string scj="J";
    double dci=0,dcj=0;

    //various letters
    std::string f="f";

    object.type="g0";
    object.d=0;
    object.xs=toolpos.x; //view rapid line from current toolpos to startpos.
    object.ys=toolpos.y;
    object.zs=toolpos.z;
    object.xe=toolpos.x;
    object.ye=toolpos.y;
    object.ze=toolpos.z;
    object.xc=0;
    object.yc=0;
    object.zc=0;
    object.xcon=0;
    object.ycon=0;
    object.zcon=0;
    objects.push_back(object);

    for(unsigned int i=0; i<gcode.size(); i++){

        //std::cout<<"gcode line : "<<gcode.at(i)<<std::endl;

        std::vector<std::string> result=split_line(gcode.at(i));
        for (auto str : result){

            if(str.find(g0) != std::string::npos){
                object.type="g0";
                object.d=0;
                object.red=0;
                object.green=0;
                object.blue=255;
                object.alpha=255;
            }

            if(str.find(g1) != std::string::npos){
                object.type="g1";
                object.d=0;
                object.red=0;
                object.green=255;
                object.blue=0;
                object.alpha=255;
            }

            if(str.find(g2) != std::string::npos){
                object.type="g2";
                object.d=1;
                object.red=0;
                object.green=255;
                object.blue=0;
                object.alpha=255;
            }

            if(str.find(g3) != std::string::npos){
                object.type="g3";
                object.d=-1;
                object.red=0;
                object.green=255;
                object.blue=0;
                object.alpha=255;
            }

            if(str.find(x) != std::string::npos){
                object.xs=objects.back().xe;
                object.xe=std::stod(str.assign(str.begin()+1,str.end()));
            }
            if(str.find(y) != std::string::npos){
                object.ys=objects.back().ye;
                object.ye=std::stod(str.assign(str.begin()+1,str.end()));
            }
            if(str.find(z) != std::string::npos){
                object.xs=objects.back().xe;
                object.ys=objects.back().ye;
                object.zs=objects.back().ze;
                object.ze=std::stod(str.assign(str.begin()+1,str.end()));
            }
            if(str.find(sci) != std::string::npos){
                dci=std::stod(str.assign(str.begin()+1,str.end()));
                object.xc=dci+object.xs; std::cout<<"center_x: "<<object.xc<<std::endl;
            }
            if(str.find(scj) != std::string::npos){
                dcj=std::stod(str.assign(str.begin()+1,str.end()));
                object.yc=dcj+object.ys; std::cout<<"center_y: "<<object.yc<<std::endl;
            }
        }

        if(object.type=="g0" || object.type=="g1" || object.type=="g2" || object.type=="g3"){
            objects.push_back(object);
        }
    }

}

std::vector<std::string> split_line(std::string string)
{
    std::string word = "";
    std::vector<std::string> str;
    for (auto x : string){
        if (x == ' '){
            //std::cout << word << std::endl;
            str.push_back(word);
            word = "";
        }
        else {
            word = word + x;
        }
    }
    //std::cout << word << std::endl;
    str.push_back(word);
    return str;
}

#endif // PARSE_GCODE_H
