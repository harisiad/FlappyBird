#include "fb_background.h"

Background::Background(){
	x = 0;
	y = 0;
	velX = -0.3;
	velY = 0;

	image = (ALLEGRO_BITMAP*)0;

	win = new Window();
}

Background::Background(ALLEGRO_BITMAP* img,int w, int h, Window *_win){
	x = 0;
	y = 0;
	velX = -0.3;
	velY = 0;

	width = w;
	height = h;
	
	image = img;

	win = _win;
}

void Background::update()
{
	updateBackground();
}

void Background::draw()
{
	drawBackground();
}

void Background::updateBackground(){
	x += velX;
	if (x + width <= 0){
		x = 0;
	}
}

void Background::drawBackground(){
	al_draw_scaled_bitmap(image, 0, 0, 
		al_get_bitmap_width(image),
		al_get_bitmap_height(image),
		x,y,
		al_get_bitmap_width(image), win->getHeight(), 0);

	if (x + width < SCREEN_W){
		al_draw_scaled_bitmap(image, 0, 0, 
			al_get_bitmap_width(image),
			al_get_bitmap_height(image),
			x + width, y,
			al_get_bitmap_width(image), win->getHeight(), 0);
	}
}