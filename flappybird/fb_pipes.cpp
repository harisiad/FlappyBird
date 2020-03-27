#include "fb_pipes.h"
#include <math.h>

# define M_PIl          3.141592653589793238462643383279502884L

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
	scored = false;

	seed = 0;
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
	scored = false;

	seed = rand32();
	initCMWC(&cmwc, seed);
}

PipeBk::~PipeBk()
{
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

void PipeBk::startPipes(int size, int lastPipePosition)
{
	x = width + lastPipePosition + pipeDistance;

	// y = minimum possible location + rand() % maximum interval
	// y => min - (max interval + min)
	y = win->getHeight() / 5 + (randCMWC(&cmwc) % (int)(win->getHeight() / 2));
}



void PipeBk::recalculateY()
{
	// y = minimum possible location + rand() % maximum interval
	// y => min - (max interval + min)
	y = win->getHeight() / 5 + (randCMWC(&cmwc) % (int)(win->getHeight()/2));
}

void PipeBk::drawPipes()
{
	static int ALLEGRO_NO_FLIP = 0;

	al_draw_scaled_bitmap(image,
		0, 0,
		width, height,
		x - width / 2, y - boundFreeY - height,
		width, height,
		ALLEGRO_NO_FLIP);

	al_draw_scaled_bitmap(image,
		0, 0,
		width, height,
		x - width / 2, y + boundFreeY,
		width, height,
		ALLEGRO_FLIP_VERTICAL);

	if (x < 0 - width - 5)
	{
		alive = false;
	}
}

void PipeBk::updatePipes()
{
	x += velX;
	y += velY;
}

void PipeBk::update()
{
	//updatePipes();
}

void PipeBk::draw()
{
	drawPipes();
}

void PipeBk::resetPlay()
{
	x = 0;
	y = 0;
}

Pipe1Level::Pipe1Level(ALLEGRO_BITMAP* img, int w, int h, Window* _win) : 
	PipeBk(img, w, h, _win), level(LEVEL::L1) {}

void Pipe1Level::update()
{
	x += velX;
}

Pipe2Level::Pipe2Level(ALLEGRO_BITMAP* img, int w, int h, Window* _win) : 
	PipeBk(img, w, h, _win), level(LEVEL::L2) {}

void Pipe2Level::setYAxisVel()
{
	float topPipeLoc = y - getBoundFreeY();
	float bottomPipeLoc = y + getBoundFreeY();

	if (velY == 0)
	{
		if (topPipeLoc >= win->getHeight() / 5 - 30 &&
			topPipeLoc <= win->getHeight() / 2)
		{
			velY = 1.0f;
		}
		else if (topPipeLoc < win->getHeight() / 5 - 30)
		{
			velY = 1.0f;
		}
		else if (bottomPipeLoc <= 4 * win->getHeight() / 5 &&
			bottomPipeLoc >= win->getHeight() / 2)
		{
			velY = -1.0f;
		}
		else if (bottomPipeLoc > 4 * win->getHeight() / 5)
		{
			velY = -1.0f;
		}
	}

	if (topPipeLoc >= win->getHeight() / 5 - 30 &&
		topPipeLoc <= win->getHeight() / 5 - 25)
	{
		velY = 1.0f;
	}
	else if (bottomPipeLoc <= 4 * win->getHeight() / 5 &&
		bottomPipeLoc >= 4 * win->getHeight() / 5 - 5)
	{
		velY = -1.0f;
	}
}

void Pipe2Level::update()
{
	setYAxisVel();

	x += velX;
	y += velY;
}


Pipe3Level::Pipe3Level(ALLEGRO_BITMAP* img, int w, int h, Window* _win)
	: PipeBk(img, w, h, _win) 
{
	setBoundFreeY(65);	// For bigger space between pipes
}

void Pipe3Level::setYAxisVel()
{
	float topPipeLoc = y - getBoundFreeY();
	float bottomPipeLoc = y + getBoundFreeY();

	if (velY == 0)
	{
		if (topPipeLoc >= win->getHeight() / 5 - 30 &&
			topPipeLoc <= win->getHeight() / 2)
		{
			velY = 1.0f;
		}
		else if (topPipeLoc < win->getHeight() / 5 - 30)
		{
			velY = 1.0f;
		}
		else if (bottomPipeLoc <= 4 * win->getHeight() / 5 &&
			bottomPipeLoc >= win->getHeight() / 2)
		{
			velY = -1.0f;
		}
		else if (bottomPipeLoc > 4 * win->getHeight() / 5)
		{
			velY = -1.0f;
		}
	}

	if (topPipeLoc >= win->getHeight() / 5 - 30 &&
		topPipeLoc <= win->getHeight() / 5 - 25)
	{
		velY = 1.0f;
	}
	else if (bottomPipeLoc <= 4 * win->getHeight() / 5 &&
		bottomPipeLoc >= 4 * win->getHeight() / 5 - 5)
	{
		velY = -1.0f;
	}
}

void Pipe3Level::update()
{
	setYAxisVel();
	
	x += velX;
	//y += velY;
}

void Pipe3Level::drawPipes()
{
	static int ALLEGRO_NO_FLIP = 0;

	al_draw_scaled_bitmap(image,
		0, 0,
		width, height,
		x - width / 2, y - getBoundFreeY() - height,
		width, height,
		ALLEGRO_NO_FLIP);

	al_draw_scaled_bitmap(image,
		0, 0,
		width, height,
		x - width / 2, y + getBoundFreeY(),
		width, height,
		ALLEGRO_FLIP_VERTICAL);

	if (x < 0 - width - 5)
	{
		setAlivePipe(false);
	}
}

void Pipe3Level::draw()
{
	drawPipes();
}

void Pipe3Level::startPipes(int size, int lastPipePosition)
{
	if (size % 6 == 0)
	{
		x = width + lastPipePosition + pipeDistance;
	}
	else
	{
		x = width + lastPipePosition;
	}
	
	// y = minimum possible location + rand() % maximum interval
	// y => min - (max interval + min)
	y = win->getHeight() / 2 + 32*cos((lastPipePosition * win->getHeight() / 5) * M_PIl / 180);
}
