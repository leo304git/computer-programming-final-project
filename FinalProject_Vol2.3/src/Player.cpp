#include "Player.h"
//#include "Bullet.h"
#include "Humanoid.h"
#include "SDL2/SDL.h"
#include "Barrel_test.h"
#include <cmath>
#include<vector>


int Player::N = 0;
int Player::ZombieKilled = 0;
Player::Player(int posX,int posY,double theta)
{

    if(N==0)
    {
         if( !this->gDotTexture.loadFromFile("picture/img013.png") )
        {
            printf( "Failed to load dot texture!\n" );
            //success = false;
        }
    }
    else
    {
         if( !this->gDotTexture.loadFromFile("picture/player2.png") )
        {
            printf( "Failed to load dot texture!\n" );
        //success = false;
        }
    }
    N++;
    id = N;
	flipType = SDL_FLIP_NONE;
    //ctor
    this ->posX=posX ;
    this ->posY=posY ;
    this ->theta =theta;
    blood = 500;
    weaponNum = 2;
    weaponType=0;
    for(int i=0;i<weaponNum;i++)
        weaponAmmo[i]=100;
    //Set collision box dimension
	mCollider.w = PlayerWidth;
	mCollider.h = PlayerHeight;
    Vx = 0;
    Vy = 0;
    V = 5;
    score = 0;
    shootLag = 400;
    state = normal;
    last_state = normal;
    counter = 0;


}

Player::~Player()
{
    //dtor
    gDotTexture.free();
    //printf("gDotTexture.free");
}
//Humanoid::Shoot(){}
void Player::HandleInput(SDL_Event & event)
{

}
void Player::move(SDL_Rect* wall)
{
    posX += Vx;
    mCollider.x = posX;
    //If the dot collided or went too far to the left or right
    if( ( posX < 0 ) || ( posX + PlayerWidth > SCREEN_WIDTH ) ||
       checkCollision( mCollider, wall[0] ) || checkCollision( mCollider, wall[1]) ||
       checkCollision( mCollider, wall[2] ) || checkCollision( mCollider, wall[3] ) ||
       checkCollision( mCollider, wall[4]) || checkCollision(mCollider, wall[5]) )
    {
        //Move back
        posX -= Vx;
		mCollider.x = posX;
    }


    //Move the dot up or down
    posY += Vy;
	mCollider.y = posY;

    //If the dot collided or went too far up or down
    if( ( posY < 0 ) || ( posY + PlayerHeight > SCREEN_HEIGHT ) ||
        checkCollision( mCollider, wall[0] ) || checkCollision( mCollider, wall[1]) ||
       checkCollision( mCollider, wall[2] ) || checkCollision( mCollider, wall[3] ) ||
       checkCollision( mCollider, wall[4]) || checkCollision(mCollider, wall[5]))
    {
        //Move back
        posY -= Vy;
		mCollider.y = posY;
    }

}

void Player::render()
{
    //Show the dot
	gDotTexture.renderForRotate( posX, posY, NULL, degrees, NULL ,flipType);
	//gDotTexture.render( posX, posY+100 );
}

bool Player::operator !=(Player& player2)
{
    /*if(this->posX == player2.posX)
    {
        if(this->posY == player2.posY)
        {
            if(this->theta == player2.theta)
                return 0;
            else return 1;
        }
        else return 1;
    }
    else return 1;*/
    if(this->id == player2.id)
        return 1;
    else
        return 0;
}

void Player::changeWeapon()
{
    weaponType++;
    if(weaponType > 1)
    {
        weaponType = 0;
    }
}

void Player::checkSuper()
{
    if(state == super)
    {
        if(last_state == normal)
        {
            V += 5;
            shootLag = 0;
            counter++;
        }
        else
        {
            if(counter <= 1000)
            {
                counter++;
                if(counter%9 == 0 || counter%9 == 1 || counter%9 == 2)
                    gDotTexture.setColor(255, 100, 255);
                if(counter%3 == 3 || counter%9 == 4 || counter%9 == 5)
                    gDotTexture.setColor(255, 255, 100);
                if(counter%3 == 6 || counter%9 == 7 || counter%9 == 8)
                    gDotTexture.setColor(100, 255, 255);
            }
            else
            {
                V -= 5;
                Vx = 0;
                Vy = 0;
                shootLag = 400;
                counter = 0;
                state = normal;
                gDotTexture.setColor(255, 255, 255);
            }
        }

        last_state = state;
    }

}
