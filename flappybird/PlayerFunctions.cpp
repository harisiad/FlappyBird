#include "PlayerCS.h"

using namespace std;

Player::Player(ALLEGRO_BITMAP* image)
{
	x = SCREEN_W / 5;
	y = SCREEN_H / 2;
	velX = 0;
	velY = 6;
	gravity = 0.35;
	rotation = 0;

	boundX = 10;
	boundY = 10;

	maxframe = 4;
	currframe = 0;
	framecount = 0;
	framedelay = 4;
	framewidth = 48;
	frameheight = 35;
	animationColumns = 1;
	animationDirection = 1;

	animationRow = 0;

	score = 0;
	highscore = 0;
	gameOver = false;
	godMode = false;

	if (image != NULL){
		Player::image = image;
	}
}

void Player::Destroy(){}

void Player::updatePlayer()
{
	if (y < 5)
	{
		y = 10;
	}
	else 
	{
		velY -= gravity;
		y += -velY;
	}
	if (++framecount >= framedelay)
	{
		currframe += animationDirection;
		if (currframe >= maxframe)
		{
			currframe = 0;
		}
		else if (currframe <= 0)
		{
			currframe = 4;
		}
		framecount = 0;
	}
}
void Player::gravityPull(int groundHeight)
{
	rotation -= 5.0;
	
	if (y + boundY >= groundHeight) 
	{
		y = groundHeight - boundY;
		Player::setGameOver();
	}
	if (rotation <= -90.0) 
	{
		rotation = -90.0;
	}
}
void Player::drawPlayer()
{
	int animationFrameX = (currframe % animationColumns) * framewidth;
	int animationFrameY = (currframe / animationColumns) * frameheight;

	al_draw_bitmap_region(image,
	animationFrameX, animationFrameY,
	framewidth, frameheight,
	x - framewidth / 2, y - frameheight / 2, 0);
	
}

void Player::gainHeight()
{
	animationRow = 1;
	velY = 6;
	rotation += 10.0;
	if (rotation >= 10.0)
	{ 
		rotation = 10.0; 
	}
}

void Player::resetAnimation()
{
	animationRow = 0;
}

bool Player::collidePipes(PipeBk* pipe, GroundBk ground, Window *win)
{

	if (x + boundX > pipe->getX() - pipe->getBoundXup() &&
		y + boundY > pipe->getY() - pipe->getBoundFreeY() - pipe->getBoundYup() &&
		x - boundX < pipe->getX() + pipe->getBoundXup() &&
		y - boundY < pipe->getY() - pipe->getBoundFreeY())
	{
		return true;
	} 
	if (x + boundX > pipe->getX() - pipe->getBoundXdown() &&
		y + boundY > pipe->getY() + pipe->getBoundFreeY() &&
		x - boundX < pipe->getX() + pipe->getBoundXdown() &&
		y - boundY < pipe->getY() + pipe->getBoundFreeY() + 2*pipe->getBoundYdown()) 
	{
		return true;
	}

	return false;
}

bool Player::passMark(PipeBk* pipes)
{
	if (((x - framewidth / 2) + boundX == pipes->getX() + 30)    &&
		(((y - frameheight / 2) - boundY >= pipes->getY() - 120) || 
		((y - frameheight / 2) + boundY <= pipes->getY() + 120))) 
	{

		return true;
	}

	return false;
}

bool Player::collideGround(GroundBk ground)
{
	return false;
}