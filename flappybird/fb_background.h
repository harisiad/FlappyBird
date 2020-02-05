#ifndef _FLAPPYBIRD_ENVIRONMENT_BITMAP_H_
#define _FLAPPYBIRD_ENVIRONMENT_BITMAP_H_

#include "fb_globals.h"
#include "fb_window.h"
#include "fb_game_object.h"

class Background : public GameObject {
	public:
		Background();
		Background(ALLEGRO_BITMAP*,int,int,Window*);

		void update();
		void draw();

		void updateBackground();
		void drawBackground();

		void resetPlay();
};

#endif