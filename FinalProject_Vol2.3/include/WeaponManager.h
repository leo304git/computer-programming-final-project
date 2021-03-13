#ifndef WEAPONMANAGER_H
#define WEAPONMANAGER_H
#include "Bullet.h"
#include "Player.h"
#include "Player1.h"
#include "Player2.h"
#include "Zombie.h"
#include "Barrel_test.h"
#include "Global.h"
#include <ctime>
#include "mana.h"
class WeaponManager
{
    friend bool loadText_death();
    friend bool gameplay();
    public:
        WeaponManager();
        virtual ~WeaponManager();

        void setPlayer();
        void handlePlayer(SDL_Event&);
        void movePlayer(SDL_Rect*);
        void checkPlaSup();
        bool checkPlaDie();
        void showPlayer();

        void setZombie();
        void moveZombie(SDL_Rect*);
        void checkZomDie();
        void showZombie();

        void manageBullet();
        void showBullet();



        void manageBarrel();
        //void Barrelsleep();
        void showBarrel();

 		void setMana();
        void showMana();
        bool manageMana();

        int showScore1();
        int showScore2();



    protected:

    private:
        mana* manaPointer;
        int manaArray[8][2];
        Bullet* BulletPointer[100];
        int BulletNumber;
        Player* PlayerPointer[2];
        int PlayerNumber;
        Barrel* BarrelPointer[100];
        int BarrelNumber;
        Zombie* ZombiePointer[100];
        int ZombieNumber;
        SDL_Rect walls[6];
        int waveNumber;
        bool checkc;
};

#endif // WEAPONMANAGER_H
