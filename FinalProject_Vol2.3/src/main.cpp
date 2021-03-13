#include "LTexture.h"
#include "Humanoid.h"
#include "Player.h"
#include "Zombie.h"
#include "Barrel_test.h"
#include<ctime>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "Global.h"
#include "WeaponManager.h"


//Screen dimension constants
const int SCREEN_WIDTH = 960;  //640
const int SCREEN_HEIGHT = 540; //480

TTF_Font *gFont = NULL;

//public:
//Starts up SDL and creates window
bool init();

//Loads media
bool loadMedia();

//Frees media and shuts down SDL
void close();

//Box collision detector
bool checkCollision( SDL_Rect a, SDL_Rect b );


//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//The window renderer
SDL_Renderer* gRenderer = NULL;

//Scene textures
//LTexture gDotTexture;
LTexture gWindowTexture ;
LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
//LTexture gSpriteSheetTexture;

//SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];

bool init()
{
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Set texture filtering to linear
        if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
        {
            printf( "Warning: Linear texture filtering not enabled!" );
        }

        //Create window
        gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create vsynced renderer for window
            gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
            if( gRenderer == NULL )
            {
                printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize renderer color
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

                //Initialize PNG loading
                int imgFlags = IMG_INIT_PNG;
                if( !( IMG_Init( imgFlags ) & imgFlags ) )
                {
                    printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
                    success = false;
                }
            }
        }
    }

    return success;
}

bool loadMedia()
{
	//Loading success flag
	bool success = true;

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	// now we open the font
	gFont = TTF_OpenFont( "./picture/lazy.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };

		//Load prompt texture
		if( !gPromptTextTexture.loadFromRenderedText( "TINTIN is sitting next to me.", textColor ) )
		{
			printf( "Unable to render prompt texture!\n" );
			success = false;
		}

	}
	//Load press texture

	/*if( !gDotTexture.loadFromFile("picture/dot.bmp") )
	{
		printf( "Failed to load dot texture!\n" );
		success = false;
	}*/
	/*gWindowTexture.loadFromFile("picture/small-mario.png") ;
    if( !gWindowTexture.loadFromFile("picture/small-mario.png") )
	{
		printf( "Failed to load mario\n" );
		success = false;
	}*/

	//Load sprite sheet texture


	return success;
}


void close()
{
	//Free loaded images
	//gDotTexture.free();
    gWindowTexture.free() ;
	gTimeTextTexture.free();
	gPromptTextTexture.free();


	//Free global font
	TTF_CloseFont( gFont );
	gFont = NULL;

	//Destroy window
	SDL_DestroyRenderer( gRenderer );
	SDL_DestroyWindow( gWindow );
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}

bool checkCollision( SDL_Rect a, SDL_Rect b )
{
    //The sides of the rectangles
    int leftA, leftB;
    int rightA, rightB;
    int topA, topB;
    int bottomA, bottomB;

    //Calculate the sides of rect A
    leftA = a.x;
    rightA = a.x + a.w;
    topA = a.y;
    bottomA = a.y + a.h;

    //Calculate the sides of rect B
    leftB = b.x;
    rightB = b.x + b.w;
    topB = b.y;
    bottomB = b.y + b.h;

    //If any of the sides from A are outside of B
    if( bottomA <= topB )
    {
        return false;
    }

    if( topA >= bottomB )
    {
        return false;
    }

    if( rightA <= leftB )
    {
        return false;
    }

    if( leftA >= rightB )
    {
        return false;
    }

    //If none of the sides from A are outside B
    return true;
}


int main( int argc, char* args[] )
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

            // the start of the age
			SDL_Color textColor = { 0, 0, 0, 255 };
			Uint32 startTime = 0;
			std::stringstream timeText;


			//The dot that will be moving around on the screen
			//Dot dot;

            WeaponManager manager;
			SDL_Rect walls[3];
			walls[0].x = 300;
			walls[0].y = 40;
			walls[0].w = 40;
			walls[0].h = 30;

			walls[1].x = 150;
			walls[1].y = 400;
			walls[1].w = 15;
			walls[1].h = 40;
			walls[2].x = 340;
			walls[2].y = 190;
			walls[2].w = 15;
			walls[2].h = 40;
			walls[1].x = 150;
			walls[1].y = 400;
			walls[1].w = 15;
			walls[1].h = 40;


            //call player
            //Player player(0, 50, 0);
            manager.setPlayer();


            //Barrel* BarrelPointer[100]={NULL};
            //int BarrelNumber = 0;

            //Bullet* BulletPointer[100]={NULL};
           // int BulletNumber = 0;
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
                    manager.handlePlayer(e);

                }

                int health  =3 ;
				//Set text to be rendered
				timeText.str( "" );
				 timeText << "stanley is so  sexy " << SDL_GetTicks() - startTime;
				timeText << "player 1 HP" << health ;

				//Render text

				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}
                //move the player
                manager.movePlayer(walls);

                manager.manageBullet();

                manager.manageBarrel();
                /*if(player.LayBarrel&&Barrel::counter<100)
                {
                    bool stoplay=0;
                    for(int i=0; i<100; i++) if(BarrelPointer[i])
                    {
                        if(abs(BarrelPointer[i]->getPosX()-player.getPosX())<40&&abs(BarrelPointer[i]->getPosY()-player.getPosY())<40)
                        {
                            stoplay=1;
                        }
                    }
                    if(!stoplay){
                        if(BarrelNumber >= 100)
                        {
                            BarrelNumber = 0;
                        }
                        while(BarrelPointer[BarrelNumber] != NULL)
                        {
                                BarrelNumber++;
                                if(BarrelNumber >= 100) BarrelNumber = 0;
                        }
                        BarrelPointer[BarrelNumber] = new Barrel(player);
                        BarrelNumber++;
                    }
                }
                for(int i=0; i<100; i++) if(BarrelPointer[i])
                {
                    if(BarrelPointer[i]->destroy == true)
                    {
                        delete BarrelPointer[i];
                    }
                }*/
//Bullet比照辦理,寫在WeaponManager內
                SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
                SDL_RenderClear( gRenderer );
                //Render wall
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderDrawRect( gRenderer, &walls[0] );
				SDL_RenderDrawRect( gRenderer, &walls[1] );
				SDL_RenderDrawRect( gRenderer, &walls[2] );


				/*for(int i=0;i<100;i++)if(BarrelPointer[i])
                {
                    BarrelPointer[i]->render();
                }*/
                manager.showBullet();
                manager.showBarrel();


				gWindowTexture.render(NULL,NULL );
                //player.render();
                manager.showPlayer();
				gPromptTextTexture.render( 0, 0 );
				gTimeTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) / 2, ( SCREEN_HEIGHT - gPromptTextTexture.getHeight() ) / 2 );

                SDL_RenderPresent( gRenderer );

            }
        }
    }

    //Player player(0,0,0)
    close();

    return 0;
}




//// Build Settings -> Search Path -> Headers search path -> /usr/local/include
//// Build Settings -> Search Path -> Library search path -> /usr/local/lib
//// Ohter Linker Llags -> -lSDL_bgi
//
//// g++ [檔案名].cpp -F /Liåbrary/Frameworks -framework SDL2 -lSDL_bgi -o [自訂名稱]
//// ./[執行檔名稱]
