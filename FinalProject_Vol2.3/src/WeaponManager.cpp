#include "WeaponManager.h"

WeaponManager::WeaponManager()
{
    //ctor
    for(int i=0; i<100; i++)
        BulletPointer[i] = NULL;
    BulletNumber = 0;
    for(int i=0; i<2; i++)
        PlayerPointer[i] = NULL;
    PlayerNumber = 0;
    for(int i=0; i<100; i++)
        BarrelPointer[i] = NULL;
    BarrelNumber = 0;
    for(int i=0; i<100; i++)
        ZombiePointer[i] = NULL;
    ZombieNumber = 0;
    walls[0].x = SCREEN_WIDTH/2-312-100;
			walls[0].y = SCREEN_HEIGHT/2-350+50;
			walls[0].w = 200;
			walls[0].h = 100;

			walls[1].x = SCREEN_WIDTH/2+312-100;
			walls[1].y = SCREEN_HEIGHT/2-350+50;
			walls[1].w = 200;
			walls[1].h = 100;

			walls[2].x = SCREEN_WIDTH/2-312-100+150;
			walls[2].y = SCREEN_HEIGHT/2-150+50;
			walls[2].w = 200;
			walls[2].h = 100;

			walls[3].x = SCREEN_WIDTH/2+312-100-150;
			walls[3].y = SCREEN_HEIGHT/2-150 +50;
			walls[3].w = 200;
			walls[3].h = 100;

			walls[4].x = SCREEN_WIDTH/2-312-100;
			walls[4].y = SCREEN_HEIGHT/2+100;
			walls[4].w = 200;
			walls[4].h = 100;

			walls[5].x = SCREEN_WIDTH/2+312-100;
			walls[5].y = SCREEN_HEIGHT/2+100;
			walls[5].w = 200;
			walls[5].h = 100;
    waveNumber = 1;
    manaArray[0][0]=0;
    manaArray[0][1]=0;

    manaArray[1][0]=512;
    manaArray[1][1]=384;

    manaArray[2][0]=512;
    manaArray[2][1]=0;

    manaArray[3][0]=512;
    manaArray[3][1]=684;

     manaArray[4][0]=900;
    manaArray[4][1]=0;


     manaArray[5][0]=900;
    manaArray[5][1]=300;
    checkc = 0;





}

WeaponManager::~WeaponManager()
{
    //dtor
}
void WeaponManager::setPlayer()
{
    PlayerPointer[0] = new Player1(500, 150, 0);
    PlayerPointer[1] = new Player2(500, 450, 0);
}

void WeaponManager::handlePlayer(SDL_Event& e)
{
    for(int j=0; j<2; j++)if(PlayerPointer[j])
    {
        PlayerPointer[j]->HandleInput(e);
    }
}
void WeaponManager::movePlayer(SDL_Rect* wall)
{
    for(int j=0; j<Player::N; j++)if(PlayerPointer[j])
    {
        PlayerPointer[j]->move(wall);
        /*for(int i=0; i<100 && BarrelPointer[i] && BarrelPointer[i]->state == Barrel::sleeping; i++)
        {
            printf("i");
            if(checkCollision( PlayerPointer[j]->mCollider, BarrelPointer[i]->mCollider ))
            {
                PlayerPointer[j]->posX -= PlayerPointer[j]->Vx;
                PlayerPointer[j]->mCollider.x = PlayerPointer[j]->posX;
                PlayerPointer[j]->posY -= PlayerPointer[j]->Vy;
                PlayerPointer[j]->mCollider.y = PlayerPointer[j]->posY;
            }
        }*/

    }
}

void WeaponManager::checkPlaSup()
{
    for(int i=0; i<2; i++) if(PlayerPointer[i])
    {
        PlayerPointer[i]->checkSuper();
    }
}
bool WeaponManager::checkPlaDie()
{
    for(int i=0; i<2; i++) if(PlayerPointer[i])
    {
        //printf("%d", ZombiePointer[i]->blood);
        if(PlayerPointer[i]->blood<=0)
        {
            //printf("%d, ",ZombiePointer[i]->blood);
            //delete PlayerPointer[i];
            //PlayerPointer[i] = NULL;
            return true;
            printf("die");
        }


    }
    return 0;
}
void WeaponManager::showPlayer()
{
    for(int j=0; j<2; j++)if(PlayerPointer[j])
    {
        PlayerPointer[j]->render();
    }
}

