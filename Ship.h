/*
 The Ship class renders a blue cube to the game world
 which represents the player's ship. The player can move the sphere
 around the game world in an attempt to avoid hitting "debris"
 objects. The Ship class is also responsible for determining 
 whether the player's ship has collided with a sphere in the
 scene.
 */

#ifndef SHIP_H
#define SHIP_H

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
#include <cmath>
#include "Entity.h"
#include "Sphere.h"
#include "PPMImageIO.h"


class Ship : public Entity
{
private:

public:
    Ship(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);
    ~Ship();
    void draw(GLfloat x, GLfloat y, GLfloat z);
    bool collidesWithSphere(Sphere *s);
};

#endif
