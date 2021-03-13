//1024*768
#include <stdlib.h>
#include <SDL2/SDL.h>
#include <SDL2_image/SDL_image.h>
#include <SDL2_ttf/SDL_ttf.h>
#include <SDL2_mixer/SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include<ctime>
#include <iostream>
using namespace std;
 

bool aaa = false;
//Screen dimension constants
const int SCREEN_WIDTH = 1024;
const int SCREEN_HEIGHT = 768;
const int BUTTON_WIDTH = 300;
const int BUTTON_HEIGHT = 200;

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
class LButton
{
  public:
	//Initializes internal variables
	LButton();

	//Sets top left position
	void setPosition(int x, int y);

	//Handles mouse event
	bool handleEvent(SDL_Event *e);

	//Shows button sprite
	void render();

  private:
	//Top left position
	SDL_Point mPosition;
};
LButton::LButton()
{
	mPosition.x = 0;
	mPosition.y = 0;
}

void LButton::setPosition(int x, int y)
{
	mPosition.x = x;
	mPosition.y = y;
}

bool LButton::handleEvent(SDL_Event *e)
{
	
	if (e->type == SDL_MOUSEMOTION || e->type == SDL_MOUSEBUTTONDOWN || e->type == SDL_MOUSEBUTTONUP)
	{
		//Get mouse position
		int x, y;
		SDL_GetMouseState(&x, &y);
		//Check if mouse is in button
		bool inside = true;
		//Mouse is left of the button
		if (x < mPosition.x)
		{
			inside = false;
		}
		//Mouse is right of the button
		else if (x > mPosition.x + BUTTON_WIDTH)
		{
			inside = false;
		}
		//Mouse above the button
		else if (y < mPosition.y)
		{
			inside = false;
		}
		//Mouse below the button
		else if (y > mPosition.y + BUTTON_HEIGHT)
		{
			inside = false;
		}

		//Mouse is outside button
		if (inside)
		{
			//Set mouse over sprite
			switch (e->type)
			{

			case SDL_MOUSEBUTTONDOWN:
				aaa = true;
				break;
			}
		}
	}
}

//Texture wrapper class
class LTexture
{
  public:
	//Initializes variables
	LTexture();
	//Deallocates memory
	~LTexture();
	//Loads image at specified path
	bool loadFromFile(std::string path);
#ifdef _SDL_TTF_H
	//Creates image from font string
	bool loadFromRenderedText(std::string textureText, SDL_Color textColor);
#endif
	//Deallocates texture
	void free();
	//Set color modulation
	void setColor(Uint8 red, Uint8 green, Uint8 blue);
	//Set blending
	void setBlendMode(SDL_BlendMode blending);
	//Set alpha modulation
	void setAlpha(Uint8 alpha);
	//Renders texture at given point
	void render(int x, int y, SDL_Rect *clip = NULL, double angle = 0.0, SDL_Point *center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE);

	//Gets image dimensions
	int getWidth();
	int getHeight();

  private:
	//The actual hardware texture
	SDL_Texture *mTexture;

	//Image dimensions
	int mWidth;
	int mHeight;
};

//init nulls
TTF_Font *gFont = NULL;
Mix_Music *gMusic = NULL;

//The dot that will move around on the screen
class Dot
{
  public:
	//The dimensions of the dot
	static const int DOT_WIDTH = 60;
	static const int DOT_HEIGHT = 40;

	//Maximum axis velocity of the dot
	static const int DOT_VEL = 1;

	//Initializes the variables
	Dot();

	//Takes key presses and adjusts the dot's velocity
	void handleEvent(SDL_Event &e);

	//Moves the dot and checks collision
	void move(SDL_Rect *wall);

	//Shows the dot on the screen
	void render();

  private:
	//The X and Y offsets of the dot
	int mPosX, mPosY;

	//The velocity of the dot
	int mVelX, mVelY;

	//Dot's collision box
	SDL_Rect mCollider;
};

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
LTexture gDotTexture;
LTexture gWindowTexture;
LTexture gTimeTextTexture;
LTexture gPromptTextTexture;
LTexture gPrompt1TextTexture;
LTexture gPrompt2TextTexture;
LTexture gPromptpressTextTexture;
LTexture gPromptKILLATextTexture;
LTexture gPromptkillsTextTexture;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

LTexture::~LTexture()
{
	//Deallocate
	free();
}

