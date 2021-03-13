#include"Barrel_test.h"
#include "Global.h"
int Barrel::N = 0;
const int Barrel::damage = -50;
const int Barrel::setback = 40;
const int WALKING_ANIMATION_FRAMES = 26;
Barrel::Barrel(Player &player)
{
    owner = &player;
    if(owner->state != Player::super)
        owner->weaponAmmo[owner->weaponType]--;
    frame = 0;
    if( !gSpriteSheetTexture.loadFromFile( "picture/explosion_new.png" ) )
	{
		printf( "Failed to load walking animation texture!\n" );

	}
	else
	{
		//Set sprite clips
		for(int i=0; i<WALKING_ANIMATION_FRAMES-2; i++)
        {
            gSpriteClips[ i ].x = (i%5)*128;
            gSpriteClips[ i ].y = (i/5)*128;
            gSpriteClips[ i ].w =  128;
            gSpriteClips[ i ].h =  128;
        }
        gSpriteClips[ 25 ].x = 640;
        gSpriteClips[ 25 ].y = 0;
        gSpriteClips[ 25 ].w = 64;
        gSpriteClips[ 25 ].h = 64;

	}

	gBang = Mix_LoadWAV( "sound effect/Big_Explosion_Cut_Off.mp3" );
	if( gBang == NULL )
	{
		printf( "Failed to load bang sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		//success = false;
	}
	gLay = Mix_LoadWAV( "sound effect/lay_barrel.mp3" );
	if( gLay == NULL )
	{
		printf( "Failed to load lay_barrel sound effect! SDL_mixer Error: %s\n", Mix_GetError() );
		//success = false;
	}
	Mix_PlayChannel( -1, gLay, 0 );
    //owner = player;
    mPosX = player.getPosX();
    mPosY = player.getPosY();
    N++;
    destroy = 0;
    //Render current frame
    currentClip = &gSpriteClips[ 25 ];
    state = setting;
    last_state = sleeping;
    kill = false;
    mWidth = 64;
    mHeight = 64;
    ExploExpand = 100;

    mCollider.x = mPosX;
    mCollider.y = mPosY;
    mCollider.w = mWidth;
    mCollider.h = mHeight;

}

Barrel::~Barrel()
{
    owner = NULL;
    gSpriteSheetTexture.free();
    Mix_FreeChunk( gBang );
	gBang = NULL;
}

void Barrel::explode()
{
    if(state == exploding)
    {
        if(last_state == sleeping)
        {
            //printf("(%d, %d, %d, %d)", mPosX, mPosY, mWidth, mHeight);

            mPosX -= ExploExpand/2;
            mPosY -= ExploExpand/2;
            mWidth += ExploExpand;
            mHeight += ExploExpand;
            //printf("(%d, %d, %d, %d)", mPosX, mPosY, mWidth, mHeight);
            //sound effect
            Mix_PlayChannel( -1, gBang, 0 );
            kill = true;
        }
        else kill = false;

        //show explosion
        if(frame >= 50)
        {
            state = ending;
            //("ending");
        }
        else
        {
            currentClip = &gSpriteClips[ frame /2 ];
            //printf("(%d, %d)", currentClip->x, currentClip->y);
            //printf ("," );
            frame++;
        }
    }
    last_state = state;
}

/*void Barrel::Destroy()
{
    gSpriteSheetTexture.free();
    destroy = true;
}*/

int Barrel::getBarrelN()
{
    return N;
}

int Barrel::getPosX()
{
    return mPosX;
}

int Barrel::getPosY()
{
    return mPosY;
}
void Barrel::render(){
    gSpriteSheetTexture.render( mPosX, mPosY, currentClip );

}


/*bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Load sprite sheet texture
	if( !gSpriteSheetTexture.loadFromFile( "explosion.bmp" ) )
	{
		printf( "Failed to load walking animation texture!\n" );
		success = false;
	}
	else
	{
		//Set sprite clips
		for(int i=0; i<WALKING_ANIMATION_FRAMES-2; i++)
        {
            gSpriteClips[ i ].x = (i%5)*64;
            gSpriteClips[ i ].y = (i%5)*64;
            gSpriteClips[ i ].w =  64;
            gSpriteClips[ i ].h =  64;
        }
        gSpriteClips[ 25 ] = gSpriteClips[ 10 ];

	}

	return success;
}*/

/*void close()
{
	//Free loaded images
	gSpriteSheetTexture.free();

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}*/

/*int MAIN()
{
	//Start up SDL and create window
	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			//Main loop flag
			bool quit = false;

			//Event handler
			SDL_Event e;

			//Current animation frame
			int frame = 0;

			//While application is running
			while( !quit )
			{
				//Handle events on queue
				while( SDL_PollEvent( &e ) != 0 )
				{
					//User requests quit
					if( e.type == SDL_QUIT )
					{
						quit = true;
					}
				}

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				/*Render current frame
				SDL_Rect* currentClip = &gSpriteClips[ frame / 10 ];
				gSpriteSheetTexture.render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

				//Update screen
				SDL_RenderPresent( gRenderer );

				//Go to next frame
				++frame;

				//Cycle animation
				if( frame / 10 >= WALKING_ANIMATION_FRAMES )
				{
					frame = 0;
				}
			}
		}
	}

	//Free resources and close SDL
	close();

	return 0;
}*/

