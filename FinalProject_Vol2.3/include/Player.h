#ifndef PLAYER_H
#define PLAYER_H
#include "Humanoid.h"
#include "SDL2/SDL.h"
#include <cmath>
#define _USE_MATH_DEFINES // for C++
#include "LTexture.h"
#include "Global.h"



class Player : public Humanoid
{
    friend class WeaponManager;
    public:
        Player(int ,int , double);
        virtual ~Player();
        void Shoot();//
        void move(SDL_Rect*);
        void changeWeapon();
        virtual void HandleInput(SDL_Event&);
        void render();
        static const int PlayerWidth = 60;
        static const int PlayerHeight = 50;
        bool LayBarrel = 0;
        bool shoot = 0;
        static int N;
        static int ZombieKilled;
        bool operator !=(Player&);
        int weaponAmmo[2];
        int weaponType;
        //void getMana();
        enum State{normal, super, hit};
        State state;

    protected:

        int weaponNum;
        double degrees;
        int score;
        int shootLag;
        State last_state;
        void checkSuper();
        int counter;


    private:

        LTexture gDotTexture;
        SDL_RendererFlip flipType ;
        //Dot's collision box
		SDL_Rect mCollider;

        //vector<Barrel*> barrel;
        int id;

};


#endif // PLAYER_H
