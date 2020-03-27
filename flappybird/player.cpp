#include "player.h"

using namespace std;

Player::Player(ALLEGRO_BITMAP* image) :
	x(SCREEN_W / 5),
	y(SCREEN_H / 3),
	velX(0),
	velY(6.0f),
	gravity(0.35),
	rotation(0.0f),
	boundX(11),
	boundY(11),
	maxframe(4),
	currframe(0),
	framecount(0),
	framedelay(4),
	framewidth(48),
	frameheight(35),
	animationColumns(1),
	animationDirection(1),
	animationRow(0),
	score(0),
	highscore(0),
	gameOver(false),
	godMode(false)
{
	if (image != NULL)
	{
		Player::image = new ALLEGRO_BITMAP*[maxframe];
		for (int i = currframe; i < maxframe; i++)
		{
			Player::image[i] = al_create_sub_bitmap(image,
				(i % animationColumns) * framewidth,
				(i / animationColumns) * frameheight,
				framewidth,
				frameheight);
		}
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
	if (velY > 0)
	{
		if (rotation > 0.0f)
		{
			rotation = 0.0f;
		}
		rotation -= .02f;
		if (rotation < -.1f)
		{
			rotation = -.1f;
		}
	}
	else if (velY < 0)
	{
		rotation += .015f;
		if (rotation > .5f)
			rotation = .5f;
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
	al_draw_scaled_rotated_bitmap(
		image[currframe],
		framewidth / 2,
		frameheight / 2,
		x,
		y,
		1,
		1,
		rotation,
		0
	);
}

void Player::gainHeight()
{
	animationRow = 1;
	velY = 6.0f;
}

void Player::resetAnimation()
{
	animationRow = 0;
}

bool Player::collidePipes(PipeBk* pipe) const
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
	rotation = 0.0f;

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