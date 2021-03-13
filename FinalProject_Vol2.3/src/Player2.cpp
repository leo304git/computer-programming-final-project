#include "Player2.h"

Player2::Player2(int posX,int posY,double theta):Player(posX,posY,theta)
{
   /* //ctor
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
    id = N;*/
}

Player2::~Player2()
{
    //dtor
    gDotTexture.free();
    //printf("gDotTexture.free");
}
void Player2::HandleInput(SDL_Event & event)
{
    //If a key was pressed
    if( event.type == SDL_KEYDOWN )
    {
        //Adjust the velocity
        switch( event.key.keysym.sym )
        {
            case SDLK_w: if(Vy>=0)Vy -= V;theta = M_PI/2.0;degrees=180; break;
            case SDLK_s:if(Vy<=0) Vy += V;theta = 3.0*M_PI/2.0;degrees=0; break;
            case SDLK_a: if(Vx>=0) Vx -=  V;theta = M_PI;degrees = 90; break;
            case SDLK_d: if(Vx<=0) Vx += V;theta = 0;degrees = 270; break;
            case SDLK_SPACE:
                if(weaponType == 0)
                {
                    if(weaponAmmo[weaponType]>0){shoot = true;break;}
                    else {shoot=false;break;}
                }
                else if(weaponType == 1)
                {
                    if(weaponAmmo[weaponType]>0){LayBarrel = true; break;}
                    else {LayBarrel = false; break;}

                }

            case SDLK_1: changeWeapon(); break;
            case SDLK_2:
                score -= 100;
                state = super;
                break;
        }
    }
     else if( event.type == SDL_KEYUP )
    {
        switch( event.key.keysym.sym )
        {
            case SDLK_w: if(Vy<0)Vy += V; break;
            case SDLK_s: if(Vy>0)Vy -= V; break;
            case SDLK_a: if(Vx<0)Vx +=  V; break;
            case SDLK_d: if(Vx>0)Vx -= V; break;
            case SDLK_SPACE:
                if(weaponType == 0)
                {
                    shoot = false; break;
                }
                else if(weaponType == 1)
                {
                    LayBarrel = false; break;
                }

            //case SDLK_1: changeWeapon(); break;
        }
    }

}
