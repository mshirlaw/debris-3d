#include "Ship.h"

Ship::Ship(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) : Entity(l,r,b,t,n,f)
{
    setSpeed(0.5);
}

Ship::~Ship()
{

}

void Ship::draw(GLfloat x, GLfloat y, GLfloat z)
{

    const float XSCALE = 0.6;
    const float YSCALE = 0.4;
    const float ZSCALE = 0.6;
    
    //update x,y,z positions
    setX(x);
    setY(y);
    setZ(z);
    
    //colours
    float blue[] = {0.0f,0.0f,1.0f};
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    glTranslatef(x,y,z);
    glScalef(XSCALE,YSCALE,ZSCALE);
    
    
    //render a blue cube to the screen which can be controlled by the player
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,blue);
    GLfloat sphereSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, sphereSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 328);
    
    glBegin(GL_POLYGON); // top face oriented toward y
    glNormal3f(0.0,1.0,0.0);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glEnd();
    
    glBegin(GL_POLYGON); // back face oriented toward -z
    glNormal3f(0.0,0.0,-1.0);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
    
    glBegin(GL_POLYGON); // right face oriented toward x
    glNormal3f(1.0,0.0,0.0);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, 1.0f, -1.0f);
    glEnd();
    
    glBegin(GL_POLYGON); // left face oriented toward -x
    glNormal3f(-1.0,0.0,0.0);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, -1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glEnd();
    
    glBegin(GL_POLYGON); // bottom face oriented toward -y
    glNormal3f(0.0,-1.0,0.0);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, -1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();
    
    glBegin(GL_POLYGON); // front face oriented toward z
    glNormal3f(0.0,0.0,1.0);
    glVertex3f(1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, 1.0f, 1.0f);
    glVertex3f(-1.0f, -1.0f, 1.0f);
    glVertex3f(1.0f, -1.0f, 1.0f);
    glEnd();
     
    // Set Material properties back to default values
    GLfloat defaultSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, defaultSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
    
    glPopMatrix();
    
}

/*
 Uses the AABB collision detection algorithm to determine
 whether the player's ship has collided with one of the spheres in the scene'
 - boxMin[] bottom left (x,y,z) of player's ship
 - boxMax[] top right (x,y,z) of player's ship
 - sphereMid[] midPoint of ball
 - rSquared = radius^2
 - minDistance min distance from centre of sphere to box
*/
bool Ship::collidesWithSphere(Sphere *s)
{
    GLfloat minDistance = 0;
    GLfloat rSquared = s->getRadius() * s->getRadius();
    GLfloat boxMin[3]={ getX(), getY(), getZ()};
    GLfloat boxMax[3]={ static_cast<GLfloat>(getX()+2.0),
                        static_cast<GLfloat>(getY()+2.0),
                        static_cast<GLfloat>(getZ()+2.0) };
    GLfloat sphereMid[3] = { s->getX(), s->getY(), s->getZ() };
    
    for(int i = 0; i < 3; i++ )
    {
        if(sphereMid[i] < boxMin[i])
            minDistance += sqrt( sphereMid[i] - boxMin[i] );
        else if( sphereMid[i] > boxMax[i] )
            minDistance += sqrt(sphereMid[i] - boxMax[i]);
    }
    
    //return true if we have detected a collision
    if(s->isAlive() && (minDistance <= rSquared) )
    {
        s->setAlive(false);
        return true;
    }
    
    return false;
}


