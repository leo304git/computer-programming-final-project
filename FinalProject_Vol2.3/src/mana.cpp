#include "mana.h"

mana::mana(int x,int y){
	posX =  x  ;
	posY = y ;
	used = false  ;
    if (!gManaTexture.loadFromFile("picture/mana.png"))
	{
		printf("Failed to load mana texture!\n");

	}
	mCollider.h = manaHeight;
	mCollider.w = manaWidth;
    mCollider.x = posX;
    mCollider.y = posY;
}
void mana::render(){

	gManaTexture.render(posX,posY);

}


mana::~mana()
{
    //dtor
    gManaTexture.free();
}
