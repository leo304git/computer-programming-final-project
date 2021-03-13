#include "Humanoid.h"
//#include "Bullet.h"
//#include <imagehlp.h>
Humanoid::Humanoid()
{
    //ctor
}

Humanoid::~Humanoid()
{
    //dtor
}
void Humanoid ::bloodChange(int change)
{
    blood += change;
}

int Humanoid::getBlood()
{
    return blood;
}
void Humanoid::posChange(double changeX,double changeY)
{
    posX += changeX;
    posY += changeY;
}
int Humanoid::getPosX()
{
    return posX;
}
int Humanoid::getPosY()
{
    return posY;
}
double Humanoid :: getTheta()
{
    return theta;
}