//changed
void WeaponManager::setZombie()
{

    srand(time(NULL));
    if (Zombie::N<=50)
    {

        for(int i = 0 ; i< 100;i++)
        {
            int type;
            if(rand()%waveNumber == 0)
            {
                type = 0;
            }
            else if(rand()%waveNumber == 3)
            {
                type = 2;
            }
            else if(rand()%waveNumber == 4)
            {
                type = 3;
            }
            else
            {
                type = 1;
            }
            if(ZombiePointer[i]==NULL)
            {
                ZombiePointer[i]=new Zombie(type,((rand()%2)? -1 : SCREEN_WIDTH+1),rand()%768,0);
                //ZombiePointer[i]=new Zombie(0,-1,-1,0);
            }

        }
        waveNumber += 1;
    }
}
void WeaponManager::moveZombie(SDL_Rect*wall)
{

    for(int i = 0; i<100  ;i++) if(ZombiePointer[i] && PlayerPointer[i%2])
    {
        //ZombiePointer[i]->bumpEachOther(ZombiePointer);
        ZombiePointer[i]->FollowPlayer(PlayerPointer[i%2],wall);
        ZombiePointer[i]->killPlayer(PlayerPointer[i%2]);
        if(checkCollision(PlayerPointer[i%2]->mCollider, ZombiePointer[i]->mCollider)  && PlayerPointer[i%2]->state != Player::super)
        {
            if(ZombiePointer[i]->kill == true)
            PlayerPointer[i%2]->bloodChange(ZombiePointer[i]->damage);
            checkc = false;
            for(int j=0;j<100;j++) if(BarrelPointer[j])
            {
                if(checkCollision(PlayerPointer[i%2]->mCollider, BarrelPointer[j]->mCollider))
                    checkc = true;
            }
            if(!(checkCollision(PlayerPointer[i%2]->mCollider, walls[0]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[1]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[2]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[3]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[4]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[5]) ||
            PlayerPointer[i%2]->posX<0 || PlayerPointer[i%2]->posX>SCREEN_WIDTH-Player::PlayerWidth ||
            PlayerPointer[i%2]->posY<0 || PlayerPointer[i%2]->posY>SCREEN_HEIGHT-Player::PlayerHeight || checkc == true))
            PlayerPointer[i%2]->posChange(ZombiePointer[i]->setback * cos(ZombiePointer[i]->getTheta()) ,
                                        -ZombiePointer[i]->setback * sin(ZombiePointer[i]->getTheta()) );

        if(checkCollision(PlayerPointer[i%2]->mCollider, walls[0]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[1]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[2]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[3]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[4]) ||
            checkCollision(PlayerPointer[i%2]->mCollider, walls[5]) ||
            PlayerPointer[i%2]->posX<0 || PlayerPointer[i%2]->posX>SCREEN_WIDTH-Player::PlayerWidth ||
            PlayerPointer[i%2]->posY<0 || PlayerPointer[i%2]->posY>SCREEN_HEIGHT-Player::PlayerHeight || checkc == true)
                PlayerPointer[i%2]->posChange(-ZombiePointer[i]->setback * cos(ZombiePointer[i]->getTheta()) ,
                                        ZombiePointer[i]->setback * sin(ZombiePointer[i]->getTheta()) );
        }
    }
}

void WeaponManager::checkZomDie()
{
    for(int i=0; i<100; i++) if(ZombiePointer[i])
    {
        //printf("%d", ZombiePointer[i]->blood);
        if(ZombiePointer[i]->blood<=0)
        {
            //printf("%d, ",ZombiePointer[i]->blood);
            delete ZombiePointer[i];
            ZombiePointer[i] = NULL;
            printf("die");
        }

    }
}
void WeaponManager::showZombie()
{
    for(int i=0;i<100 ;i++) if(ZombiePointer[i])
    {
        ZombiePointer[i]->render();

    }
}
//changed

