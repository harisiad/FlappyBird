#ifndef _FLAPPYBIRD_ENVIRONMENT_PIPES_H_
#define _FLAPPYBIRD_ENVIRONMENT_PIPES_H_

#include "fb_globals.h"
#include "fb_window.h"
#include "fb_game_object.h"
#include "fb_background.h"
#include "MWC_Rand.h"


enum class LEVEL {L0, L1, L2};

class PipeBk : public GameObject {
private:
	float pipeDistance = 150;

	int boundXup;
	int boundYup;
	int boundXdown;
	int boundYdown;

	int boundFreeX;
	int boundFreeY;

	bool alive;
	bool scored;

	// MWC Random Number Generator parameters
	unsigned int seed;
	cmwc_state cmwc;

	LEVEL level = LEVEL::L0;

public:
	PipeBk();
	PipeBk(ALLEGRO_BITMAP*, int, int, Window*);
	~PipeBk();

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
	
	void recalculateY();

	void drawPipes();
	void updatePipes();
	void startPipes(Background, int);

	void update();
	void draw();

	void resetPlay();
};

class Pipe1Level : public PipeBk
{
private:
	LEVEL level = LEVEL::L1;
public:
	Pipe1Level(ALLEGRO_BITMAP*, int, int, Window*);
	void update();
	inline LEVEL getLevel() const { return level; };
};

class Pipe2Level : public PipeBk
{
private:
	LEVEL level = LEVEL::L2;
public:
	Pipe2Level(ALLEGRO_BITMAP*, int, int, Window*);
	void update();
	inline LEVEL getLevel() const { return level; };
};

#endif
