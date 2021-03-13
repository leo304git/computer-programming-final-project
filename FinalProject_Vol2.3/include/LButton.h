#ifndef LBUTTON_H
#define LBUTTON_H
#include <SDL2/SDL.h>
#include "Global.h"

class LButton
{
    public:
        //Initializes internal variables
        LButton();
        virtual ~LButton();
		//Sets top left position
		void setPosition( int x, int y );

		//Handles mouse event
		bool handleEvent( SDL_Event* e );

		//Shows button sprite
		void render();


    protected:

    private:
        //Top left position
		SDL_Point mPosition;
};

#endif // LBUTTON_H
