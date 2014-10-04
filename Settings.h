/*
 A small library of functions which are used to perform
 initialisation of the window and lighting
 as well as rendering of text to the screen
 */

#ifndef SETTINGS_H
#define SETTINGS_H

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
#include <string>

void initialiseWindow();
void initialiseLighting(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f);
void renderLives(GLfloat l, GLfloat r, GLfloat t, GLfloat b, GLuint lives);
void renderGameName(GLfloat l, GLfloat r, GLfloat t, GLfloat b);
void renderScore(GLfloat l, GLfloat r, GLfloat t, GLfloat b, GLuint score);


#endif
