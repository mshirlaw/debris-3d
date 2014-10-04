/**********************************************************************************
 
 Debris 3D
 Author: mshirlaw
 COMP323 - Project - Part 2
 
 A simple 3D game which requires the player
 to control a ship within a 3D environment to avoid 
 moving objects. The player has 3 lives and receives points
 as he/she passes objects.
 
 Controls:
 Left arrow - move left
 Right arrow - move right
 Up arrow - move up
 Down arow - move down
 w - move along the -Z axis
 s - move along the + Z axis
 p - pause the game
 r - resume the game
 
***********************************************************************************/

#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#include <GLUT/glut.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#endif

#include <cstdlib>
#include <ctime>
#include <iostream>

#include "Environment.h"
#include "Sphere.h"
#include "Ship.h"
#include "Player.h"
#include "Settings.h"
#include "GameOver.h"

//specify bounds of the gameworld - used for positioning walls and ball
float l = -5.0f, r = 5.0f, b = -5.0f, t = 5.0f, n = -1.0f, f = -25.0f;

//create instnances of the world, enemies, ship, player and GameOver screen
Environment world(l,r,b,t,n,f);
Sphere ball(l,r,b,t,n,f);
Sphere ball2(l,r,b,t,n,f);
Sphere ball3(l,r,b,t,n,f);
Sphere ball4(l,r,b,t,n,f);
Sphere ball5(l,r,b,t,n,f);
Sphere ball6(l,r,b,t,n,f);
Ship playerShip(l,r,b,t,n,f);
Player playerOne(l,r,b,t);
GameOver endScreen(l,r,b,t,n,f);

//an array to store enemies
Sphere enemies[] = {ball,ball2,ball3,ball4,ball5,ball6};


//framerate and clock
const int FRAMES_PER_SEC = 30;
clock_t clock_ticks = clock();

//starting positions for player's ship
GLfloat player_x = (l+r)/2;
GLfloat player_y = -3.0;
GLfloat player_z = -8.0;

/*
 The init function sets up the lighting for the scene,
 enables back face culling and
 seeds the random number generator
*/
void init(void)
{
    //set up lighting
    initialiseLighting(l,r,b,t,n,f);
    
    //cull back faces
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    
    //seed random number gen
    srand(static_cast<unsigned int>(time(NULL)));
}

/*
 The display callback function
 is responsible for rendering objects to the screen
 */
void display(void)
{
    if(playerOne.isAlive())
    {
        //render world
        world.draw();
    
        //render enemies
        for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
        {
            enemies[i].draw();
        }
    
        //render ship
        playerShip.draw(player_x,player_y,player_z);
    
        //test collisions
        for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
        {
            if(playerShip.collidesWithSphere(&enemies[i]))
                playerOne.loseLife();
        }
    
        //display the on screen text (HUD)
        renderGameName(l, r, t, b);
        renderLives(l, r, t, b, playerOne.getLives());
        renderScore(l, r, t, b, playerOne.getScore());
    }
    else
    {
        //render the game over screen
        endScreen.draw();
     
        //randomise location for enemies
        for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
        {
            enemies[i].setZ(f-10);
            enemies[i].randomize();
        }
    }
    
    glutSwapBuffers();
}


/*
 The wait function ensures that the framerate is
 consistent by implementing a short delay on each iteration
 of the game loop
 */
void wait(float seconds)
{
    clock_t endwait;
    endwait = clock_t(clock () + seconds * CLOCKS_PER_SEC);
    while (clock() < endwait)
    {
        //doing nothing here
    }
}


/*
 The idle callback function (update) is responsible for
 implementing the game logic which occurs on each repetition 
 of the game loop
 */
void update(void)
{
    // update enemy positions
    for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
    {
        enemies[i].setZ(enemies[i].getZ()+enemies[i].getSpeed());
    }
    
    //randomise location for enemies who have passed the player
    for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
    {
        if(enemies[i].getZ()>n)
        {
            enemies[i].setZ(f);
            enemies[i].randomize();
            
            //update player score
            playerOne.setScore(playerOne.getScore()+1);
        }
    }
    
    // Wait and update the clock
    clock_t clocks_elapsed = clock() - clock_ticks;
    if ((float) clocks_elapsed < (float) CLOCKS_PER_SEC / (float) FRAMES_PER_SEC)
        wait(((float) CLOCKS_PER_SEC / (float) FRAMES_PER_SEC - (float) clocks_elapsed)/(float) CLOCKS_PER_SEC);
    clock_ticks = clock();
    
    glutPostRedisplay();
}

/*
 The special key callback function is responsible for
 dealing with arrow key events and moving the players ship
 throughout the scene
 */
void special(int key, int x, int y)
{
    if(key == GLUT_KEY_LEFT && GLUT_KEY_DOWN)
        player_x-=playerShip.getSpeed();
    else if (key == GLUT_KEY_RIGHT && GLUT_KEY_DOWN)
        player_x+=playerShip.getSpeed();
    else if (key == GLUT_KEY_UP && GLUT_KEY_DOWN)
        player_y+=playerShip.getSpeed();
    else if (key == GLUT_KEY_DOWN && GLUT_KEY_DOWN)
        player_y-=playerShip.getSpeed();

    glutPostRedisplay();
}

/*
 The keyboard callback function
 is responsible for dealing with keyboard events
 which are used to move the player's ship along 
 the Z axis as well as pausing and resuming the game
 */
void keyboard(unsigned char key, int w, int h)
{
    if(key == 'w' && GLUT_KEY_DOWN)
        player_z-=playerShip.getSpeed();
    else if (key == 's' && GLUT_KEY_DOWN)
        player_z+=playerShip.getSpeed();
    else if (key == 'p' && GLUT_KEY_DOWN)
    {
        playerShip.pause();
        for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
        {
            enemies[i].pause();
        }
    }
    else if (key == 'r' && GLUT_KEY_DOWN)
    {
        playerShip.resume();
        for(int i = 0; i<sizeof(enemies)/sizeof(Sphere); i++)
        {
            enemies[i].resume();
        }
    }
    
    glutPostRedisplay();
}

/*
 The mouse callback function deals with mouse
 events on the game over screen
 Left mouse button = play again
 Right mouse button = exit
 */

void mouse(int button, int state, int x, int y)
{
    //if the player is dead, deal with mouse events
    if(!playerOne.isAlive())
    {
        if(button==GLUT_LEFT_BUTTON)
        {
            playerOne.setScore(0);
            playerOne.setLives(3);
            playerOne.setAlive(true);
        }
        if(button == GLUT_RIGHT_BUTTON)
        exit(EXIT_SUCCESS);
    }
}

/*
 The reshape callback function controls how
 the screen responds when it is resized by a user
 */
void reshape(int w, int h)
{
    //set up the projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    
    //fov, aspect (w/h) = 1.0, near, far
    gluPerspective(60.0f,1.0f,1.0f,100.0f);
    
    //set up the viewport
    glViewport(0,0,(GLsizei) w,(GLsizei) h);
}

/*
 The main function intialises GLUT, registers
 callback functions and starts an event loop running
*/
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    initialiseWindow();
    init();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutIdleFunc(update);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(special);
    glutMouseFunc(mouse);
    glutMainLoop();
    return 0;
}
