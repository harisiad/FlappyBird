#ifndef _FLAPPYBIRD_ENVIRONMENT_GAMEOBJECT_H_
#define _FLAPPYBIRD_ENVIRONMENT_GAMEOBJECT_H_

#include "allegro5\bitmap.h"
#include "fb_window.h"

class GameObject {
	protected:
		float x;
		float y;
		int width;
		int height;

		float velX;
		float velY;

		Window *win;

		ALLEGRO_BITMAP *image;

	public:
		inline void setX(float value) { x = value; };
		inline float getX() { return x; };

		inline void setY(float value) { y = value; };
		inline float getY() { return y; };

		inline void setWidth(int value) { width = value; };
		inline int getWidth() { return width; };
		inline void setHeight(int value) { height = value; };
		inline int getHeight() { return height; };

		inline void setVelX(float value) { velX = value; };
		inline float getVelX() { return velX; };
		inline void setVelY(float value) { velY = value; };
		inline float getVelY() { return velY; };

		inline void setImage(ALLEGRO_BITMAP* img) { image = img; };
		inline ALLEGRO_BITMAP* getImage() { return image; };

		virtual void update() = 0;
		virtual void draw() = 0;
};

#endif