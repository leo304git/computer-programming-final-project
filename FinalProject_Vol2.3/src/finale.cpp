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
#include<ctime>
#include <iostream>
using namespace std;


bool aaa = false;
//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;
WeaponManager manager;
int timer(int n , int &k ){
    clock_t  t1 ;
	t1 =  clock() ;
	clock_t t2 ;
	while(true){
		t2 = clock () ;
		if (((t2 - t1)/CLOCKS_PER_SEC)>n){
			k=1 ;
		}

	}

}


//init nulls
TTF_Font *gFont = NULL;
Mix_Music *gMusic = NULL;



//Starts up SDL and creates window
bool init();
//Loads media
bool loadMedia();
//Frees media and shuts down SDL
void close();
void close_game();
//Box collision detector
bool checkCollision(SDL_Rect a, SDL_Rect b);
//The window we'll be rendering to
SDL_Window *gWindow = NULL;
//The window renderer
SDL_Renderer *gRenderer = NULL;

//Scene textures
//LTexture gDotTexture;
LTexture gWindowTexture;
LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
LTexture gPromptplayer2TextTexture;
LTexture gPrompt1TextTexture;
LTexture gPrompt2TextTexture;
LTexture gPromptpressTextTexture;
LTexture gPromptKILLSTextTexture;
LTexture gPromptkillsTextTexture;
LTexture gPromptammoTextTexture;
LTexture gPromptAMMOTextTexture;
LTexture gPrompDeathTextTexture;




bool init()
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not initialize( for init)! SDL Error: %s\n", SDL_GetError());
		success = false;
	}
	else
	{
		//Set texture filtering to linear
		if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
		{
			printf("Warning: Linear texture filtering not enabled!");
		}

		//Create window
		gWindow = SDL_CreateWindow("EEHEAD", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created(EEHEAD LOGO FOR INIT)! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			//Create vsynced renderer for window
			gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
			if (gRenderer == NULL)
			{
				printf("Renderer could not be created(for init)! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				//Initialize renderer color
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize (for init)! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
			}
			if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize (for init)! SDL_mixer Error: %s\n", Mix_GetError() );
					success = false;
				}

		}



	}
	return success;
}


