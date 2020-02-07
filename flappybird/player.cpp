#include "player.h"

using namespace std;

Player::Player(ALLEGRO_BITMAP* image)
{
	x = SCREEN_W / 5;
	y = SCREEN_H / 3;
	velX = 0;
	velY = 6.0f;
	gravity = 0.35;
	rotation = 0;

	boundX = 11;
	boundY = 11;

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
		y = 5;
	}
	else 
	{
		velY -= gravity;
		y += -velY;
	}

	updateSpriteAnimation();
}

void Player::updateSpriteAnimation()
{
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

bool Player::gravityPull(int groundHeight)
{
	if (y + boundY >= groundHeight)
	{
		y = groundHeight - boundY;
		return true;
	}

	return false;
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
	velY = 6.0f;
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

bool Player::collidePipes(PipeBk* pipe)
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

bool Player::passMark(PipeBk* pipe)
{
	if (!pipe->getScored() &&
		!collidePipes(pipe) && 
		(x - framewidth / 2) >= pipe->getX() - pipe->getBoundFreeX() && 
		(x - framewidth / 2) <= pipe->getX() + pipe->getBoundFreeX())
	{
		return true;
	}

	return false;
}

bool Player::collideGround(GroundBk ground)
{
	return false;
}

void Player::resetPlayer()
{
	x = SCREEN_W / 5;
	y = SCREEN_H / 3;

	velY = 6.0f;
	
	currframe = 0;

	score = 0;
	gameOver = false;
	godMode = false;
}

void Player::resetGravity()
{
	gravity = 0.35;
}