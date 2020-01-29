#include "fb_bitmap.h"

FbBackground::FbBackground(){
	x = 0;
	y = 0;
	velX = -0.3;
	velY = 0;

	bg = (ALLEGRO_BITMAP*)0;

	win = new Window();
}

FbBackground::FbBackground(ALLEGRO_BITMAP* image,int width, int height, Window *_win){
	x = 0;
	y = 0;
	velX = -0.3;
	velY = 0;

	bgwidth = width;
	bgheight = height;
	
	bg = image;

	win = _win;
}

void FbBackground::setX(int x){
	FbBackground::x = x;
}
float FbBackground::getX(){
	return FbBackground::x;
}
void FbBackground::setvelX(float x){
	velX = x;
}
float FbBackground::getvelX(){
	return velX;
}

void FbBackground::setY(float diry){
	y = diry;
}
float FbBackground::getY(){ return y; }
void FbBackground::setvelY(float){}
float FbBackground::getvelY(){ return velY; }

void FbBackground::setBgWidth(int width){
	bgwidth = width;
}
int FbBackground::getBgWidth(){
	return bgwidth;
}
void FbBackground::setBgHeight(int height){
	bgheight = height;
}
int FbBackground::getBgHeight(){
	return bgheight;
}

void FbBackground::setImage(ALLEGRO_BITMAP* image){
	bg = image;
}
ALLEGRO_BITMAP* FbBackground::getImage(){
	return bg;
}

void FbBackground::updateBackground(){
	x += velX;
	if (x + bgwidth <= 0){
		x = 0;
	}
}
void FbBackground::drawBackground(){
	al_draw_scaled_bitmap(bg, 0, 0, 
		al_get_bitmap_width(bg),
		al_get_bitmap_height(bg),
		x,y,
		al_get_bitmap_width(bg), win->getHeight(), 0);

	if (x + bgwidth < SCREEN_W){
		al_draw_scaled_bitmap(bg, 0, 0, 
			al_get_bitmap_width(bg),
			al_get_bitmap_height(bg),
			x + bgwidth, y,
			al_get_bitmap_width(bg), win->getHeight(), 0);
	}
}