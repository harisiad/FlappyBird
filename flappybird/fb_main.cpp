#include "fb_globals.h"

#include "fb_background.h"
#include "player.h"
#include "config.h"
#include "pub_funcs.h"
#include "sound_manager.h"
#include "fb_ground.h"
#include "fb_pipes.h"

using namespace std;

enum FLAP { UP };
bool FLAPS[1] = { false };

list<PipeBk *> pipeList;
list<PipeBk *>::iterator pipeI;

int main(int argc, char **argv)
{
	ALLEGRO_CONFIG *config = (ALLEGRO_CONFIG*)0;							//CONFIGURATION ALLEGRO VAR

	GameData gameData;

	bool redraw = true;
	bool isPaused = false;
	bool done = false;
	bool debugMode = false;

	float gameTime = 0;

	int pcount = 0;

	ConfigAPI *configData;													//CONFIGURATION CLASS
	Window *displayWindow = new Window();									//DISPLAY CLASS
	SoundManager *soundManager = new SoundManager();

	config = al_load_config_file("config_file.cfg");
	configData = new ConfigAPI(
		atoi(al_get_config_value(config, NULL, "WIDTH")),
		atoi(al_get_config_value(config, NULL, "HEIGHT")),
		GetFullscreenValue(al_get_config_value(config, NULL, "FULLSCREEN")),
		stof(al_get_config_value(config, "GameSettings", "DIFFICULT")),
		atoi(al_get_config_value(config, "GameSettings", "HIGHSCORE")));

	displayWindow->init(configData->WinWidth(), configData->WinHeight(), configData->WinFullscreen());

	if (!al_init()) 
	{
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	gameData = InitializeGameData(gameData, configData);
	if (gameData.code != 000)
	{
		DestroyGameData(gameData);
		return -1;
	}

	installSound(soundManager);

	Background bg(gameData.background, al_get_bitmap_width(gameData.background), displayWindow->getHeight(),displayWindow);
	GroundBk groundbk(gameData.ground, al_get_bitmap_width(gameData.ground), al_get_bitmap_height(gameData.ground), displayWindow);
	PipeBk *bg_pipes = new PipeBk();
	Player *player = new Player(gameData.playerBmp);

	player->setHighscore(configData->GetHighScore());

	RegisterEventSources(gameData);

	al_start_timer(gameData.timer);
	gameTime = al_current_time();

	soundManager->playThemeSong();

	while (!done) 
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(gameData.event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) 
		{
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode) 
			{
				case ALLEGRO_KEY_P:
				{
					if (isPaused)
					{
						isPaused = false;
					}
					else 
					{
						isPaused = true;
					}
					break;
				}
				case ALLEGRO_KEY_G:
				{
					if (player->getGodMode())
					{
						player->setGodModeOff();
					}
					else 
					{
						player->setGodModeOn();
					}
					break;
				}
				case ALLEGRO_KEY_D:
				{
					if (!debugMode)
					{
						debugMode = true;
					}
					else
					{
						debugMode = false;
					}
				}
				case ALLEGRO_KEY_ESCAPE:
					break;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				if (!player->isGameOver())
				{
					soundManager->playFlapSound();
					player->gainHeight();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ev.mouse.button & 1)
			{
				if (!player->isGameOver())
				{
					//player->resetAnimation();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) 
		{
			isPaused = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) 
		{
			isPaused = false;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (!player->isGameOver())
			{
				if (!isPaused)
				{
					player->updatePlayer();
					player->gravityPull(groundbk.getY());

					bg.update();

					groundbk.update();

					gameTime = al_current_time();

					if (pcount < 10)
					{
						bg_pipes = new PipeBk(gameData.pipes, al_get_bitmap_width(gameData.pipes), al_get_bitmap_height(gameData.pipes),displayWindow);
						pipeList.push_back(bg_pipes);
						bg_pipes->startPipes(bg, pcount++);
					}

					for (pipeI = pipeList.begin(); pipeI != pipeList.end(); ++pipeI)
					{

						if (player->collidePipes((*pipeI), groundbk, displayWindow) && (!player->getGodMode()))
						{
							soundManager->playCollisionSound();
							player->setGameOver();
						}

						if (player->passMark((*pipeI)))
						{
							soundManager->playSuccessSound();
							player->addScore();
						}

						if ((*pipeI)->getX() < -(*pipeI)->getWidth())
						{
							PipeBk* firstPipe = pipeList.front();
							PipeBk* lastPipe = pipeList.back();

							firstPipe->setX(lastPipe->getX() + 300);
							pipeI = pipeList.erase(pipeI);
							pipeList.push_back(firstPipe);
						}
						else
						{
							(*pipeI)->updatePipes();
						}
					}
				}
			}
			
			redraw = true;
		} 

		if ((redraw && al_event_queue_is_empty(gameData.event_queue)) && (!isPaused))
		{

			redraw = false;
			
			//Draws Every Element of the Game
			drawGameAspects(
				bg,
				player,
				pipeI,
				pipeList,
				gameData.font,
				displayWindow,
				gameTime,
				debugMode
				);

			//Draws Time
			tellTime(gameData.font, gameTime, displayWindow);

			if (player->isGameOver())
			{
				al_draw_bitmap(gameData.gameOverScreen, displayWindow->getWidth() / 2 - al_get_bitmap_width(gameData.gameOverScreen) / 2, displayWindow->getHeight() / 2 - al_get_bitmap_height(gameData.gameOverScreen) / 2, 0);
				al_draw_textf(gameData.gameOverFont, al_map_rgb(194, 152, 45), displayWindow->getWidth() / 2 + 69, displayWindow->getHeight() / 2 - 15, ALLEGRO_ALIGN_CENTRE, "%i", player->getScore());
			}

			groundbk.drawGround();
			al_flip_display();
			al_map_rgb(0, 0, 0);
		}
		
	}
	/*=---------------------Keep Highscore in configuration file-------------------------=*/
	if (player->getScore() > player->getHighscore())
	{
		al_set_config_value(config, "GameSettings", "HIGHSCORE", to_string(player->getScore()).c_str());
		al_save_config_file("config_file.cfg", config);
	}

	/*=-------------------Destroy All and Free memory-----------------------=*/
	for (pipeI = pipeList.begin(); pipeI != pipeList.end();)
	{
		delete (*pipeI);
		pipeI = pipeList.erase(pipeI);
	}

	DestroyGameData(gameData);
	al_destroy_config(config);

	return 0;
}