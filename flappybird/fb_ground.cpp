#include "fb_ground.h"

GroundBk::GroundBk()
{
	x = 0;
	y = SCREEN_H - 50;
	velX = -1.0;
	velY = 0;

	image = (ALLEGRO_BITMAP*)0;

	boundx = SCREEN_W;
	boundy = 0;
}

GroundBk::GroundBk(ALLEGRO_BITMAP* img, int w, int h, Window *_win)
{
	win = _win;

	x = 0;
	y = win->getHeight() - 50;

	velX = -1.0;
	velY = 0;

	width = w;
	height = h;

	image = img;
	
	boundx = SCREEN_W;
	boundy = height;
}

void GroundBk::setBoundX(int x)
{
	boundx = x;
}
int GroundBk::getBoundX()
{
	return boundx;
}
void GroundBk::setBoundY(int y)
{
	boundy = y;
}
int GroundBk::getBoundY()
{
	return boundy;
}

void GroundBk::update() 
{
	x += velX;
	if (x + width <= 0)
	{
		x = 0;
	}
}

void GroundBk::draw()
{
	drawGround();
}

void GroundBk::drawGround()
{
	al_draw_scaled_bitmap(image, 0, 0,
		al_get_bitmap_width(image),
		al_get_bitmap_height(image),
		x, y,
		win->getWidth(), al_get_bitmap_height(image), 0);

	if (x + width < SCREEN_W)
	{
		al_draw_scaled_bitmap(image, 0, 0,
			al_get_bitmap_width(image),
			al_get_bitmap_height(image),
			x + width, y,
			win->getWidth(), al_get_bitmap_height(image), 0);
	}
}

bool GroundBk::groundCollision(int x, int y)
{
	return false;
}


void GroundBk::resetPlay()
{
	x = 0;
}