void WeaponManager::manageBullet()
{

    for(int j=0; j<Player::N; j++) if(PlayerPointer[j])
    if(PlayerPointer[j]->shoot)
    {
        if(PlayerPointer[j]->weaponAmmo[PlayerPointer[j]->weaponType]<=0)continue;
        bool stopshoot=0;
        for(int i=0; i<100; i++) if(BulletPointer[i])
        {       //子彈不重疊, 中彈不能射
            if(BulletPointer[i]->mPosX-PlayerPointer[j]->posX>=-PlayerPointer[j]->shootLag &&
               BulletPointer[i]->mPosX-PlayerPointer[j]->posX<=Player::PlayerWidth+PlayerPointer[j]->shootLag &&
               BulletPointer[i]->mPosY-PlayerPointer[j]->posY>=-PlayerPointer[j]->shootLag &&
               BulletPointer[i]->mPosY-PlayerPointer[j]->posY<Player::PlayerHeight+PlayerPointer[j]->shootLag)
            {
                stopshoot=1;
            }
        }
        if(!stopshoot){
            if(BulletNumber >= 100)
            {
                BulletNumber = 0;
            }
            while(BulletPointer[BulletNumber] != NULL)
            {
                BulletNumber++;
                if(BulletNumber >= 100) BulletNumber = 0;
            }
            BulletPointer[BulletNumber] = new Bullet(*PlayerPointer[j]);
            BulletNumber++;
            //printf("%d", BulletNumber);
        }
    }
    for(int i=0; i<100; i++) if(BulletPointer[i])
    {
        BulletPointer[i]->move();
        for(int j=0;j<2 ;j++){
                //printf("(%d, %d)", PlayerPointer[j]->id, BulletPointer[i]->owner->id);
        if(PlayerPointer[j] && BulletPointer[i] && PlayerPointer[j]->state != Player::super &&
           PlayerPointer[j]->id != BulletPointer[i]->owner->id &&
           BulletPointer[i]->mPosX>=PlayerPointer[j]->posX &&
           BulletPointer[i]->mPosX<=PlayerPointer[j]->posX+Player::PlayerWidth &&
            BulletPointer[i]->mPosY>=PlayerPointer[j]->posY &&
            BulletPointer[i]->mPosY<=PlayerPointer[j]->posY+Player::PlayerHeight)
        {
            PlayerPointer[j]->bloodChange(BulletPointer[i]->damage);

            if(!(checkCollision(PlayerPointer[j]->mCollider, walls[0]) ||
            checkCollision(PlayerPointer[j]->mCollider, walls[1]) ||
            checkCollision(PlayerPointer[j]->mCollider, walls[2]) ||
            checkCollision(PlayerPointer[j]->mCollider, walls[3]) ||
            checkCollision(PlayerPointer[j]->mCollider, walls[4]) ||
            checkCollision(PlayerPointer[j]->mCollider, walls[5]) ||
            PlayerPointer[j]->posX<0 || PlayerPointer[j]->posX>SCREEN_WIDTH-Player::PlayerWidth ||
            PlayerPointer[j]->posY<0 || PlayerPointer[j]->posY>SCREEN_WIDTH-Player::PlayerHeight))
                PlayerPointer[j]->posChange(BulletPointer[i]->setback * cos(BulletPointer[i]->getTheta()) ,
                                        -BulletPointer[i]->setback * sin(BulletPointer[i]->getTheta()) );
            printf("%d",PlayerPointer[j]->blood);
            //BulletPointer[i]->destroy();
            delete BulletPointer[i];
            BulletPointer[i] = NULL;

        }
        }
        for(int j=0; j<100; j++) if(ZombiePointer[j])
        {
            if(BulletPointer[i] &&
           BulletPointer[i]->mPosX>=ZombiePointer[j]->posX &&
           BulletPointer[i]->mPosX<=ZombiePointer[j]->posX+Zombie::ZombieWidth &&
            BulletPointer[i]->mPosY>=ZombiePointer[j]->posY &&
            BulletPointer[i]->mPosY<=ZombiePointer[j]->posY+Zombie::ZombieHeight)
            {
            ZombiePointer[j]->bloodChange(BulletPointer[i]->damage);
            if(ZombiePointer[j]->blood <= 0)
                BulletPointer[i]->owner->score += 1;
            if(!(checkCollision(ZombiePointer[j]->mCollider, walls[0]) ||
            checkCollision(ZombiePointer[j]->mCollider, walls[1]) ||
            checkCollision(ZombiePointer[j]->mCollider, walls[2]) ||
            checkCollision(ZombiePointer[j]->mCollider, walls[3]) ||
            checkCollision(ZombiePointer[j]->mCollider, walls[4]) ||
            checkCollision(ZombiePointer[j]->mCollider, walls[5]) ||
            ZombiePointer[j]->posX<0 || ZombiePointer[j]->posX>SCREEN_WIDTH-Zombie::ZombieWidth ||
            ZombiePointer[j]->posY<0 || ZombiePointer[j]->posY>SCREEN_WIDTH-Zombie::ZombieHeight))
            ZombiePointer[j]->posChange(BulletPointer[i]->setback * cos(BulletPointer[i]->getTheta()) ,
                                        -BulletPointer[i]->setback * sin(BulletPointer[i]->getTheta()) );

            //if(ZombiePointer[j])
            printf("%d, ",ZombiePointer[j]->blood);
            //BulletPointer[i]->destroy();
            delete BulletPointer[i];
            BulletPointer[i] = NULL;

            }
        }


        bool a=0;
        for(int k=0; k<6; k++)
        {
            if(BulletPointer[i] &&
               BulletPointer[i]->mPosX>=walls[k].x && BulletPointer[i]->mPosX<=walls[k].x+walls[k].w &&
               BulletPointer[i]->mPosY>=walls[k].y && BulletPointer[i]->mPosY<=walls[k].y+walls[k].h )
                a = 1;
        }
        if(BulletPointer[i] && (
           BulletPointer[i]->mPosX<=0 || BulletPointer[i]->mPosX>=SCREEN_WIDTH ||
           BulletPointer[i]->mPosY<=0 || BulletPointer[i]->mPosY>=SCREEN_HEIGHT ||
           a == true))

        {
            //BulletPointer[i]->destroy();

            delete BulletPointer[i];
            //BulletPointer[i]->~Bullet();
            BulletPointer[i] = NULL;
        }
        else
        {
            for(int j=0; j<100; j++) if(BarrelPointer[j] && BulletPointer[i])
            {
                if(BulletPointer[i]->mPosX >= BarrelPointer[j]->mPosX &&
                BulletPointer[i]->mPosX <= BarrelPointer[j]->mPosX+BarrelPointer[j]->mWidth &&
                BulletPointer[i]->mPosY >= BarrelPointer[j]->mPosY &&
                BulletPointer[i]->mPosY <= BarrelPointer[j]->mPosY+BarrelPointer[j]->mHeight)
                {
                    //printf("explode");
                    BarrelPointer[j]->state = Barrel::exploding;
                    delete BulletPointer[i];
                    BulletPointer[i] = NULL;
                }

            }
        }


    }

}