bool LTexture::loadFromFile(std::string path)
{
	//Get rid of preexisting texture
	free();

	//The final texture
	SDL_Texture *newTexture = NULL;

	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		//Color key image
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

		//Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		//Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	//Return success
	mTexture = newTexture;
	return mTexture != NULL;
}

#ifdef _SDL_TTF_H
bool LTexture::loadFromRenderedText(std::string textureText, SDL_Color textColor)
{
	//Get rid of preexisting texture
	free();

	//Render text surface
	SDL_Surface *textSurface = TTF_RenderText_Solid(gFont, textureText.c_str(), textColor);
	if (textSurface != NULL)
	{
		//Create texture from surface pixels
		mTexture = SDL_CreateTextureFromSurface(gRenderer, textSurface);
		if (mTexture == NULL)
		{
			printf("Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
		}
		else
		{
			//Get image dimensions
			mWidth = textSurface->w;
			mHeight = textSurface->h;
		}

		//Get rid of old surface
		SDL_FreeSurface(textSurface);
	}
	else
	{
		printf("Unable to render text surface! SDL_ttf Error: %s\n", TTF_GetError());
	}

	//Return success
	return mTexture != NULL;
}
#endif

void LTexture::free()
{
	//Free texture if it exists
	if (mTexture != NULL)
	{
		SDL_DestroyTexture(mTexture);
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
	//Modulate texture rgb
	SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
	//Set blending function
	SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
	//Modulate texture alpha
	SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect *clip, double angle, SDL_Point *center, SDL_RendererFlip flip)
{
	//Set rendering space and render to screen
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};

	//Set clip rendering dimensions
	if (clip != NULL)
	{
		renderQuad.w = clip->w;
		renderQuad.h = clip->h;
	}

	//Render to screen
	SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

Dot::Dot()
{
	//Initialize the offsets
	mPosX = 0;
	mPosY = 0;

	//Set collision box dimension
	mCollider.w = DOT_WIDTH;
	mCollider.h = DOT_HEIGHT;

	//Initialize the velocity
	mVelX = 0;
	mVelY = 0;
}

void Dot::handleEvent(SDL_Event &e)
{
	//If a key was pressed
	if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mVelY -= DOT_VEL;
			break;
		case SDLK_DOWN:
			mVelY += DOT_VEL;
			break;
		case SDLK_LEFT:
			mVelX -= DOT_VEL;
			break;
		case SDLK_RIGHT:
			mVelX += DOT_VEL;
			break;
		}
	}
	//If a key was released
	else if (e.type == SDL_KEYUP && e.key.repeat == 0)
	{
		//Adjust the velocity
		switch (e.key.keysym.sym)
		{
		case SDLK_UP:
			mVelY += DOT_VEL;
			break;
		case SDLK_DOWN:
			mVelY -= DOT_VEL;
			break;
		case SDLK_LEFT:
			mVelX += DOT_VEL;
			break;
		case SDLK_RIGHT:
			mVelX -= DOT_VEL;
			break;
		}
	}
}

void Dot::move(SDL_Rect *wall)
{
	//Move the dot left or right
	mPosX += mVelX;
	mCollider.x = mPosX;

	//If the dot collided or went too far to the left or right
	if ((mPosX < 0) || (mPosX + DOT_WIDTH > SCREEN_WIDTH) || checkCollision(mCollider, wall[0]) || checkCollision(mCollider, wall[1]) || checkCollision(mCollider, wall[2]) || checkCollision(mCollider, wall[1]) || checkCollision(mCollider, wall[2]) || checkCollision(mCollider, wall[3]) || checkCollision(mCollider, wall[4]) || checkCollision(mCollider, wall[5]))

	{
		//Move back
		mPosX -= mVelX;
		mCollider.x = mPosX;
	}

	//Move the dot up or down
	mPosY += mVelY;
	mCollider.y = mPosY;

	//If the dot collided or went too far up or down
	if ((mPosY < 0) || (mPosY + DOT_HEIGHT > SCREEN_HEIGHT) || checkCollision(mCollider, wall[0]) || checkCollision(mCollider, wall[1]) || checkCollision(mCollider, wall[2]) || checkCollision(mCollider, wall[3]) || checkCollision(mCollider, wall[4]) || checkCollision(mCollider, wall[5]))
	{
		//Move back
		mPosY -= mVelY;
		mCollider.y = mPosY;
	}
}

