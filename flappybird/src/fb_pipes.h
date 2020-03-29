#ifndef _FLAPPYBIRD_ENVIRONMENT_PIPES_H_
#define _FLAPPYBIRD_ENVIRONMENT_PIPES_H_

#include "fb_globals.h"
#include "fb_window.h"
#include "fb_game_object.h"
#include "MWC_Rand.h"


enum class LEVEL {L0, L1, L2, L3};

class PipeBk : public GameObject {
private:
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

	LEVEL level = LEVEL::L0;
protected:
	float pipeDistance = 125;
	
	cmwc_state cmwc;

public:
	PipeBk();
	PipeBk(ALLEGRO_BITMAP*, int, int, Window*);
	~PipeBk();

	inline float getPipeDistance() const { return pipeDistance; };

	void setBoundXup(int);
	int getBoundXup();
	void setBoundYup(int);
	int getBoundYup();
	void setBoundXdown(int);
	int getBoundXdown();
	void setBoundYdown(int);
	int getBoundYdown();

	inline void setBoundFreeY(int value) { boundFreeY = value; }

	inline int getBoundFreeX() const { return boundFreeX; }
	inline int getBoundFreeY() const { return boundFreeY; }

	inline void setAlivePipe(bool value) { alive = value; }
	inline bool getAlivePipe() const { return alive; }

	void setScored(bool value) { scored = value; };
	inline bool getScored() const { return scored; };
	
	void recalculateY();

	void drawPipes();
	void updatePipes();
	virtual void startPipes(int, int);

	void update();
	virtual void draw();

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
	void setYAxisVel();
	inline LEVEL getLevel() const { return level; };
};

class Pipe3Level : public PipeBk
{
private:
	LEVEL level = LEVEL::L3;
public:
	Pipe3Level(ALLEGRO_BITMAP*, int, int, Window*);
	void setYAxisVel();
	void drawPipes();
	void startPipes(int, int) override;
	
	// Game Object Interface
	void draw();
	void update();
	inline LEVEL getLevel() const { return level; };
};

#endif
