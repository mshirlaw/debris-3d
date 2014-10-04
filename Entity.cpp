#include "Entity.h"

Entity::Entity(GLfloat l, GLfloat r, GLfloat b, GLfloat t, GLfloat n, GLfloat f) : left(l), right(r), bottom(b), top(t), near(n), far(f)
{

}

Entity::~Entity()
{

}

void Entity::pause()
{
    if(speed > 0.0)
    {
        previousSpeed = speed;
    }
    speed = 0.0;
}

void Entity::resume()
{
    if (previousSpeed > 0.0) {
        speed = previousSpeed;
    }
    else
    {
        //do nothing
    }

}