void WeaponManager::showBullet()
{
    for(int i=0;i<100;i++)if(BulletPointer[i])
    {
        BulletPointer[i]->render();
    }
}

void WeaponManager::manageBarrel()
{   //lay barrel
    for(int j=0; j<Player::N; j++) if(PlayerPointer[j])
    if(PlayerPointer[j]->LayBarrel && Barrel::N<100)
    {
        bool stop_lay=0;
        for(int i=0; i<100; i++) if(BarrelPointer[i])
        {       //barrel不重疊
            if(PlayerPointer[j]->posX - BarrelPointer[i]->mPosX >= -Player::PlayerWidth &&
               PlayerPointer[j]->posX - BarrelPointer[i]->mPosX <= BarrelPointer[i]->mWidth &&
               PlayerPointer[j]->posY - BarrelPointer[i]->mPosY >= -Player::PlayerHeight &&
               PlayerPointer[j]->posY - BarrelPointer[i]->mPosY <= BarrelPointer[i]->mHeight)
            {
                stop_lay=1;
                //printf("1");
            }
        }

        if(!stop_lay)
        {
            if(BarrelNumber >= 100)
            {
                BarrelNumber = 0;

            }
            while(BarrelPointer[BarrelNumber] != NULL)
            {
                BarrelNumber++;
                if(BarrelNumber >= 100) BarrelNumber = 0;
            }
            BarrelPointer[BarrelNumber] = new Barrel(*PlayerPointer[j]);
            BarrelNumber++;
            //printf("%d", BarrelNumber);
        }
    }
    for(int i=0; i<100; i++) if(BarrelPointer[i])
    {
        BarrelPointer[i]->explode();
        switch(BarrelPointer[i]->state)
        {
            case Barrel::setting:

                if(BarrelPointer[i]->owner){
                if(!(BarrelPointer[i]->owner->posX - BarrelPointer[i]->mPosX >= -Player::PlayerWidth &&
                BarrelPointer[i]->owner->posX - BarrelPointer[i]->mPosX <= BarrelPointer[i]->mWidth &&
                BarrelPointer[i]->owner->posY - BarrelPointer[i]->mPosY >= -Player::PlayerHeight &&
                BarrelPointer[i]->owner->posY - BarrelPointer[i]->mPosY <= BarrelPointer[i]->mHeight))
                {
                    BarrelPointer[i]->state = Barrel::sleeping;
                }
                }
                break;
            case Barrel::sleeping:
                for(int j=0; j<2; j++) if(PlayerPointer[j])
                {
                    if(checkCollision( PlayerPointer[j]->mCollider, BarrelPointer[i]->mCollider ))
                    {

                        PlayerPointer[j]->posX -= PlayerPointer[j]->Vx;
                        PlayerPointer[j]->mCollider.x = PlayerPointer[j]->posX;
                        PlayerPointer[j]->posY -= PlayerPointer[j]->Vy;
                        PlayerPointer[j]->mCollider.y = PlayerPointer[j]->posY;
                    }
                }
                for(int j=0; j<100; j++) if(ZombiePointer[j])
                {
                    if(checkCollision( BarrelPointer[i]->mCollider,  ZombiePointer[j]->mCollider))
                    {
                        ZombiePointer[j]->posX -= ZombiePointer[j]->Vx;
                        ZombiePointer[j]->mCollider.x = ZombiePointer[j]->posX;
                        ZombiePointer[j]->posY -= ZombiePointer[j]->Vy;
                        ZombiePointer[j]->mCollider.y = ZombiePointer[j]->posY;
                    }
                }
                break;
            case Barrel::exploding:
                for(int j=0; j<2; j++) if(PlayerPointer[j])
                {
                    if(BarrelPointer[i]->kill == true && PlayerPointer[j]->state != Player::super &&
                         PlayerPointer[j]->posX - BarrelPointer[i]->mPosX >= -Player::PlayerWidth &&
                         PlayerPointer[j]->posX - BarrelPointer[i]->mPosX <= BarrelPointer[i]->mWidth &&
                         PlayerPointer[j]->posY - BarrelPointer[i]->mPosY >= -Player::PlayerHeight &&
                         PlayerPointer[j]->posY - BarrelPointer[i]->mPosY <= BarrelPointer[i]->mHeight)
                    {

                        int disvecX = (PlayerPointer[j]->posX+Player::PlayerWidth/2) - (BarrelPointer[i]->mPosX+BarrelPointer[i]->mWidth/2);
                        int disvecY = (PlayerPointer[j]->posY+Player::PlayerHeight/2) - (BarrelPointer[i]->mPosY+BarrelPointer[i]->mHeight/2);
                        int distance = sqrt(pow(disvecX,2) + pow(disvecY,2));

                        PlayerPointer[j]->bloodChange(Barrel::damage);
                        PlayerPointer[j]->posChange(Barrel::setback * (disvecX/distance) / distance  ,
                                        -Barrel::setback * (disvecY/distance) / distance );
                        printf("%d ", PlayerPointer[j]->blood);
                    }
                }
                for(int j=0; j<100; j++)

                    if(BarrelPointer[j]  && BarrelPointer[j]->state == Barrel::sleeping &&
                        BarrelPointer[j]->mPosX - BarrelPointer[i]->mPosX >= -BarrelPointer[j]->mWidth &&
                         BarrelPointer[j]->mPosX - BarrelPointer[i]->mPosX <= BarrelPointer[i]->mWidth &&
                         BarrelPointer[j]->mPosY - BarrelPointer[i]->mPosY >= -BarrelPointer[j]->mHeight &&
                         BarrelPointer[j]->mPosY - BarrelPointer[i]->mPosY <= BarrelPointer[i]->mHeight
                        )
                    {
                        //printf("exploding");

                        BarrelPointer[j]->state = Barrel::exploding;
                    }
                    for(int j=0; j<100; j++) if(ZombiePointer[j])
                    {
                        if(BarrelPointer[i]->kill == true &&
                         ZombiePointer[j]->posX - BarrelPointer[i]->mPosX >= -Zombie::ZombieWidth &&
                         ZombiePointer[j]->posX - BarrelPointer[i]->mPosX <= BarrelPointer[i]->mWidth &&
                         ZombiePointer[j]->posY - BarrelPointer[i]->mPosY >= -Zombie::ZombieHeight &&
                         ZombiePointer[j]->posY - BarrelPointer[i]->mPosY <= BarrelPointer[i]->mHeight)

                        {
                            int disvecX = (ZombiePointer[j]->posX+Zombie::ZombieWidth/2) - (BarrelPointer[i]->mPosX+BarrelPointer[i]->mWidth/2);
                            int disvecY = (ZombiePointer[j]->posY+Zombie::ZombieHeight/2) - (BarrelPointer[i]->mPosY+BarrelPointer[i]->mHeight/2);
                            int distance = sqrt(pow(disvecX,2) + pow(disvecY,2));

                            ZombiePointer[j]->bloodChange(Barrel::damage);
                            if(ZombiePointer[j]->blood <= 0)
                                BarrelPointer[i]->owner->score += 1;
                            ZombiePointer[j]->posChange(Barrel::setback * (disvecX/distance) / distance  ,
                                        -Barrel::setback * (disvecY/distance) / distance );
                            printf("%d ", ZombiePointer[j]->blood);
                        }
                    }

                break;
            case Barrel::ending:
                delete BarrelPointer[i];
                BarrelPointer[i] = NULL;
                break;
            default: break;
        }
        /*if(BarrelPointer[i]->destroy == true)
        {
            printf("delete\t");
            delete BarrelPointer[i];
            BarrelPointer[i] = NULL;

        }*/
    }

}

