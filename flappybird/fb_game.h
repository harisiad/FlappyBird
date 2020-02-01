#ifndef _FLAPPYBIRD_GAME_H_
#define _FLAPPYBIRD_GAME_H_

#include "fb_game_acts.h"
#include "fb_window.h"
#include "config.h"
#include "sound_manager.h"
#include "fb_background.h"
#include "player.h"
#include "fb_pipes.h"

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
struct GameModes
{
	bool running;
	bool redraw;
	bool pause;
	bool debug;
};

class FBGame : public Acts
{
	protected:
		GameData gameData;
		GameModes gameModes;
		ConfigAPI *configData;
		Window *displayWindow = new Window();
		SoundManager *soundManager = new SoundManager();

		enum FLAP { UP };
		bool FLAPS[1] = { false };
		int pipeCount = 0;

		std::list<PipeBk *> pipeList;
		std::list<PipeBk *>::iterator pipeI;

	public:
		FBGame();
		~FBGame();

		void InitializeWindow();
		void InitializeGameData();
		void InstallAddons();
		void InstallSound();
		void RegisterEventSources();

		void DestroyGameData();

		void TellTime(ALLEGRO_FONT*, int, Window*);
		void DrawGameAspects(Background, Player*, std::list<PipeBk *>::iterator, std::list<PipeBk *>, ALLEGRO_FONT*, Window*, int time, bool debugMode);

		bool GetFullscreenValue(const char* c);

		void ActsPlayLoop();
		void ActsProgramme();
		void PauseAct();
		void CheatTheGame();
		void DebugAct();
		void OpenCurtains();
		void CloseCurtains();
};

#endif