#include <math.h>
#include <mainwindow.h>
#include <iostream>
#include <display/opengl.h>
#include <display/variable.h>
#include <display/display.h>
#include <keyboard/keyboard.h>
#include <thread>

opengl::opengl(QWidget *parent)
    : QOpenGLWidget(parent)
{
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(10);
}

opengl::~opengl()
{
    //destructor
}

void opengl::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LINE_STIPPLE);
    setMouseTracking(true);
    zf=50;
    zl=-100;
    zr=100;
    zb=-100;
    zt=100;
}

void opengl::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
    aspect=double(w)/double(h);
}

void opengl::paintGL()
{
    //gluPerspective(45,aspect,0,10);
    //gluLookAt(0,0,0,0,0,0,0,1,0);
    //glClearColor(1,1,1,1); //background color white
    glClearColor(0,0,0,1); //background color black
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glOrtho(zl, zr, zb/aspect, zt/aspect, -10000.0, 10000.0);

    display();
}

void opengl::wheelEvent(QWheelEvent *event)
{
    if(zr-zl>5 && zr-zl<10){ //zoom accelerator..
        zf=1;
    } else
        if(zr-zl>=10 && zr-zl<50){
            zf=2;
        } else
            if(zr-zl>=50 && zr-zl<100){
                zf=4;
            } else
                if(zr-zl>=100 && zr-zl<200){
                    zf=10;
                } else
                    if(zr-zl>= 200 && zr-zl<300){
                        zf=25;
                    } else
                        if(zr-zl>= 300 && zr-zl<400){
                            zf=50;
                        } else
                            if(zr-zl>=400 && zr-zl<800){
                                zf=100;
                            } else
                                if(zr-zl>=800 && zr-zl<3000){
                                    zf=200;
                                } else
                                    if(zr-zl>=3000){
                                        zf=1000;
                                    }

    if(event->delta()>0 && zr-zl>5 && zt-zb>5){ //zoom in to mouse direction
        if(xr<=0 && yr>=0){ //quadrant top left
            zl+=zf*(2-(xr*-1));
            zr-=zf*(xr*-1);
            zt-=zf*(2-yr);
            zb+=zf*yr;
        }else if(xr>=0 && yr>=0){ //quadrant top right
            zl+=zf*xr;
            zr-=zf*(2-xr);
            zt-=zf*(2-yr);
            zb+=zf*yr;
        }else if(xr<=0 && yr<=0){ //quadrant bottom left
            zl+=zf*(2-(xr*-1));
            zr-=zf*(xr*-1);
            zt-=zf*(yr*-1);
            zb+=zf*(2-(yr*-1));
        }else if(xr>=0 && yr<=0){ //quadrant bottom right
            zl+=zf*xr;
            zr-=zf*(2-xr);
            zt-=zf*(yr*-1);
            zb+=zf*(2-(yr*-1));
        }
    }
    if(event->delta()<0){ //zoom out
        zl-=zf;
        zr+=zf;
        zt+=zf;
        zb-=zf;
    }
}

void opengl::mouseMoveEvent(QMouseEvent *event)
{
    pxw=this->width();
    aspect=double(this->width())/double(this->height());
    mx = ( (double(event->x())/ double(this->width())) * (zr-zl) ) + zl;
    my = ( ( ( double(this->height()) - double(event->y()) )/ double(this->height())) * ((zt-zb)/aspect) ) + zb/aspect;
    //std::cout<<"mx"<<mx<<std::endl;
    //std::cout<<"my"<<my<<std::endl;

    //zoom procents for the 4 quadrants, used for zoom in mouse direction
    xr = (2.0f * event->x()) / this->width() - 1.0f;
    if(xr>0){xr+=1;} else {xr-=1;}
    yr = (1.0f - (2.0f * event->y()) / this->height())/*/aspect*/;
    if(yr>0){yr+=1;} else {yr-=1;}

    if(event->buttons() == Qt::MiddleButton){
        zl+= mx_snap - mx;
        zr+= mx_snap - mx;
        zt+= my_snap - my;
        zb+= my_snap - my;
    }

    if(event->buttons() == Qt::RightButton){

    }
}

void opengl::mousePressEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton){
        click++;
    }

    if(event->buttons() == Qt::MiddleButton){
        mx_snap=mx;
        my_snap=my;
    }
}

void opengl::keyPressEvent(QKeyEvent *event)
{
    //in the gui, give the opengl widget strong focus
    int_key=event->key();
}

void opengl::keyReleaseEvent(QKeyEvent *event)
{
    int dummy=event->key(); //done to prevent qt message
    dummy=-1;
    int_key=dummy;
}

