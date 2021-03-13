#ifndef PLAYER2_H
#define PLAYER2_H

#include <Player.h>
#include "LTexture.h"
#include "Global.h"



class Player2 : public Player
{
    friend class WeaponManager;
    public:
        Player2(int, int, double);
        virtual ~Player2();
        void HandleInput(SDL_Event&);
    protected:

    private:
         LTexture gDotTexture;

        //Dot's collision box
		SDL_Rect mCollider;
        //vector<Barrel*> barrel;
        int id;
};

#endif // PLAYER2_H