bool loadMedia_gameplay()
{
	bool success = true;
	gMusic = Mix_LoadMUS( "sound effect/BGM.mp3" );
	if( gMusic == NULL )
	{
		printf( "Failed to load music(for music)! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize(for gameplay)! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load gameplay 498 font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 0, 255};

		if (!gPromptTextTexture.loadFromRenderedText("HP1", textColor))
		{
			printf("Unable to render gameplay prompt texture!\n");
			success = false;
		}
		if (!  gPromptplayer2TextTexture.loadFromRenderedText("HP2", textColor))
        {
            printf("Unable to render gameplay prompt texture!\n");
            success = false;
        }
	}

	/*if (!gDotTexture.loadFromFile("picture/zombies.png"))
	{
		printf("Failed to load zombies texture!\n");
		success = false;
	}*/

	if (!gWindowTexture.loadFromFile("picture/aaa.png"))
	{
		printf("Failed to load gameplay\n");
		success = false;
	}

	return success;
}
bool loadMedia1()
{

	bool success = true;
	gMusic = Mix_LoadMUS( "sound effect/BGM.mp3" );
	if( gMusic == NULL )
	{
		printf( "Failed to loadMEDIA1 music! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	if (TTF_Init() == -1)
	{
		printf("SDL_ttf could not initialize! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}

	if (!gWindowTexture.loadFromFile("picture/intro.png"))
	{
		printf("Failed to load intro\n");
		success = false;
	}


	return success;
}
bool loadMedia_instructions( string s)
{
	//Loading success flag
	bool success = true ;

	if( gMusic == NULL )
	{
		printf( "Failed to load killanyte music(load_media_instructions string s)! SDL_mixer Error: %s\n", Mix_GetError() );
		success = false;
	}

	if( TTF_Init() == -1 )
	{
		printf( "SDL_ttf could not initialize(for genreral load_media_instructions string s )! SDL_ttf Error: %s\n", TTF_GetError() );
		success = false;
	}

    if( !gWindowTexture.loadFromFile(s) )
	{
		printf( "Failed to load media files (string input) cute\n" );
		success = false;
	}

	return success;
}
void close()
{
	//Free loaded images
	//gDotTexture.free();
	gWindowTexture.free();
    gTimeTextTexture.free();
	gPromptTextTexture.free();
	gPrompt1TextTexture.free();

	//Free global font


	Mix_FreeMusic( gMusic );
	gMusic = NULL;


	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	TTF_Quit();
	Mix_Quit();
	IMG_Quit();
	SDL_Quit();
}

void close_game()
{
	//Free loaded images
	//gDotTexture.free();
	gWindowTexture.free();
	gPromptTextTexture.free();
	gPrompt1TextTexture.free();
	gPromptplayer2TextTexture.free();
	gPromptkillsTextTexture.free();
	gPrompt2TextTexture.free();
	gPromptKILLSTextTexture.free();
	gPromptammoTextTexture.free();
	gPromptAMMOTextTexture.free();


	//Free global font
	TTF_CloseFont(gFont);
	gFont = NULL;
	// quit music ;
	Mix_FreeMusic( gMusic );
	gMusic = NULL;

	//Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;

	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	SDL_Quit();
}
void close_gamea()
{
	//Free loaded images

	gWindowTexture.free();
	gPromptTextTexture.free();
	gPrompt1TextTexture.free();
	gPromptplayer2TextTexture.free();
	gPromptkillsTextTexture.free();
	gPrompt2TextTexture.free();
	gPromptKILLSTextTexture.free();
	gPromptammoTextTexture.free();
	gPromptAMMOTextTexture.free();


	//Free global font
	/*TTF_CloseFont(gFont);
	gFont = NULL;
	// quit music ;
	Mix_FreeMusic( gMusic );
	gMusic = NULL;
    //Destroy window
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	gRenderer = NULL;


	//Quit SDL subsystems
	Mix_Quit();
	TTF_Quit();
	IMG_Quit();
	//SDL_Quit();*/

}
bool checkCollision(SDL_Rect a, SDL_Rect b)
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
	if (bottomA <= topB)
	{
		return false;
	}

	if (topA >= bottomB)
	{
		return false;
	}

	if (rightA <= leftB)
	{
		return false;
	}

	if (leftA >= rightB)
	{
		return false;
	}

	return true;
}
bool gameplay();
bool intro() ;
bool recap()
{

	Uint32 startTime = SDL_GetTicks();
	std::stringstream timeText;
	SDL_Color textColor = { 255,255,255,255  };

	if (!loadMedia_instructions("picture/recap.png"))
	{
		printf("Failed to load recap!\n");
	}
	else{


			 while(true){
				timeText.str( "" );
				timeText << "closing in " << 6 -(SDL_GetTicks() - startTime)/1000; ;
				if ((SDL_GetTicks() - startTime)>=6000) close_game()  ;
			  if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time (for recap) texture!\n" );
				}

			  SDL_RenderClear( gRenderer );
			  SDL_Event finale ;

					gWindowTexture.render(NULL,NULL ) ;
                    gTimeTextTexture.render( 512-gTimeTextTexture.getWidth(),0 );
                    gPrompDeathTextTexture.render( 512-gPrompDeathTextTexture.getWidth(),600 );
					SDL_RenderPresent( gRenderer );

					SDL_PollEvent(&finale) ;

            }
		close_game() ;

	}
}
bool backdoor(SDL_Event k ,  bool &quit)
{
	if (k.type == SDL_KEYDOWN)
	{
		if (k.key.keysym.sym == SDLK_ESCAPE)
		{
			close_game();
			quit = true ;
		}
	}
}
int pause (SDL_Event k, int &state )
{
	if (k.type == SDL_KEYDOWN)
	{
		if (k.key.keysym.sym == SDLK_p)
		{
			if(state ==1 ){
				state = 0 ;
			}
			else state = 1;
		}
	}
}
bool loadText_hp2()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load font 698 ! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 255, 0};

		//Load prompt texture
		if (!gPrompt1TextTexture.loadFromRenderedText("Hp2", textColor))
		{
			printf("Unable to render prompt(hp) texture!\n");
			success = false;
		}
	}
	return success;
}
bool loadText_hp()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load font 698 ! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 255, 0};

		//Load prompt texture
		if (!gPrompt1TextTexture.loadFromRenderedText("Hp", textColor))
		{
			printf("Unable to render prompt(hp) texture!\n");
			success = false;
		}
	}
	return success;
}

