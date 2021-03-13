#include "Player1.h"


Player1::Player1(int posX,int posY,double theta): Player(posX,posY,theta)
{
    /*//ctor
    if( !gDotTexture.loadFromFile("picture/dot.bmp") )
	{
		printf( "Failed to load dot texture!\n" );
		//success = false;
	}
    //ctor
    this ->posX=posX ;
    this ->posY=posY ;
    this ->theta =theta;
    blood = 500;
    //Set collision box dimension
	mCollider.w = PlayerWidth;
	mCollider.h = PlayerHeight;
    Vx = 0;
    Vy = 0;
    V = 10;
    N++;
    id = N;
    Player::N++;*/
}

Player1::~Player1()
{
    //dtor
    gDotTexture.free();
    //printf("gDotTexture.free");
}
void Player1::HandleInput(SDL_Event & event)
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: if(Vy>=0)Vy -= V;theta = M_PI/2.0;degrees=180; break;
            case SDLK_DOWN:if(Vy<=0) Vy += V;theta = 3.0*M_PI/2.0;degrees=0;break;
            case SDLK_LEFT: if(Vx>=0) Vx -=  V;theta = M_PI;degrees=90; break;
            case SDLK_RIGHT: if(Vx<=0) Vx += V;theta = 0;degrees=270; break;
            case SDLK_RCTRL:
                if(weaponType == 0)
                {
                    if(weaponAmmo[weaponType]>0){shoot = true; break;SDL_PollEvent(&event);}
                    else {shoot=false;break;SDL_PollEvent(&event);}
                }
                else if(weaponType == 1)
                {
                    if(weaponAmmo[weaponType]>0){LayBarrel = true; break;}
                    else {LayBarrel = false; break;}

                }

            case SDLK_RALT: changeWeapon(); break;
            case SDLK_SLASH:
                if(score >= 100)
                {
                    score -= 100;
                    state = super;
                }

                break;

        }
    }
     else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_UP: if(Vy<0)Vy += V; break;
            case SDLK_DOWN: if(Vy>0)Vy -= V; break;
            case SDLK_LEFT: if(Vx<0)Vx +=  V; break;
            case SDLK_RIGHT: if(Vx>0)Vx -= V; break;
            case SDLK_RCTRL:
                if(weaponType == 0)
                {
                    shoot = false;
                    break;
                }
                else if(weaponType == 1)
                {
                    LayBarrel = false; break;
                }

            //case SDLK_1: changeWeapon(); break;
        }
    }

}
