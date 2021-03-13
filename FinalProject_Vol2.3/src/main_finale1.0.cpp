//1024*768
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include "LButton.h"
#include "Global.h"
#include "WeaponManager.h"
using namespace std;


bool aaa = false  ;
//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;





// the start of timing module ;

TTF_Font *gFont = NULL;

//The dot that will move around on the screen

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
LTexture gWindowTexture ;
LTexture gTimeTextTexture;
LTexture gPromptTextTexture;


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
		gWindow = SDL_CreateWindow( "EEHEAD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
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
				//Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}
			}
		}
	}
	return success;
}
void get_text_and_rect(SDL_Renderer *renderer, int x, int y, char *text,
        TTF_Font *font, SDL_Texture **texture, SDL_Rect *rect) {
    int text_width;
    int text_height;
    SDL_Surface *surface;
    SDL_Color textColor = {255, 255, 255, 0};

    surface = TTF_RenderText_Solid(font, text, textColor);
    *texture = SDL_CreateTextureFromSurface(renderer, surface);
    text_width = surface->w;
    text_height = surface->h;
    SDL_FreeSurface(surface);
    rect->x = x;
    rect->y = y;
    rect->w = text_width;
    rect->h = text_height;
}


bool loadMedia_gameplay()
{
	bool success = true;
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

	gFont = TTF_OpenFont( "picture/OpenSans-Bold.ttf", 28 );
	if( gFont == NULL )
	{
		printf( "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = { 0, 0, 0, 255 };
		// //Load prompt texture
		// if( !gPromptTextTexture.loadFromRenderedText( "HP", textColor ) )
		// {
		// 	printf( "Unable to render prompt texture!\n" );
		// 	success = false;
		// }

	}
	/*if( !gDotTexture.loadFromFile("picture/zombies.png") )
	{
		printf( "Failed to load zombies texture!\n" );
		success = false;
	}*/

    if( !gWindowTexture.loadFromFile("picture/aaa.png") )
	{
		printf( "Failed to load gameplay\n" );
		success = false;
	}
	return success;
}
bool loadMedia1()
{
	//Loading success flag
	bool success = true;
	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    if( !gWindowTexture.loadFromFile("picture/intro.png") )
	{
		printf( "Failed to load intro\n" );
		success = false;
	}
	return success;
}
bool loadMedia_instructions( string s)
{
	//Loading success flag
	bool success = true;

	//Initialize SDL_ttf
	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    if( !gWindowTexture.loadFromFile(s) )
	{
		printf( "Failed to load cute\n" );
		success = false;
	}
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
	Mix_Quit();
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

    return true;
}
bool gameplay (){


		if( !loadMedia_gameplay() )
		{
			printf( "Failed to load media!\n" );
		}
		else
		{
			bool quit = false;
			SDL_Event e;
			SDL_Color textColor = { 0, 0, 0, 255 };
			Uint32 startTime = 0;
			std::stringstream timeText;
			SDL_Rect walls[6];

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

			WeaponManager manager;
			manager.setPlayer();
			manager.setZombie();

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
					//Handle input for
					manager.handlePlayer(e);
				}

				timeText.str( "" );
				timeText << "time elapsed " << SDL_GetTicks() - startTime;


				// Render text

				if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time texture!\n" );
				}

				//Move the dot and check collision
				manager.movePlayer(walls);
				manager.moveZombie(walls);

                manager.manageBullet();

                manager.manageBarrel();

                manager.checkPlaDie();

                manager.checkZomDie();

				//Clear screen
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );
				SDL_RenderClear( gRenderer );

				//Render wall
				SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF );
				SDL_RenderDrawRect( gRenderer, &walls[0] );
				SDL_RenderDrawRect( gRenderer, &walls[1] );
				SDL_RenderDrawRect( gRenderer, &walls[2] );
                SDL_RenderDrawRect( gRenderer, &walls[3] );
				SDL_RenderDrawRect( gRenderer, &walls[4] );
				SDL_RenderDrawRect( gRenderer, &walls[5] );


				//Render dot
				gWindowTexture.render(NULL,NULL );
				manager.showBullet();
                manager.showBarrel();
				manager.showPlayer();
				manager.showZombie();
				gPromptTextTexture.render( 0, 0 );
				gTimeTextTexture.render( ( SCREEN_WIDTH - gPromptTextTexture.getWidth() ) ,  0 );
				SDL_RenderPresent( gRenderer );
			}
		}

	//Free resources and close SDL
	close();
}
bool instructions2(){
		// Load media
        LButton  button;
        button.setPosition( 0, 0 ) ;
         SDL_Rect a;
			a.x = 0;
			a.y = 0;
			a.w = 100;
			a.h = 100;
		if( !loadMedia_instructions("picture/instructions2.png") )
		{
			printf( "Failed to load media!\n" );
		}
		else{
			int next_state = 0 ;
			while(next_state==0){
				SDL_RenderClear( gRenderer );
				//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				 	SDL_Event event ;
					gWindowTexture.render(NULL,NULL ) ;
					SDL_RenderDrawRect( gRenderer, &a );
					SDL_RenderPresent( gRenderer );

					 SDL_PollEvent(&event) ;
                    button.handleEvent(&event) ;
                    if(aaa == true ){
                        next_state= 1 ;
                        gWindowTexture.free();
                        break;

                    }
				}
			}
            aaa= false;
             gameplay() ;

	}

bool instructions(){

        LButton  button;
        button.setPosition( 0, 0 ) ;
         SDL_Rect a;
			a.x = 0;
			a.y = 0;
			a.w = 100;
			a.h = 100;
		if( !loadMedia_instructions("picture/instructions1.png") )
		{
			printf( "Failed to load media!\n" );
		}
		else{
			int next_state = 0 ;
			while(next_state==0){
				SDL_RenderClear( gRenderer );
				//SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				 	SDL_Event event ;
					gWindowTexture.render(NULL,NULL ) ;
					SDL_RenderDrawRect( gRenderer, &a );
					SDL_RenderPresent( gRenderer );

					 SDL_PollEvent(&event) ;
					// switch( event.key.keysym.sym ){
					// 	 case SDLK_0:  next_state=1;gWindowTexture.free();    break;
					// }
                    button.handleEvent(&event) ;
                    if(aaa == true ){
                        next_state= 1 ;
                        gWindowTexture.free();
                        break;

                    }


				}
			}
            aaa= false;
            instructions2() ;
	}
bool intro( ){

	//Start up SDL and create window

	if( !init() )
	{
		printf( "Failed to initialize!\n" );
	}
	else
	{
		//Load media
		if( !loadMedia1() )
		{
			printf( "Failed to load media!\n" );
		}
		else{
			int next_state = 0 ;
			while(next_state==0){
				SDL_RenderClear( gRenderer );
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				 	SDL_Event event ;
                    // set_text("dickhead",0,0) ;
					gWindowTexture.render(NULL,NULL ) ;
					SDL_RenderPresent( gRenderer );
					SDL_PollEvent(&event) ;
					switch( event.key.keysym.sym ){
						 case SDLK_SPACE:  next_state=1;gWindowTexture.free();    break;
					}
				}



			}
            instructions();

	}
}
int main( int argc, char* args[] ){
	intro() ;
	return 0 ;
}
