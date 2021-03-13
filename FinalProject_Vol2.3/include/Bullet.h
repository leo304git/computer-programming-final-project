#ifndef BULLET_H
#define BULLET_H
#include "LTexture.h"
#include "Player.h"
#include <SDL2/SDL_mixer.h>
//#include "WeaponManager.h"

class Bullet
{
    friend class WeaponManager;
    public:
        Bullet(Player&);
        virtual ~Bullet();
        int getPosX();
        int getPosY();
        double getTheta();
        void render();
        void destroy();
        void hit();
        bool loadBulletMedia();
        void move();
        Player* getOwner();


    protected:

    private:
        Player* owner;
        int mPosX, mPosY;
        double theta;
        int damage, setback;
        int mVelX, mVelY;
        int mVel;

        LTexture gBulletTexture;
        Mix_Chunk *gShot = NULL;

        //SDL_Rect* RenderClip;

};

#endif // BULLET_H
