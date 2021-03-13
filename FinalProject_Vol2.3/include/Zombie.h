#ifndef ZOMBIE_H
#define ZOMBIE_H
#include "SDL2/SDL.h"
#include "Humanoid.h"
#include "Player.h"


class Zombie : public Humanoid
{
    friend class WeaponManager;
    public:
        static const int ZombieHeight = 60;
        static const int ZombieWidth = 60;
        //changed
        void bumpEachOther(Zombie**);
        Zombie(int, int, int, double);
        virtual ~Zombie();
        int getZombieN();
        void FollowPlayer(Player*&,SDL_Rect*);
        void killPlayer(Player* &);
        void render();
        int Vx;
        int Vy;
        int V;
        static int inGame;
        //changed

//changed
    protected:
        int type;
        static int N;
    private:
        SDL_Rect mCollider ;
        SDL_Rect oCollider;
//changed
        LTexture gZombieTexture;
        enum State{up, down, right, left, initi};
        State X, Y;
        int counter;
        int counter1;
        int damage;
        int setback;
        bool kill;
};


#endif // ZOMBIE_H
