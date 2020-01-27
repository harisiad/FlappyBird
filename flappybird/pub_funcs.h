#pragma once

#include "Globals.h"
#include "PlayerCS.h"
#include "fb_bitmap.h"
#include "config.h"
#include "SoundManager.h"

void installAddons();
void installSound(SoundManager* target);

bool GetFullscreenValue(const char* c);
void tellTime(ALLEGRO_FONT*,int, Window*);
void drawGameAspects(FbBackground, Player*, std::list<PipeBk *>::iterator, std::list<PipeBk *>,ALLEGRO_FONT*,Window*,int time);
std::string const highscore_string(int);

