#ifndef _FLAPPYBIRD_ENVIRONMENT_PIPES_H_
#define _FLAPPYBIRD_ENVIRONMENT_PIPES_H_

#include "fb_globals.h"
#include "fb_window.h"
#include "fb_game_object.h"
#include "fb_background.h"

class PipeBk : public GameObject {
private:
	float pipeDistance = 250;

	int boundXup;
	int boundYup;
	int boundXdown;
	int boundYdown;

	int boundFreeX;
	int boundFreeY;

	bool alive;
	bool scored;

public:
	PipeBk();
	PipeBk(ALLEGRO_BITMAP*, int, int, Window*);

	inline float getPipeDistance() { return pipeDistance; };

	void setBoundXup(int);
	int getBoundXup();
	void setBoundYup(int);
	int getBoundYup();
	void setBoundXdown(int);
	int getBoundXdown();
	void setBoundYdown(int);
	int getBoundYdown();

	int getBoundFreeX() { return boundFreeX; }
	int getBoundFreeY() { return boundFreeY; }

	void setAlivePipe(bool value) { alive = value; }
	bool getAlivePipe() { return alive; }

	void setScored(bool value) { scored = value; };
	bool getScored() { return scored; };

	void drawPipes();
	void updatePipes();
	void startPipes(Background, int);

	void update();
	void draw();
};

#endif
