/*
 The Entity class is the base class which includes most of the 
 functionality for entities in the game world. The Ship, 
 Environment and Sphere classes all inherit from this class.
 */

#ifndef ENTITY_H
#define ENTITY_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <iostream>

class Entity
{
    private:
        GLfloat left,right,bottom,top,near,far;
        GLfloat x_pos;
        GLfloat y_pos;
        GLfloat z_pos;
        bool alive;
        GLfloat speed;
        GLfloat previousSpeed;
    public:
    
        Entity(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);
        ~Entity();
    
        GLfloat getLeft() {return left;};
        GLfloat getRight() {return right;};
        GLfloat getBottom() {return bottom;};
        GLfloat getTop() {return top;};
        GLfloat getNear() {return near;};
        GLfloat getFar() {return far;};
    
        GLfloat getX(){return x_pos;};
        GLfloat getY(){return y_pos;};
        GLfloat getZ(){return z_pos;};

        void setX(GLfloat x){x_pos = x;};
        void setY(GLfloat y){y_pos = y;};
        void setZ(GLfloat z){z_pos = z;};    
    
        GLfloat getSpeed() {return speed;}
        void setSpeed(GLfloat s) {speed = s;}
    
        bool isAlive(){return alive;};
        void setAlive(bool a){alive=a;};
    
        virtual void draw(){};
    
        void pause();
        void resume();
};

#endif