void Dot::render()
{
	//Show the dot
	gDotTexture.render(mPosX, mPosY);
}

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
	gMusic = Mix_LoadMUS( "picture/bgm.mp3" );
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
		
		if (!gPromptTextTexture.loadFromRenderedText("HP", textColor))
		{
			printf("Unable to render gameplay prompt texture!\n");
			success = false;
		}
	}
	if (!gDotTexture.loadFromFile("picture/zombies.png"))
	{
		printf("Failed to load zombies texture!\n");
		success = false;
	}

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
	gMusic = Mix_LoadMUS( "picture/bgm.mp3" );
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
	gDotTexture.free();
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
	gDotTexture.free();
	gWindowTexture.free();
	gPromptTextTexture.free();
	gPrompt1TextTexture.free();
	gPromptkillsTextTexture.free();
	gPrompt2TextTexture.free();

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
				if ((SDL_GetTicks() - startTime)>=6000) break  ;
			  if( !gTimeTextTexture.loadFromRenderedText( timeText.str().c_str(), textColor ) )
				{
					printf( "Unable to render time (for recap) texture!\n" );
				}
				
			  SDL_RenderClear( gRenderer );
			  SDL_Event finale ;

					gWindowTexture.render(NULL,NULL ) ;
                    gTimeTextTexture.render( 512-gTimeTextTexture.getWidth(),0 );
					SDL_RenderPresent( gRenderer );
					SDL_PollEvent(&finale) ;
					switch( finale.key.keysym.sym ){
						 case SDLK_SPACE:  gWindowTexture.free(); gameplay() ; break ;
					}
			}

	
		


		
		close() ; 

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
bool loadText_KILLA(string s)
{
	//Loading success flag
	bool success = true;
	//Open the font
	gFont = TTF_OpenFont("picture/OpenSans-Bold.ttf", 28);
	if (gFont == NULL)
	{
		printf("Failed to load font 724 ! SDL_ttf Error: %s\n", TTF_GetError());
		success = false;
	}
	else
	{
		//Set text color as black
		SDL_Color textColor = {255, 0, 0, 0};

		//Load prompt texture
		if (!gPromptKILLATextTexture.loadFromRenderedText(s, textColor))
		{
			printf("Unable to render prompt texture!\n");
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
// class mana {
// 	public:
// 		mana(int, int) ;
// 		bool check_and_gain() ;

// 	private:
// 		int pos_x ;
// 		int pos_y ;
// 		bool used  ;

// };
// mana::mana(int x,int y){
// 	pos_x =  x  ;
// 	pos_y = y ;
// 	used = false  ;

// }
// mana::check_and_gain(){
// 	if (player collide== true){
// 		if(player.blood>=50){
// 			ammo+=30 ;
// 		}
// 		else {
// 			blood += 50 ;
// 		}
// 		return true ;

// 	}
// 	else return false ;
// }

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

	// string s;
	// stringstream ss;
	// ss << n;
	string str = to_string(n);
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
bool gameplay()
{
	Uint32 startTime = 0;
	static int n = 0;
	static int state  = 0 ;
	std::stringstream timeText;
	loadText_hp();
	loadText_score();
	// loadText_kills(n);
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
		Dot dot;

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
		while (!quit)

		{
			loadText_kills(n++);

			static int time = 0;


			while (SDL_PollEvent(&e) != 0)
			{
				if (e.type == SDL_QUIT)
				{
					quit = true;
				}
				backdoor(e,quit);
				pause(e,state) ; 
				
				dot.handleEvent(e);
			}

	

			dot.move(walls);

			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			
			time = (SDL_GetTicks() - startTime) / 100;

			SDL_Rect blood_line;
			blood_line.x = 0;
			blood_line.y = 0;
			blood_line.w = time;
			blood_line.h = 35;

			gWindowTexture.render(NULL, NULL);
			SDL_SetRenderDrawColor(gRenderer, 0xff, 0x00, 0x00, 0x00);
			SDL_RenderFillRect(gRenderer, &blood_line);
			SDL_RenderDrawRect(gRenderer, &blood_line);
			gPromptTextTexture.render(time - gPromptTextTexture.getWidth(), 0);
			gPrompt1TextTexture.render(700, 0);
			gPromptkillsTextTexture.render(800, 0);

			dot.render();
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
			// Mix_PlayMusic( gMusic, -1) ;
			
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
	recap() ; 
	// gameplay();
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
