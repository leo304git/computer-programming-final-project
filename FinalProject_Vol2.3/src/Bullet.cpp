#include "Bullet.h"
//Bullet::gBulletTexture
Bullet::Bullet(Player &player)
{
    //ctor
    owner = &player;
    if(owner->state != Player::super)
        owner->weaponAmmo[owner->weaponType]--;
    mPosX = owner->getPosX();
    mPosY = owner->getPosY();
    theta = owner->getTheta();
    mVel = 20;
    mVelX = mVel * cos(theta);
    mVelY = -mVel * sin(theta);
    setback = 10;
    loadBulletMedia();
    Mix_PlayChannel( -1, gShot, 0 );
    damage = -10;



}

Bullet::~Bullet()
{
    //dto
    owner = NULL;
    gBulletTexture.free();
}

void Bullet::move()
{
    mPosX += mVelX;
    mPosY += mVelY;
}

void Bullet::hit()
{

}

bool Bullet::loadBulletMedia()
{
    //Loading success flag
	bool success = true;
		if( !gBulletTexture.loadFromFile("picture/star30.png") )
	{
		printf( "Failed to load bullet texture!\n" );
		success = false;
	}
	gShot = Mix_LoadWAV( "sound effect/Long_Rifle_Shots.wav" );
	if( gShot == NULL )
	{
		printf( "Failed to load bang sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}
	return success;

}

void Bullet::render()
{
    gBulletTexture.render(mPosX, mPosY);
}

void Bullet::destroy()
{
    gBulletTexture.free();

}

int Bullet::getPosX()
{
    return mPosX;
}

int Bullet::getPosY()
{
    return mPosY;
}

double Bullet::getTheta()
{
    return theta;
}

Player* Bullet::getOwner()
{
    return owner;
}
