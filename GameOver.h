/*
 The GameOver class is responsible for rendering the game
 over screen once the player has exhausted all of his/her lives
 The GameOver screen consists of a black background with white
 "Game Over" text
 */

#ifndef GAMEOVER_H
#define GAMEOVER_H

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

class GameOver: public Entity
{

private:
    bool texturesLoaded;

public:
    GameOver(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);
    ~GameOver(){};
    void draw();
};

#endif