/*void Barrel::Barrelsleep()
{
    for(int i=0; i<100 && BarrelPointer[i] && BarrelPointer[i]->state == Barrel::setting; i++)
    {
        if(!checkCollision( BarrelPointer[i]->owner.mCollider, BarrelPointer[i]->mCollider ))
        {
            BarrelPointer[i]->state = sleep;
        }
    }
}*/

void WeaponManager::showBarrel()
{
    for(int i=0;i<100;i++)if(BarrelPointer[i])
    {
        BarrelPointer[i]->render();
    }
}
void WeaponManager::setMana()
{
    srand(time(NULL));
    int randomPos = rand()%6;
    manaPointer = new mana(manaArray[randomPos][0],manaArray[randomPos][1]);
}

void WeaponManager::showMana()
{
    manaPointer->render();
}

bool WeaponManager::manageMana()
{
   for(int i=0;i<Player::N;i++)
   {
        if(checkCollision(PlayerPointer[i]->mCollider,manaPointer->mCollider))if(PlayerPointer[i])
        {
            if(PlayerPointer[i]->getBlood()>=450)
            {
                PlayerPointer[i]->weaponAmmo[PlayerPointer[i]->weaponType]+=30 ;
            }
            else
            {
                PlayerPointer[i]->bloodChange(50) ;
            }
            delete manaPointer;
            return true;
            manaPointer = NULL;

        }
   }
   return false;
}


int WeaponManager::showScore1()
{
    return PlayerPointer[0]->score;
}
int WeaponManager::showScore2()
{
    return PlayerPointer[1]->score;
}
