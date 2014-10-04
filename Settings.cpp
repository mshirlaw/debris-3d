#include "Settings.h"

void initialiseWindow()
{
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(300,100);
    glutCreateWindow("Debris3D");
}

void initialiseLighting(GLfloat l,GLfloat r,GLfloat b,GLfloat t,GLfloat n,GLfloat f)
{
    //white light color
    const GLfloat whiteLightColor[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    
    // set up a first light
    //centre top - GL_LIGHT0
    glEnable(GL_LIGHT0); // Turn on the light 0
    glLightfv(GL_LIGHT0, GL_AMBIENT, whiteLightColor);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, whiteLightColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, whiteLightColor);
    GLfloat lightPos0[] = {(l+r)/2, t, (n+f)/2, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);
    
    // set up a second light
    //centre bottom - GL_LIGHT1
    glEnable(GL_LIGHT1); // Turn on the light 1
    glLightfv(GL_LIGHT1, GL_AMBIENT, whiteLightColor);
    glLightfv(GL_LIGHT1, GL_DIFFUSE, whiteLightColor);
    glLightfv(GL_LIGHT1, GL_SPECULAR, whiteLightColor);
    GLfloat lightPos1[] = {(l+r)/2, b, (n+f)/2, 1.0 };
    glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);
    
    // Now enable lighting
    glEnable(GL_LIGHTING);


}

void renderGameName(GLfloat l, GLfloat r, GLfloat t, GLfloat b)
{

    //display text
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //game name
    glRasterPos3f(r/15,t/6.0,0.0);
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'D');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'e');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'b');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'r');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'i');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 's');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, ' ');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, '3');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'D');
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    
}

void renderLives(GLfloat l, GLfloat r, GLfloat t, GLfloat b, GLuint lives)
{
    //display text
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //display lives
    glRasterPos3f(r/15,t/8.0,0.0 );
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'L');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'i');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'v');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'e');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 's');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, ':');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, ' ');
    
    if (lives == 3)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, '3');
    else if (lives == 2)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, '2');
    else if (lives == 1)
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, '1');
    else
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, '0');
    
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

void renderScore(GLfloat l, GLfloat r, GLfloat t, GLfloat b, GLuint score)
{
    
    
    //display text
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
    
    //display score
    glRasterPos3f(r/15,t/7.0,0.0 );
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'S');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'c');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'o');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'r');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, 'e');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, ':');
    glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, ' ');
    
    std::string s = std::to_string(score);
    int i=0;
    while(*(s.c_str()+i) != '\0')
    {
        glutBitmapCharacter( GLUT_BITMAP_HELVETICA_18, *(s.c_str()+i));
        i++;
    }

    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
}

