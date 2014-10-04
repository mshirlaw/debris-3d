/*
 The PPMImageIO library includes a helper function which is 
 used to load a PPM image for use as a texture 
*/

#ifndef PPMIMAGEIO_H
#define PPMIMAGEIO_H

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <string>
#include <fstream>
#include <iostream>

using namespace std;
bool PPMReader(char* filename, int& height, int& width, GLubyte*& pixels);

#endif
