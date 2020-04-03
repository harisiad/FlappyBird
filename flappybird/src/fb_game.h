#ifndef _FLAPPYBIRD_GAME_H_
#define _FLAPPYBIRD_GAME_H_

#include "fb_game_acts.h"
#include "fb_window.h"
#include "config.h"
#include "sound_manager.h"
#include "fb_background.h"
#include "player.h"
#include "fb_pipes.h"

#include <vector>

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
	ALLEGRO_BITMAP *godMod = (ALLEGRO_BITMAP*)0;							//ALLEGRO BITMAP REPLAY BUTTON
	ALLEGRO_BITMAP* godModPressed = (ALLEGRO_BITMAP*)0;
	ALLEGRO_BITMAP* buffer = (ALLEGRO_BITMAP*)0;
	ALLEGRO_FONT *font = (ALLEGRO_FONT*)0;									//ALLEGRO FONT FOR SCORE HIGHSCORE
	ALLEGRO_FONT *debugFont = (ALLEGRO_FONT*)0;
	ALLEGRO_FONT *gameOverFont = (ALLEGRO_FONT*)0;							//ALLEGRO GAMEOVER SCORE DISPLAY
	double fpsTimeCounter;
	unsigned code = 000;
};
struct GameModes
{
	bool running;
	bool redraw;
	bool pause;
	bool debug;
};
struct Scene
{
	Background bg;
	GroundBk groundbk;
	PipeBk* bg_pipes;
	Player* player;
};
enum Stages {StartMenu, CountDown, MainGame, GameOver};
enum PipeState {Update, LevelFaze};

class FBGame : public Acts
{
	protected:
		GameData gameData;
		GameModes gameModes;
		Scene scene;
		ConfigAPI *configData;
		Window *displayWindow = new Window();
		SoundManager *soundManager = new SoundManager();

		int pipeCount = pipeList.size();
		float gameTime = 0.0f;

		float secondsPassed;

		int currentStage = Stages::StartMenu;
		int pipeState = PipeState::Update;

		//std::list<PipeBk *> pipeList;
		std::vector<PipeBk*> pipeList;
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

		void TellTime();

		bool GetFullscreenValue(const char* c);
		
		void DrawGameAspects();
		void DrawGodMode();
		void DrawMainGame();
		void DrawDebugMode(PipeBk&);
		void DrawCountDownTimer(int countDown);
		void DrawStartMenu();
		void DrawExitGame();
		void DrawStartGame();
		void DrawGameTitle();
		void DrawGameOverReplay();

		void CountDown();
		void MainGame();

		void DifficultyStateMachine(bool& isMoved);

		void GeneratePipes();

		void ActsPlayLoop();
		void ActsProgramme();
		void PauseAct();
		void CheatTheGame();
		void DebugAct();
		void OpenCurtains();
		void CloseCurtains();
		void ResetPlay();
};

#endif