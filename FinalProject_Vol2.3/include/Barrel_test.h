#ifndef barrel
#define barrel

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include "LTexture.h"
#include "Player.h"
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_mixer.h>
//Loads media
//bool loadMedia();
//const int WALKING_ANIMATION_FRAMES = 26;
//SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

//LTexture gSpriteSheetTexture;

class Barrel
{
    friend class WeaponManager;
public:
    //friend bool operator^()
    static int N;
    Barrel(Player&);
    virtual ~Barrel();
    void explode();
    void render();
    //void Destroy();

    int getPosX();
    int getPosY();
    int getBarrelN();



private:
    Player* owner;
    int mPosX, mPosY;
    int ExploExpand;
    int mWidth, mHeight;

    //Current animation frame
    int frame;
    SDL_Rect* currentClip ;
    bool destroy;
    enum State{setting, sleeping, exploding, ending};
    State state;
    State last_state;
    bool kill;
    static const int damage;
    static const int setback;
    static const int WALKING_ANIMATION_FRAMES = 26;
    SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
    LTexture gSpriteSheetTexture;
    //The sound effects that will be used
    Mix_Chunk *gBang = NULL;
    Mix_Chunk *gLay = NULL;

    SDL_Rect mCollider;
};

#endif // barrel
