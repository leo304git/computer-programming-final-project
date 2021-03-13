#ifndef GLOBAL
#define GLOBAL

#include <SDL2/SDL.h>
#include <SDL_image.h>
#include <SDL2/SDL_ttf.h>
//#define WALKING_ANIMATION_FRAMES 26
extern SDL_Window* gWindow ;
extern SDL_Renderer* gRenderer;
extern const int SCREEN_WIDTH;  //640
extern const int SCREEN_HEIGHT; //480
extern bool checkCollision( SDL_Rect a, SDL_Rect b );
extern TTF_Font *gFont;
extern const int BUTTON_WIDTH ;
extern const int BUTTON_HEIGHT ;
extern bool aaa;
extern SDL_Rect walls[6];
//extern LTexture gDotTexture;
//extern LTexture gSpriteSheetTexture;
//extern const int WALKING_ANIMATION_FRAMES;
//extern SDL_Rect gSpriteClips[ WALKING_ANIMATION_FRAMES ];
#endif
