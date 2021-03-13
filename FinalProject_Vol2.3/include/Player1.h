#ifndef PLAYER1_H
#define PLAYER1_H

#include <Player.h>
#include "LTexture.h"
#include "Global.h"



class Player1 : public Player
{
    friend class WeaponManager;
    public:
        Player1(int,int,double);
        virtual ~Player1();
        void HandleInput(SDL_Event&);
    protected:
    private:
        LTexture gDotTexture;

        //Dot's collision box
		SDL_Rect mCollider;
        //vector<Barrel*> barrel;
        int id;
};

#endif // PLAYER1_H
