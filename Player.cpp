#include "Player.h"


Player::Player(GLfloat l,GLfloat r,GLfloat b,GLfloat t) : left(l),right(r),bottom(b),top(t)
{
    score = 0;
    lives = 3;
    alive = true;
}

Player::~Player()
{

}

void Player::loseLife()
{
    //if the player is still alive - take off one life
    if(isAlive())
    {
        if(lives>0)
            lives--;
        else
        {
            alive=false;
            std::cout << "You are dead!" << std::endl;
        }
    }
}


void Player::incrementScore()
{
    score++;
}

//TODO - read a high score from file
void Player::loadHighScore()
{
    
}

//TODO - write a high score to file 
void Player::saveHighScore(GLuint s)
{

}