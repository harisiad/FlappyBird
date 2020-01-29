#include "fb_pipes.h"

PipeBk::PipeBk()
{
	x = 0;
	y = 0;
	velX = -1.0;
	velY = 0;

	bgwidth = 0;
	bgheight = 0;

	bg = (ALLEGRO_BITMAP*)0;

	boundXup = 0;
	boundYup = 0;

	boundXdown = 0;
	boundYdown = 0;

	alive = true;
}
PipeBk::PipeBk(ALLEGRO_BITMAP* image, int width, int height, Window *_win)
{
	x = 0;
	y = 0;
	velX = -3.0;
	velY = 0;

	bgwidth = width;
	bgheight = height;

	bg = image;

	win = _win;

	boundXup = 27;
	boundYup = height;

	boundXdown = 27;
	boundYdown = height;

	boundFreeX = 20;
	boundFreeY = 50;

	alive = true;
}

void PipeBk::setBoundXup(int x)
{
	boundXup = x;
}
int PipeBk::getBoundXup()
{
	return boundXup;
}
void PipeBk::setBoundYup(int y)
{
	boundYup = y;
}
int PipeBk::getBoundYup()
{
	return boundYup;
}

void PipeBk::setBoundXdown(int x)
{
	boundXdown = x;
}
int PipeBk::getBoundXdown()
{
	return boundXdown;
}
void PipeBk::setBoundYdown(int y)
{
	boundYdown = y;
}
int PipeBk::getBoundYdown()
{
	return boundYdown;
}

void PipeBk::startPipes(FbBackground back, int mul)
{
	x = win->getWidth() + mul * 300;
	y = win->getHeight() / 4 + (rand() % (int)((win->getHeight() - 2 * win->getHeight() / 5) - win->getHeight() / 4 + 1));
}

void PipeBk::drawPipes()
{
	al_draw_scaled_bitmap(bg,
		0, 0,
		bgwidth, bgheight,
		x - bgwidth / 2, y - boundFreeY - bgheight,
		bgwidth, bgheight,
		0);
	al_draw_scaled_bitmap(bg,
		0, 0,
		bgwidth, bgheight,
		x - bgwidth / 2, y + boundFreeY,
		bgwidth, bgheight,
		-1);

	if (x < 0 - bgwidth - 5)
	{
		alive = false;
	}
}

void PipeBk::updatePipes()
{
	x += velX;
}

bool PipeBk::groundCollision(int x, int y)
{
	return false;
}