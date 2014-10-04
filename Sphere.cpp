#include "Sphere.h"

Sphere::Sphere(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) : Entity(l,r,b,t,n,f)
{
    randomize();
    setZ(f);
    radius = (getRight()-getLeft())/15;
    setAlive(true);
}

//helper function to get a random float
float randomFloat(float a, float b)
{
    float random_float = ((float) rand()) / (float) RAND_MAX;
    float difference = b - a;
    float offset = random_float * difference;
    return a + offset;
}

void Sphere::draw()
{
    // Place a sphere in the scene
    int slices = 20;
    int stacks = 20;
    
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    
    //move the sphere
    glTranslatef(getX(),getY(),getZ());
    
    GLUquadricObj *quadobj;
    quadobj = gluNewQuadric();
    glMaterialfv(GL_FRONT,GL_AMBIENT_AND_DIFFUSE,colour);
    GLfloat sphereSpecular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, sphereSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 328);
    gluSphere(quadobj,radius,slices,stacks);
    gluDeleteQuadric(quadobj);
    
    // Set Material properties back to default values
    GLfloat defaultSpecular[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, defaultSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 0.0);
    
    glPopMatrix();
}

void Sphere::randomize()
{
    //randomise the (x,y) position of a sphere in the scene
    //set the Z position to the back of the game world and
    //choose a random speed for the ball
    setX(randomFloat(getLeft(), getRight()));
    setY(randomFloat(getBottom(), getTop()));
    colour[0] = randomFloat(0.0, 1.0);
    colour[1] = randomFloat(0.0, 1.0);
    colour[2] = randomFloat(0.0, 1.0);
    setSpeed(randomFloat(0.1, 0.4));
    setAlive(true);
}

bool Sphere::collidesWith(Entity *other)
{
    return false;
}
