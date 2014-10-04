#include "GameOver.h"

GameOver::GameOver(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) : Entity(l,r,b,t,n,f), texturesLoaded(false)
{
}

void GameOver::draw()
{
    
    GLfloat l = getLeft();
    GLfloat r = getRight();
    GLfloat b = getBottom();
    GLfloat t = getTop();
    GLfloat n = getNear();
    GLfloat f = getFar();
    
    GLfloat white[] = {0.5f,0.5f,0.5f};
    
    static GLuint texName[1];
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
        char gameOverScreen[] = "/Users/mshirlaw/Ubuntu One/comp323/assignments/project/part2/Draft/Debris3D/Debris3D/images/gameover.ppm";
        bool success = PPMReader(gameOverScreen,height,width,tex1);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, height, width, 0, GL_RGB, GL_UNSIGNED_BYTE, tex1);
        delete tex1;
    
        texturesLoaded=true;
    }
    
    //bind textures
    glEnable(GL_TEXTURE_2D);
    glMaterialfv(GL_FRONT_AND_BACK,GL_AMBIENT_AND_DIFFUSE,white);
    GLfloat roomSpecular[] = { 0.3f, 0.3f, 0.3f, 1.0f };
    glMaterialfv(GL_FRONT, GL_SPECULAR, roomSpecular);
    glMaterialf(GL_FRONT, GL_SHININESS, 10);
    glBindTexture(GL_TEXTURE_2D, texName[0]);
    glBegin(GL_QUADS);
        glNormal3f(0.0,0.0,1.0);
        glTexCoord2f(0.0,0.0);
        glVertex3f(l,b,(n+f)/3);
        glTexCoord2f(0.0,1.0);
        glVertex3f(r,b,(n+f)/3);
        glTexCoord2f(1.0,1.0);
        glVertex3f(r,t,(n+f)/3);
        glTexCoord2f(1.0,0.0);
        glVertex3f(l,t,(n+f)/3);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    
}