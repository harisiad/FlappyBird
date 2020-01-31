#include "fb_pipes.h"

PipeBk::PipeBk()
{
	x = 0;
	y = 0;
	velX = -1.0;
	velY = 0;

	width = 0;
	height = 0;

	image = (ALLEGRO_BITMAP*)0;

	boundXup = 0;
	boundYup = 0;

	boundXdown = 0;
	boundYdown = 0;

	alive = true;
}
PipeBk::PipeBk(ALLEGRO_BITMAP* img, int w, int h, Window *_win)
{
	x = 0;
	y = 0;
	velX = -3.0;
	velY = 0;

	width = w;
	height = h;

	image = img;

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

void PipeBk::startPipes(Background back, int mul)
{
	x = win->getWidth() + mul * pipeDistance;
	y = win->getHeight() / 4 + (rand() % (int)((win->getHeight() - 2 * win->getHeight() / 5) - win->getHeight() / 4 + 1));
}

void PipeBk::drawPipes()
{
	al_draw_scaled_bitmap(image,
		0, 0,
		width, height,
		x - width / 2, y - boundFreeY - height,
		width, height,
		0);
	al_draw_scaled_bitmap(image,
		0, 0,
		width, height,
		x - width / 2, y + boundFreeY,
		width, height,
		-1);

	if (x < 0 - width - 5)
	{
		alive = false;
	}
}

void PipeBk::updatePipes()
{
	x += velX;
}

void PipeBk::update()
{
	updatePipes();
}

void PipeBk::draw()
{
	drawPipes();
}