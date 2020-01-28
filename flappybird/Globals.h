#pragma once

#include <stdio.h>
#include <iostream>
#include <string>
#include <sstream>
#include <cstring>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5\allegro_audio.h>
#include <allegro5\allegro_acodec.h>
#include <list>

const int SCREEN_W = 800;
const int SCREEN_H = 600;

const float FPS = 60;

const int PIPE_LIMIT = 8;

const unsigned OK_CODE = 000;

const unsigned ERR_TIMER_LD = 501;
const unsigned ERR_DISPLAY_LD = 502;
const unsigned ERR_EVENTQUEUE_LD = 503;
const unsigned ERR_BACKGROUND_LD = 504;
const unsigned ERR_GROUND_LD = 505;
const unsigned ERR_PIPES_LD = 506;
const unsigned ERR_PLAYERBMP_LD = 507;
const unsigned ERR_GAMEOVERSCREEN_LD = 508;