bool loadText_press()
{
	//Loading success flag
	bool success = true;

	//Open the font
	gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 14);
	if (gFont == NULL)
	{
		printf("Failed to load font 724 ! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{

		SDL_Color textColor = {0, 0, 0, 255};

		if (!gPromptpressTextTexture.loadFromRenderedText("click to procede", textColor))
		{
			printf("Unable to render prompt (click to procede )texture!\n");
			success = false;
		}
	}
	return success;
}




bool loadText_score()
{
	bool success = true;
	gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load 750 font! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
	SDL_Color textColor = {0, 0, 0, 255};
	if (!gPrompt1TextTexture.loadFromRenderedText("score", textColor))
	{
		printf("Unable to render prompt(for score) texture!\n");
		success = false;
	}
	}
	return success;
}
bool loadText_kills(int n)
{
	// Loading success flag
	bool success = true;

	string s;
	stringstream ss;
	ss << n;
    string str = ss.str();
	//std::string str = std::to_string(n);
	// Open the font
	if (gFont == NULL)
	{
		gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
		if (gFont == NULL) printf("Failed to load 779 font! SDL_ttf Error: %s\n", TTF_GetError());
		// success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 0, 255};

		//Load prompt texture
		if (!gPromptkillsTextTexture.loadFromRenderedText(str, textColor))
		{
			printf("Unable to render prompt kills texture!\n");
			success = false;
		}
	}
	return success;
}
bool loadText_KILLS(int n)
{
	// Loading success flag
	bool success = true;

	string s;
	stringstream ss;
	ss << n;
    string str = ss.str();
	//std::string str = std::to_string(n);
	// Open the font
	if (gFont == NULL)
	{
		gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
		if (gFont == NULL) printf("Failed to load 779 font! SDL_ttf Error: %s\n", TTF_GetError());
		// success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 0, 255};

		//Load prompt texture
		if (!gPromptKILLSTextTexture.loadFromRenderedText(str, textColor))
		{
			printf("Unable to render prompt kills texture!\n");
			success = false;
		}
	}
	return success;
}
bool loadText_ammo(int n)
{
	// Loading success flag
	bool success = true;

	string s;
	stringstream ss;
	ss << n;
    string str = ss.str();
	//std::string str = std::to_string(n);
	// Open the font
	if (gFont == NULL)
	{
		gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
		if (gFont == NULL) printf("Failed to load 779 font! SDL_ttf Error: %s\n", TTF_GetError());
		// success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 0, 255};

		//Load prompt texture
		if (!gPromptammoTextTexture.loadFromRenderedText(str, textColor))
		{
			printf("Unable to render prompt kills texture!\n");
			success = false;
		}
	}
	return success;
}
bool loadText_AMMO(int n)
{
	// Loading success flag
	bool success = true;

	string s;
	stringstream ss;
	ss << n;
    string str = ss.str();
	//std::string str = std::to_string(n);
	// Open the font
	if (gFont == NULL)
	{
		gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
		if (gFont == NULL) printf("Failed to load 779 font! SDL_ttf Error: %s\n", TTF_GetError());
		// success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 0, 255};

		//Load prompt texture
		if (!gPromptAMMOTextTexture.loadFromRenderedText(str, textColor))
		{
			printf("Unable to render prompt KILLS texture!\n");

		}
	}
	return success;
}
bool loadText_death()
{
	// Loading success flag
	bool success = true;
	int n = 0 ;
	if(  manager.PlayerPointer[0]->getBlood()==0){
        n=1 ;
	}
	else n= 2 ;
	string s;
	stringstream ss;

	ss << n ;
	string str = "PLAYER" ;
    str += ss.str();
    str+="DIES";
	//std::string str = std::to_string(n);
	// Open the font
	if (gFont == NULL)
	{
		gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 40);
		if (gFont == NULL) printf("Failed to load 779 font! SDL_ttf Error: %s\n", TTF_GetError());
		// success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {0, 0, 0, 255};

		//Load prompt texture
		if (!gPrompDeathTextTexture.loadFromRenderedText(str, textColor))
		{
			printf("Unable to render prompt death texture!\n");
			success = false;
		}
	}
	return success;
}


