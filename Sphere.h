/*
 The Sphere class is responsible for rendering enemy objects 
 in the game world. Each of the enemy objects appear as a brightly 
 colored 3D sphere and move towards the player along the Z axis at
 a random speed. If the player's ship comes into contact with 
 a sphere, he/she loses a life.
*/

#ifndef SPHERE_H
#define SPHERE_H

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
#include "Entity.h"

class Sphere : public Entity
{
    private:
        GLfloat speed;
        GLfloat radius; 
        GLfloat colour[3];
    public:
    
        Sphere() : Entity(0.0,0.0,0.0,0.0,0.0,0.0){};
        Sphere(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);
        ~Sphere(){};
    
        void draw();
        void randomize();
        bool collidesWith(Entity *other);
    
        GLfloat getRadius(){return radius;};
};




#endif
