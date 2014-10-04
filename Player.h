/*
 The Player class keeps track of information about
 the player such as the number of lives remaining, the player's 
 score, the player's high score and whether the player is currently
 alive or dead.
 */

#ifndef PLAYER_H
#define PLAYER_H

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

class Player
{
private:
    GLfloat left,right,bottom,top;
    GLuint lives;
    GLuint score;
    GLuint highScore;
    bool alive;

public:
    Player(GLfloat l,GLfloat r,GLfloat b,GLfloat t);
    ~Player();
    
    GLuint getLives(){return lives;};
    void setLives(GLuint l){lives = l;};
    void loseLife();

    GLuint getScore() {return score;};
    void setScore(GLuint s) {score = s;};
    void incrementScore();
    
    void loadHighScore();
    void saveHighScore(GLuint s);
    
    bool isAlive(){return alive;};
    void setAlive(bool a){alive = a;};
};

#endif
