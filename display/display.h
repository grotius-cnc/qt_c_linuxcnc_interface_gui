#ifndef DISPLAY_H
#define DISPLAY_H
#include <display/variable.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <lcnc/nml/status/get_position.h>
#include <math.h>

bool trigger=0;
double dist=0;
POINT p={0,0,0};
void preview_toolpath();
void preview_parsed_gcode();
void draw_arc(int i);

void display(){

    //show current tool position
    get_position(); //get the tool coordinates etc.

    glLineWidth(1);
    glColor4d(255,0,0,255);
    glBegin(GL_LINES);
    glVertex3d(-5+toolpos.x,toolpos.y,toolpos.z);
    glVertex3d(5+toolpos.x,toolpos.y,toolpos.z);
    glVertex3d(toolpos.x,5+toolpos.y,toolpos.z);
    glVertex3d(toolpos.x,-5+toolpos.y,toolpos.z);
    glEnd();

    dist=sqrt(pow(toolpos.x-p.x,2)+pow(toolpos.y-p.y,2));
    //std::cout<<"dist: "<<dist<<std::endl;

    //mark toolpath
    if(!trigger){
        p=toolpos;
        trigger=1;
    }

    if(dist>0.01){
        if(toolpath.size()>1000000){
            toolpath.clear();
        }
        toolpath.push_back({toolpos.x,toolpos.y,toolpos.z});
        //std::cout<<"toolpath pushed back"<<std::endl;
        dist=0;
        trigger=0;
    }
    glLineWidth(4);
    glColor3f(1.0f,0.1f,0.0f); //color of toolpath
    glBegin(GL_LINE_STRIP);
    for(unsigned int i=0; i<toolpath.size(); i++){
        glVertex3d(toolpath.at(i).x,toolpath.at(i).y,toolpath.at(i).z);
    }
    glEnd();


    //parsed gcode
    for(unsigned int i=0; i<objects.size(); i++){

        if(objects.at(i).type=="g0" || objects.at(i).type=="g1"){
            glLineWidth(1);
            glBegin(GL_LINES);
            glLineWidth(1);
            glColor4d(objects.at(i).red,objects.at(i).green,objects.at(i).blue,objects.at(i).alpha);
            glVertex3d(objects.at(i).xs,objects.at(i).ys,objects.at(i).zs);
            glVertex3d(objects.at(i).xe,objects.at(i).ye,objects.at(i).ze);
            glEnd();
        }

        if(objects.at(i).type=="g2" || objects.at(i).type=="g3"){
            draw_arc(i);
        }
    }
}

void draw_arc(int i){

    double xs=objects.at(i).xs;
    double ys=objects.at(i).ys;
    double xe=objects.at(i).xe;
    double ye=objects.at(i).ye;

    double x_center = objects.at(i).xc;
    double y_center = objects.at(i).yc;
    double dx = x_center - objects.at(i).xs;
    double dy = y_center - objects.at(i).ys;
    double radius = sqrt(dx * dx + dy * dy);
    double deg_angle_start=0, deg_angle_end=0;

    if(objects.at(i).d>0){
        deg_angle_start = 180/M_PI*atan2(ye-y_center, xe-x_center);    //start angle G2
        deg_angle_end = 180/M_PI*atan2(ys-y_center, xs-x_center);    //end angle G2
    }
    if(objects.at(i).d<0){
        deg_angle_start = 180/M_PI*atan2(ys-y_center, xs-x_center);    //start angle G3
        deg_angle_end  = 180/M_PI*atan2(ye-y_center, xe-x_center);    //end angle G3
    }

    //draw arc..
    double pi_angle_start = (deg_angle_start/360)*(2*M_PI); //start angle
    //if(end_angle==360)
    //{
    //    end_angle=0;   //autocad degree problem..
    //}
    double pi_angle_end = (deg_angle_end/360)*(2*M_PI);
    if (pi_angle_end<pi_angle_start)   //this to avoid the start angle is bigger then the end angle value
    {
        pi_angle_end+=2*M_PI;
    }

    double pi_arc_angle = pi_angle_end - pi_angle_start;
    double theta = pi_arc_angle / double(segments - 1);//theta is now calculated from the arc angle instead, the - 1 bit comes from the fact that the arc is open
    double tangetial_factor = tan(theta);
    double radial_factor = cos(theta);
    double x = radius * cos(pi_angle_start);//we now start at the start angle
    double y = radius * sin(pi_angle_start);

    glLineWidth(1);
    glColor4d(objects.at(i).red,objects.at(i).green,objects.at(i).blue,objects.at(i).alpha);
    glBegin(GL_LINE_STRIP);//since the arc is not a closed curve, this is a strip now
    for(int ii = 0; ii < segments; ii++)
    {
        glVertex2d(x + x_center, y + y_center); //x center, y center..

        double tx = -y;
        double ty = x;

        x += tx * tangetial_factor;
        y += ty * tangetial_factor;

        x *= radial_factor;
        y *= radial_factor;
    }
    glEnd();
}

#endif // DISPLAY_H































