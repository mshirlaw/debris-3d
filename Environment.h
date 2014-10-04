/*
 The Environment class is responsible for rendering the 
 walls, floor, roof and back wall in the game world. 
 The Environment class also loads and sets textures for the walls, floor and
 sky to give the game world a 3D appearance
 */

#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

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
#include "PPMImageIO.h"

class Environment : public Entity
{
    private:
        bool texturesLoaded;
    public:
        Environment(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);
        void draw();
        bool collidesWith(Entity *other);
};

#endif
