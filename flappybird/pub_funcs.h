#pragma once

#include "fb_globals.h"
#include "player.h"
#include "fb_bitmap.h"
#include "config.h"
#include "sound_manager.h"

struct GameData
{
	ALLEGRO_CONFIG *config = (ALLEGRO_CONFIG*)0;							//CONFIGURATION ALLEGRO VAR
	ALLEGRO_DISPLAY *display = (ALLEGRO_DISPLAY*)0;							//DISPLAY ALLEGRO VAR
	ALLEGRO_EVENT_QUEUE *event_queue = (ALLEGRO_EVENT_QUEUE*)0;				//EVENT QUEUE ALLEGRO VAR
	ALLEGRO_TIMER *timer = (ALLEGRO_TIMER*)0;								//ALLEGRO TIMER VAR
	ALLEGRO_BITMAP *background = (ALLEGRO_BITMAP*)0;						//ALLEGRO BITMAP BACKGROUND
	ALLEGRO_BITMAP *ground = (ALLEGRO_BITMAP*)0;							//ALLEGRO BITMAP GROUND
	ALLEGRO_BITMAP *pipes = (ALLEGRO_BITMAP*)0;								//ALLEGRO BITMAP PIPES
	ALLEGRO_BITMAP *playerBmp = (ALLEGRO_BITMAP*)0;							//ALLEGRO BITMAP FLAPPY
	ALLEGRO_BITMAP *gameOverScreen = (ALLEGRO_BITMAP*)0;					//ALLEGRO BITMAP GAMEOVER DISPLAY
	ALLEGRO_FONT *font = (ALLEGRO_FONT*)0;									//ALLEGRO FONT FOR SCORE HIGHSCORE
	ALLEGRO_FONT *gameOverFont = (ALLEGRO_FONT*)0;							//ALLEGRO GAMEOVER SCORE DISPLAY
	unsigned code = 000;
};

GameData InitializeGameData(GameData data, ConfigAPI* config);
void DestroyGameData(GameData data);

void installAddons();
void installSound(SoundManager* target);

bool GetFullscreenValue(const char* c);
void tellTime(ALLEGRO_FONT*,int, Window*);
void drawGameAspects(FbBackground, Player*, std::list<PipeBk *>::iterator, std::list<PipeBk *>,ALLEGRO_FONT*,Window*,int time, bool debugMode);
std::string const highscore_string(int);