bool gameplay()
{
    Uint32 startTime = SDL_GetTicks();
	static int n = 0;

	int mana_cnt = 0 ;
	int a = 0;
	static int state  = 0 ;
	int player_one_health = 100 ;
    int player_two_health = 100 ;
	std::stringstream timeText;
	loadText_hp();
	loadText_score();
	loadText_kills(n);
	// loadText_KILLA(n );

	SDL_Color textColor = {0, 0, 0, 255};
	if (!loadMedia_gameplay())
	{
		printf("Failed to load media!(for gameplay )\n");
	}
	else
	{
		bool quit = false;
		SDL_Event e;
		SDL_Color textColor = {0, 0, 0, 255};
		Uint32 startTime = 0;
		stringstream timeText;
		//Dot dot;

		SDL_Rect walls[6];
		walls[0].x = SCREEN_WIDTH / 2 - 312 - 100;
		walls[0].y = SCREEN_HEIGHT / 2 - 350 + 50;
		walls[0].w = 200;
		walls[0].h = 100;

		walls[1].x = SCREEN_WIDTH / 2 + 312 - 100;
		walls[1].y = SCREEN_HEIGHT / 2 - 350 + 50;
		walls[1].w = 200;
		walls[1].h = 100;

		walls[2].x = SCREEN_WIDTH / 2 - 312 - 100 + 150;
		walls[2].y = SCREEN_HEIGHT / 2 - 150 + 50;
		walls[2].w = 200;
		walls[2].h = 100;

		walls[3].x = SCREEN_WIDTH / 2 + 312 - 100 - 150;
		walls[3].y = SCREEN_HEIGHT / 2 - 150 + 50;
		walls[3].w = 200;
		walls[3].h = 100;

		walls[4].x = SCREEN_WIDTH / 2 - 312 - 100;
		walls[4].y = SCREEN_HEIGHT / 2 + 100;
		walls[4].w = 200;
		walls[4].h = 100;

		walls[5].x = SCREEN_WIDTH / 2 + 312 - 100;
		walls[5].y = SCREEN_HEIGHT / 2 + 100;
		walls[5].w = 200;
		walls[5].h = 100;


        manager.setPlayer();
        manager.setZombie();

		while (!quit)

		{
			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				backdoor(e,quit);
				pause(e,state) ;

				manager.handlePlayer(e);
			}

			 if(SDL_GetTicks()-startTime>=6000){
                if(mana_cnt ==0 ){
                    mana_cnt++  ;
                    manager.setMana();

                }

                startTime = SDL_GetTicks() ;
            }



			manager.movePlayer(walls);
            manager.moveZombie(walls);


            if(mana_cnt==1)
            {
                if(manager.manageMana())
                {
                    mana_cnt=0;
                }
            }
            manager.manageBullet();

            manager.manageBarrel();

            manager.checkPlaSup();

            manager.checkPlaDie();

            manager.checkZomDie();

            manager.setZombie();

            if (manager.checkPlaDie())
                {

                    recap() ;
                }

            loadText_kills(manager.showScore1());
            loadText_KILLS(manager.showScore2()) ;

            loadText_ammo(manager.PlayerPointer[0]->weaponAmmo[manager.PlayerPointer[0]->weaponType]);
            loadText_AMMO(manager.PlayerPointer[1]->weaponAmmo[manager.PlayerPointer[1]->weaponType]);


			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);



            player_one_health = manager.PlayerPointer[0]->getBlood();
            player_two_health = manager.PlayerPointer[1]->getBlood();
			SDL_Rect blood_line;
			blood_line.x = 0;
			blood_line.y = 0;
			blood_line.w = manager.PlayerPointer[0]->getBlood() / 2;
			blood_line.h = 35;

			SDL_Rect blood_line2;
			blood_line2.x = 0;
			blood_line2.y = 35;
			blood_line2.w = manager.PlayerPointer[1]->getBlood() / 2;
			blood_line2.h = 35;



			gWindowTexture.render(NULL, NULL);
			SDL_SetRenderDrawColor(gRenderer, 0x00, 0xff, 0x00, 0x00);
			SDL_RenderFillRect(gRenderer, &blood_line);
			SDL_RenderDrawRect(gRenderer, &blood_line);
			SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0x00);
            SDL_RenderFillRect(gRenderer, &blood_line2);
            SDL_RenderDrawRect(gRenderer, &blood_line2);

            gPromptTextTexture.render(blood_line.w - gPromptTextTexture.getWidth(), 0);
            gPromptplayer2TextTexture.render(blood_line2.w - gPromptplayer2TextTexture.getWidth(), 35);

			gPrompt1TextTexture.render(700, 0);
            gPrompt1TextTexture.render(700, 35);

			gPromptkillsTextTexture.render(800, 0);
			gPromptKILLSTextTexture.render(800, 35);

			gPromptammoTextTexture.render(600, 0);
			gPromptAMMOTextTexture.render(600, 35);


			manager.showBullet();
            manager.showBarrel();
            manager.showPlayer();
            manager.showZombie();
            if (mana_cnt==1) manager.showMana() ;



			if (state==0){SDL_RenderPresent(gRenderer);}

		}
	}


}
bool instructions2()
{
	loadText_press();
	SDL_Color textColor = {0, 0, 0, 255};
	LButton button;
	button.setPosition(0, 0);
	SDL_Rect a;
	a.x = 0;
	a.y = 0;
	a.w = 100;
	a.h = 100;
	if (!loadMedia_instructions("picture/instruction2.png"))
	{
		printf("Failed to load media instructions2 !\n");
	}
	else
	{
		if (TTF_Init() == -1)
		{
			printf("SDL_ttf could not initialize for instructions2! SDL_ttf Error: %s\n", TTF_GetError());
		}
		int next_state = 0;
		while (next_state == 0)
		{
			SDL_RenderClear(gRenderer);
			SDL_Event event;
			gWindowTexture.render(NULL, NULL);
			SDL_RenderDrawRect(gRenderer, &a);
			gPromptpressTextTexture.render(0, 0);


			SDL_RenderPresent(gRenderer);

			SDL_PollEvent(&event);
			button.handleEvent(&event);
			if (aaa == true)
			{
				next_state = 1;
				gWindowTexture.free();
				break;
			}
		}
	}
	aaa = false;
	//recap();
	gameplay();
}

