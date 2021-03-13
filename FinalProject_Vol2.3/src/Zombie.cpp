#include "Zombie.h"
#include "Humanoid.h"
#include "Player.h"
#include <stdlib.h>
#include <time.h>
#include <iostream>

int Zombie::N = 0;
int Zombie::inGame = 0;
Zombie::Zombie(int type,int posX,int posY,double theta)
{//changed
    //ctor
    Vx=5;
    Vy=5;
    V = 2;
    damage = -5;
    counter1=0;
    setback = -1;
    kill = false;
    if( !gZombieTexture.loadFromFile("picture/Zombies.png") )
	{
		printf( "Failed to load dot texture!\n" );
		//success = false;
	}
	mCollider.w = ZombieWidth;
	mCollider.h = ZombieHeight;
	oCollider.w = ZombieWidth+20;
	oCollider.h = ZombieHeight+20;
    this->posX = posX;
    this ->posY = posY;
    this -> theta = theta;
    this ->type = type;
    if(type == 1)
    {
        this->blood = 100;
        gZombieTexture.setColor(255, 100, 100);
    }
    else if(type == 0)
    {
        this->blood = 50;
    }
    else if(type == 2)
    {
        blood = 50;
        gZombieTexture.setAlpha(100);
    }
    else if(type == 3)
    {
        blood = 100;
        gZombieTexture.setColor(100, 255, 100);
    }

    N++;
    X=initi;
    Y=initi;
    counter = 0;
}
//changed
Zombie::getZombieN()
{
    return N;
}
void Zombie::FollowPlayer(Player*& player,SDL_Rect* wall)
{//changed
    int disX =  player->getPosX()-posX ;
    int disY =  player->getPosY()-posY ;
    theta = atan2(disY,disX);
    //printf("%d",theta/M_PI);
    //printf("PI");
    //printf("\n");
    //posX+=Vx*cos(theta);
    //posY+=Vy*sin(theta);



    int initialPosX = posX;
    int initialPosY = posY;

    posX += Vx;
    mCollider.x = posX;
    oCollider.x = posX - 10;
    if(posX>0&&posX<1024&&posY>0&&posY<768)
    {
       Zombie::inGame ++ ;
    }
    else Zombie::inGame -- ;
    if(type == 2)
    {
        Vx = V * cos(theta);
    }
    else
    {
    if(checkCollision( mCollider, wall[0] ) || checkCollision( mCollider, wall[1] ) ||
       checkCollision( mCollider, wall[2] ) || checkCollision( mCollider, wall[3] ) ||
       checkCollision( mCollider, wall[4] ) || checkCollision( mCollider, wall[5] ))
    {

        //Move back
        posX -= Vx;
        if(checkCollision( oCollider, wall[0] ) || checkCollision( oCollider, wall[1] ) ||
           checkCollision( oCollider, wall[2] ) || checkCollision( oCollider, wall[3] ) ||
           checkCollision( oCollider, wall[4] ) || checkCollision( oCollider, wall[5] ))
           {
                //printf("collide");
               if(Y == initi)
                Y = (disY>0)? down : up;
                switch(Y)
                {
                case down:
                    posY += 1.5;
                    //printf("down");
                    break;
                case up:
                    posY -= 1.5;
                    //printf("up");
                    break;

                //default: break;
                }
           }
           //else Y = initi;

        //posY += 1;
		mCollider.x = posX;
		oCollider.x = posX-10;

        /*int vecX =initialPosX-posX ;
        int vecY =initialPosY-posY ;
        theta = atan2(vecY,vecX);
        posX += Vx*cos(theta)/2;
        posY += Vy*sin(theta)/2;
		mCollider.x = posX;
        mCollider.y = posY;*/
    }
    else{
            Vx = V * cos(theta);
            Y = initi;
            /*switch(Y)
            {
            case initi:
                 break;
            case up:
                posY -= 1; break;
            case down:
                posY += 1; break;
            }*/

    }
    }
    posY += Vy;
    mCollider.y = posY;
    oCollider.y = posY - 10;
    if(type == 2)
    {
        Vy = V * sin(theta);
    }
    else
    {
    if(checkCollision( mCollider, wall[0] ) || checkCollision( mCollider, wall[1] ) ||
       checkCollision( mCollider, wall[2] ) || checkCollision( mCollider, wall[3] ) ||
       checkCollision( mCollider, wall[4] ) || checkCollision( mCollider, wall[5] ))
       {
           posY -= Vy;

            if(checkCollision( oCollider, wall[0] ) || checkCollision( oCollider, wall[1] ) ||
           checkCollision( oCollider, wall[2] ) || checkCollision( oCollider, wall[3] ) ||
           checkCollision( oCollider, wall[4] ) || checkCollision( oCollider, wall[5] ))
           {
                //printf("collide");
            if(X == initi)
            {
                 X = (disX>0)? right : left;
                 //printf("X");
            }

            switch(X)
            {
            case right:
                posX += 1.5;
                //printf("right");
                break;
            case left:
                posX -= 1.5;
                //printf("left");
                break;
            //default: break;
            }
           }
           //else X = initi;
            //posX += 1;
            mCollider.y = posY;
            oCollider.y = posY-10;
       }
       else
        {
            Vy = V * sin(theta);
            X = initi;
       }
    }
    if(type == 3)
    {
        bool goback=0;
        gZombieTexture.setAlpha(counter/10);
        if(counter >= 2550)
            goback = 1;
        if(counter <= 0)
            goback = 0;
        if(goback)
            counter--;
        else counter++;

    }
     if(inGame>=Zombie::N)
       {
           if(posX<=0)
           {
               posX ++;
           }
           else if(posX>=1024)
           {
               posX --;
           }
           if(posY<=0)
           {
               posY++;
           }
           else if(posY>=768)
           {
               posY--;
           }
       }
}
void Zombie::killPlayer(Player*& player)
{
    /*double distX, distY, dist;
    distX = (player->getPosX() + Player::PlayerWidth/2) - (this->posX + Zombie::ZombieWidth/2);
    distY = (player->getPosY() + Player::PlayerHeight/2) - (this->posY + Zombie::ZombieHeight/2);
    dist = pow(pow(distX, 2)+pow(distY, 2), 1/2);
    printf("%f", dist);*/
    int disX =  player->getPosX()-posX ;
    int disY =  player->getPosY()-posY ;
    theta = atan2(disY,disX);

    if(abs(disX)<=30 && abs(disX)>=2 && abs(disY)<=30 && abs(disY)>=2)
    {
        //printf("%d ", );
        posX += 10*cos(theta);
        posY += 10*sin(theta);
        if(counter1%100 == 0)
        {
            kill = true;
            counter1 = 0;
        }
        else kill = false;
    }
    counter1++;
    if(counter1>=1000) counter = 0;

}
void Zombie :: bumpEachOther(Zombie** ZombiePointer)
{
    srand(time(NULL));
    if(inGame == true)
    {
        for(int i =0;i<100;i++)if(ZombiePointer[i])
        {
            if(ZombiePointer[i]==this) continue;
            else
            {
                if(checkCollision(mCollider,ZombiePointer[i]->mCollider))
                {

                    if(rand()%1==0){ Vx++;Vy++;}
                    else {Vx--;Vy--;}
                    mCollider.x = posX;
                    mCollider.y = posY;

                }
            }
        }
    }
}//changed

Zombie::~Zombie()
{
    //dtor
    gZombieTexture.free();
    N--;
}

void Zombie::render()
{
    gZombieTexture.render(posX, posY);
}
