#include "Environment.h"

Environment::Environment(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) : Entity(l,r,b,t,n,f), texturesLoaded(false)
{
}

void Environment::draw()
{
    GLfloat l = getLeft();
    GLfloat r = getRight();
    GLfloat b = getBottom();
    GLfloat t = getTop();
    GLfloat n = getNear();
    GLfloat f = getFar();
 
    GLfloat white[] = {0.5f,0.5f,0.5f};
    
    static GLuint texName[4];
    GLubyte* tex1;
    
    //load textures once only
    if(!texturesLoaded)
    {
        glGenTextures(3,texName);
        glBindTexture(GL_TEXTURE_2D, texName[0]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        int height,width;
        char walls[] = "/Users/mshirlaw/Ubuntu One/comp323/assignments/project/part2/Draft/Debris3D/Debris3D/images/cracked_concrete_256.ppm";
        bool success = PPMReader(walls,height,width,tex1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex1);
        delete tex1;
        
        glBindTexture(GL_TEXTURE_2D, texName[1]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        char floor[] = "/Users/mshirlaw/Ubuntu One/comp323/assignments/project/part2/Draft/Debris3D/Debris3D/images/pebbles_concrete_256.ppm";
        success = PPMReader(floor,height,width,tex1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex1);
        delete tex1;
        
        glBindTexture(GL_TEXTURE_2D, texName[2]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        char roof[] = "/Users/mshirlaw/Ubuntu One/comp323/assignments/project/part2/Draft/Debris3D/Debris3D/images/stars_256.ppm";
        success = PPMReader(roof,height,width,tex1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex1);
        delete tex1;

        
        glBindTexture(GL_TEXTURE_2D, texName[3]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        char endWall[] = "/Users/mshirlaw/Ubuntu One/comp323/assignments/project/part2/Draft/Debris3D/Debris3D/images/stars2_256.ppm";
        success = PPMReader(endWall,height,width,tex1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex1);
        delete tex1;
        
        texturesLoaded=true;
    }

    glEnable(GL_TEXTURE_2D);
    
    
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
    GLfloat roomSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, roomSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
 
    
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    int wslices = 100, wstrips = 100;
    float qwidth = (f-n)/wslices, qheight = (t-b)/wstrips;
    float twidth = 1.0/wslices, theight = 1.0/wstrips;
 
    //render the right wall
    glNormal3f(-1.0,0.0,0.0);
    for(int i = 0; i < wstrips; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= wslices; j++)
        {
            glTexCoord2f(i*theight,j*twidth);
            glVertex3f(r,b+i*qheight,n+j*qwidth);
            glTexCoord2f((i+1)*theight,j*twidth);
            glVertex3f(r,b+(i+1)*qheight,n+j*qwidth);
        }
        glEnd();
    }
 
    //render the left wall
    glNormal3f(1.0,0.0,0.0);
    for(int i = 0; i < wstrips; i++)
    {
        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= wslices; j++)
        {
            glTexCoord2f((i+1)*theight,j*twidth);
            glVertex3f(l,b+(i+1)*qheight,n+j*qwidth);
            glTexCoord2f(i*theight,j*twidth);
            glVertex3f(l,b+i*qheight,n+j*qwidth);
        }
        glEnd();
    }
 
    //render the rear wall
    qwidth = (r-l)/wslices, qheight = (t-b)/wstrips;
    glBindTexture(GL_TEXTURE_2D, texName[3]);
    glNormal3f(0.0,0.0,1.0);
    for(int j = 0; j < wstrips; j++)
    {
        glBegin(GL_QUAD_STRIP);
        for(int i = 0; i <= wslices; i++)
        {
            glTexCoord2f(i*twidth,(j+1)*theight);
            glVertex3f(l+i*qwidth,b+(j+1)*qheight,f);
            glTexCoord2f(i*twidth,j*theight);
            glVertex3f(l+i*qwidth,b+j*qheight,f);
        }
        glEnd();
    }
    
    
    //render the floor
    glBindTexture(GL_TEXTURE_2D, texName[1]);
    
    //back left
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.75);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,f);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l,b,f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l,b,(f-n)*0.75);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.5);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.75);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l,b,(f-n)*0.75);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l,b,(f-n)*0.5);
    glEnd();
    
    //front left
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.25);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.5);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l,b,(f-n)*0.5);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l,b,(f-n)*0.25);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,n);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.25);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l,b,(f-n)*0.25);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l,b,n);
    glEnd();
    
    //back right
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(r,b,(f-n)*0.75);
        glTexCoord2f(0.0,1.0);
        glVertex3f(r,b,f);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.75);
    glEnd();

    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(r,b,(f-n)*0.5);
        glTexCoord2f(0.0,1.0);
        glVertex3f(r,b,(f-n)*0.75);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.75);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.5);
    glEnd();
    
    //front right
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(r,b,(f-n)*0.25);
        glTexCoord2f(0.0,1.0);
        glVertex3f(r,b,(f-n)*0.5);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.5);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.25);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(r,b,n);
        glTexCoord2f(0.0,1.0);
        glVertex3f(r,b,(f-n)*0.25);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,b,(f-n)*0.25);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,b,n);
    glEnd();
    
    
    //render the ceiling in stars
    glBindTexture(GL_TEXTURE_2D, texName[2]);
   
    //back left
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l,t,(f-n)*0.75);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l,t,f);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.75);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l,t,(f-n)*0.5);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l,t,(f-n)*0.75);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.75);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.5);
    glEnd();
    
    //front left
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l,t,(f-n)*0.25);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l,t,(f-n)*0.5);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.5);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.25);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l,t,n);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l,t,(f-n)*0.25);
        glTexCoord2f(1.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.25);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,n);
    glEnd();
    
    //back right
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.75);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,f);
        glTexCoord2f(1.0,1.0);
        glVertex3f(r,t,f);
        glTexCoord2f(1.0,0.0);
        glVertex3f(r,t,(f-n)*0.75);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.5);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.75);
        glTexCoord2f(1.0,1.0);
        glVertex3f(r,t,(f-n)*0.75);
        glTexCoord2f(1.0,0.0);
        glVertex3f(r,t,(f-n)*0.5);
    glEnd();
    
    //front right
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.25);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.5);
        glTexCoord2f(1.0,1.0);
        glVertex3f(r,t,(f-n)*0.5);
        glTexCoord2f(1.0,0.0);
        glVertex3f(r,t,(f-n)*0.25);
    glEnd();
    
    glBegin(GL_QUADS);
        glNormal3f(0.0,-1.0,0.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l+(r-l)*0.5,t,n);
        glTexCoord2f(0.0,1.0);
        glVertex3f(l+(r-l)*0.5,t,(f-n)*0.25);
        glTexCoord2f(1.0,1.0);
        glVertex3f(r,t,(f-n)*0.25);
        glTexCoord2f(1.0,0.0);
        glVertex3f(r,t,n);
    glEnd();

    glDisable(GL_TEXTURE_2D);
    
}


bool Environment::collidesWith(Entity *other)
{
    return false;
}