bool instructions()
{
	loadText_press();
	SDL_Color textColor = {0, 0, 0, 255};
	LButton button;

	button.setPosition(0, 0);
	SDL_Rect a;
	a.x = 0;
	a.y = 0;
	a.w = 100;
	a.h = 100;
	if (!loadMedia_instructions("picture/instruction1.png"))
	{
		printf("Failed to load media for instructions!\n");
	}
	else
	{
		int next_state = 0;
		while (next_state == 0)
		{
			SDL_RenderClear(gRenderer);
			SDL_Event event;
			gWindowTexture.render(NULL, NULL);
			SDL_RenderDrawRect(gRenderer, &a);
			Mix_PlayMusic( gMusic, -1) ;
			gPromptpressTextTexture.render(0, 0);
			SDL_RenderPresent(gRenderer);

			SDL_PollEvent(&event);
			// switch( event.key.keysym.sym ){
			// 	 case SDLK_0:  next_state=1;gWindowTexture.free();    break;
			// }
			button.handleEvent(&event);
			if (aaa == true)
			{
				next_state = 1;
				gWindowTexture.free();
				break;
			}
		}
	}
	aaa = false;
	instructions2();
}

bool intro()
{

	if (!init())
	{
		printf("Failed to initialize (in intro)!\n");
	}
	else
	{

		if (!loadMedia1())
		{
			printf("Failed to load media1 (in intro)!\n");
		}
		else
		{
			int next_state = 0;
			while (next_state == 0)
			{
				SDL_RenderClear(gRenderer);
				SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				SDL_Event event;
				gWindowTexture.render(NULL, NULL);
				Mix_PlayMusic( gMusic, -1 );
				SDL_RenderPresent(gRenderer);
				SDL_PollEvent(&event);
				switch (event.key.keysym.sym)
				{
				case SDLK_SPACE:
					next_state = 1;
					gWindowTexture.free();
					break;
				}
			}
		}
		instructions();
	}
}
int main(int argc, char *args[])
{

	intro();

	return 0;
}
