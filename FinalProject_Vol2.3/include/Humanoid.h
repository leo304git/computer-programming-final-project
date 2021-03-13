#ifndef HUMANOID_H
#define HUMANOID_H

#include <SDL2/SDL.h>
#include <graphics.h>
//#include "Bullet.h"
class Humanoid
{
    friend class WeaponManager;
    public:
        Humanoid();
        virtual ~Humanoid();
        int getBlood();
        void bloodChange(int );
        void posChange(double ,double );
        int getPosX();
        int getPosY();
        double getTheta();


    protected:
        int blood;
        int posX;
        int posY;
        double theta;
        int Vx;
        int Vy;
        int V;


    private:
};


#endif // HUMANOID_H
