#include "fb_ground.h"

GroundBk::GroundBk()
{
	x = 0;
	y = SCREEN_H - 50;
	velX = -1.0;
	velY = 0;

	bg = (ALLEGRO_BITMAP*)0;

	boundx = SCREEN_W;
	boundy = 0;
}

GroundBk::GroundBk(ALLEGRO_BITMAP* image, int width, int height, Window *_win)
{
	x = 0;

	velX = -1.0;
	velY = 0;

	bgwidth = width;
	bgheight = height;

	bg = image;

	win = _win;

	y = win->getHeight() - 50;

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

void GroundBk::drawGround()
{
	al_draw_scaled_bitmap(bg, 0, 0,
		al_get_bitmap_width(bg),
		al_get_bitmap_height(bg),
		x, y,
		win->getWidth(), al_get_bitmap_height(bg), 0);

	if (x + bgwidth < SCREEN_W)
	{
		al_draw_scaled_bitmap(bg, 0, 0,
			al_get_bitmap_width(bg),
			al_get_bitmap_height(bg),
			x + bgwidth, y,
			win->getWidth(), al_get_bitmap_height(bg), 0);
	}
}

bool GroundBk::groundCollision(int x, int y)
{
	return false;
}
