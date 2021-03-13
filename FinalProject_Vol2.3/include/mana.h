#ifndef MANA_H
#define MANA_H
//1024*768
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include<ctime>
#include <iostream>
#include "Player.h"
using namespace std;

class mana
{
    friend class WeaponManager;
    public:
        mana(int, int) ;
        virtual ~mana();
		bool used =  false ;
		void render();
		static const int manaWidth = 60;
		static const int manaHeight = 50;

    protected:

    private:
        int posX ;
		int posY ;
		LTexture gManaTexture;
		SDL_Rect mCollider ;
};

#endif // MANA_H
