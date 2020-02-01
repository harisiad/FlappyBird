#include "fb_game.h"

FBGame::FBGame()
{

}

FBGame::~FBGame()
{
	for (pipeI = pipeList.begin(); pipeI != pipeList.end();)
	{
		delete (*pipeI);
		pipeI = pipeList.erase(pipeI);
	}

	DestroyGameData();
}

void FBGame::InitializeWindow()
{
	displayWindow->init(configData->WinWidth(), configData->WinHeight(), configData->WinFullscreen());
}

void FBGame::InitializeGameData()
{
	srand(time(NULL));	//Random Generation Initialization with Time

	if (!al_init())
	{
		fprintf(stderr, "failed to initialize allegro!\n");
	}


	gameData.config = al_load_config_file("config_file.cfg");
	if (!gameData.config)
	{
		fprintf(stderr, "failed to config file\n");
		gameData.code = ERR_CONFIG_LD;
	}

	configData = new ConfigAPI(
		std::atoi(al_get_config_value(gameData.config, NULL, "WIDTH")),
		std::atoi(al_get_config_value(gameData.config, NULL, "HEIGHT")),
		GetFullscreenValue(al_get_config_value(gameData.config, NULL, "FULLSCREEN")),
		std::stof(al_get_config_value(gameData.config, "GameSettings", "DIFFICULT")),
		std::atoi(al_get_config_value(gameData.config, "GameSettings", "HIGHSCORE")));

	gameData.timer = al_create_timer(1.0 / FPS);
	if (!gameData.timer)
	{
		fprintf(stderr, "failed to create timer!\n");
		gameData.code = ERR_TIMER_LD;
	}

	gameData.display = al_create_display(configData->WinWidth(), configData->WinHeight());
	if (!gameData.display)
	{
		fprintf(stderr, "failed to create display!\n");
		gameData.code = ERR_DISPLAY_LD;
	}

	gameData.event_queue = al_create_event_queue();
	if (!gameData.event_queue)
	{
		fprintf(stderr, "failed to create event_queue!\n");
		gameData.code = ERR_EVENTQUEUE_LD;
	}

	InstallAddons();

	gameData.background = al_load_bitmap("bkflappy.png");
	if (!gameData.background)
	{
		fprintf(stderr, "failed to load background bitmap!\n");
		gameData.code = ERR_BACKGROUND_LD;
	}

	gameData.ground = al_load_bitmap("ground.png");
	if (!gameData.ground)
	{
		fprintf(stderr, "failed to load ground bitmap!\n");
		gameData.code = ERR_GROUND_LD;
	}

	gameData.pipes = al_load_bitmap("pipes.png");
	if (!gameData.pipes)
	{
		fprintf(stderr, "failed to load pipe bitmap!\n");
		gameData.code = ERR_PIPES_LD;
	}

	gameData.playerBmp = al_load_bitmap("bird.png");
	if (!gameData.playerBmp)
	{
		fprintf(stderr, "failed to load flappy bird stripe!\n");
		gameData.code = ERR_PLAYERBMP_LD;
	}

	gameData.gameOverScreen = al_load_bitmap("gameover.png");				//Game Over Bitmap Load
	if (!gameData.gameOverScreen)
	{
		fprintf(stderr, "failed to load gameover bitmap!\n");
		gameData.code = ERR_GAMEOVERSCREEN_LD;
	}

	gameData.font = al_load_ttf_font("8bit.ttf", 18, 0);
	if (!gameData.font)
	{
		fprintf(stderr, "failed to load font!\n");
		gameData.code = ERR_FONT_LD;
	}

	gameData.gameOverFont = al_load_ttf_font("8bit.ttf", 35, 0);
	if (!gameData.font)
	{
		fprintf(stderr, "failed to load game over font\n");
		gameData.code = ERR_FONT_LD;
	}
}

void FBGame::InstallAddons()
{
	if (!al_install_keyboard())
	{
		std::cout << "Failed to install keyboard..." << std::endl;
	}
	if (!al_init_image_addon())
	{
		std::cout << "Failed to install image addon..." << std::endl;
	}
	if (!al_init_primitives_addon())
	{
		std::cout << "Failed to install primitives addon..." << std::endl;
	}
	if (!al_install_mouse())
	{
		std::cout << "Failed to install mouse..." << std::endl;
	}
	if (!al_install_audio())
	{
		std::cout << "Failed to install audio!" << std::endl;
	}
	if (!al_init_acodec_addon())
	{
		std::cout << "Failed to init acodec addon!" << std::endl;
	}

	al_init_font_addon();

	if (!al_init_ttf_addon())
	{
		std::cout << "Failed to install ttf addon..." << std::endl;
	}
}

void FBGame::InstallSound()
{
	ALLEGRO_SAMPLE_INSTANCE *themesong = (ALLEGRO_SAMPLE_INSTANCE*)0;		//ALLEGRO THEME SONG VAR
	ALLEGRO_SAMPLE_INSTANCE *flapSound = (ALLEGRO_SAMPLE_INSTANCE*)0;		//ALLEGRO FLAP SOUND VAR
	ALLEGRO_SAMPLE_INSTANCE *hitPipeSound = (ALLEGRO_SAMPLE_INSTANCE*)0;	//ALLEGRO HIT PIPE SOUND VAR
	ALLEGRO_SAMPLE_INSTANCE *pointSound = (ALLEGRO_SAMPLE_INSTANCE*)0;		//ALLEGRO POINT SOUND VAR
	ALLEGRO_SAMPLE *themedata = (ALLEGRO_SAMPLE*)0;							//ALLEGRO THEME SONG DATA VAR
	ALLEGRO_SAMPLE *flapdata = (ALLEGRO_SAMPLE*)0;							//ALLEGRO FLAP SOUND DATA VAR
	ALLEGRO_SAMPLE *hitdata = (ALLEGRO_SAMPLE*)0;							//ALLEGRO COLLISION SOUND DATA VAR
	ALLEGRO_SAMPLE *pointdata = (ALLEGRO_SAMPLE*)0;							//ALLEGRO POINT SOUND DATA VAR
	ALLEGRO_MIXER *mixer = (ALLEGRO_MIXER*)0;
	ALLEGRO_VOICE *voice = (ALLEGRO_VOICE*)0;

	if (!al_reserve_samples(4))
	{
		std::cout << "Failed to reserve audio samples!" << std::endl;
	}
	//---------Sample Loading-----------//
	themedata = al_load_sample("theme_song.ogg");
	flapdata = al_load_sample("flap.wav");
	hitdata = al_load_sample("hit.ogg");
	pointdata = al_load_sample("success.ogg");
	//---------Instances Creation----------//
	themesong = al_create_sample_instance(NULL);
	flapSound = al_create_sample_instance(NULL);
	hitPipeSound = al_create_sample_instance(NULL);
	pointSound = al_create_sample_instance(NULL);
	//---------Sound Manager Initialization + Instances and mixer loading---------//
	soundManager->initSManager(themesong, flapSound, hitPipeSound, pointSound, mixer);
	soundManager->initMixer(voice);
	soundManager->attach_Samples_to_Instances(themedata,
		flapdata,
		hitdata,
		pointdata);
	soundManager->attach_Instances_to_Mixer();
}

void FBGame::RegisterEventSources()
{
	al_register_event_source(gameData.event_queue, al_get_display_event_source(gameData.display));
	al_register_event_source(gameData.event_queue, al_get_keyboard_event_source());
	al_register_event_source(gameData.event_queue, al_get_mouse_event_source());
	al_register_event_source(gameData.event_queue, al_get_timer_event_source(gameData.timer));
}


void FBGame::DestroyGameData()
{
	al_destroy_bitmap(gameData.playerBmp);
	al_destroy_bitmap(gameData.pipes);
	al_destroy_bitmap(gameData.background);
	al_destroy_bitmap(gameData.ground);
	al_destroy_bitmap(gameData.gameOverScreen);
	al_destroy_timer(gameData.timer);
	al_destroy_display(gameData.display);
	al_destroy_event_queue(gameData.event_queue);
	al_destroy_config(gameData.config);
}


void FBGame::DrawGameAspects(Background bg, Player* player, std::list<PipeBk *>::iterator pipeI, std::list<PipeBk *> pipeList, ALLEGRO_FONT* font, Window* win, int time, bool debugMode)
{
	bg.draw(); //Draw Background

	player->drawPlayer(); //Draw Flappy

	for (pipeI = pipeList.begin(); pipeI != pipeList.end(); ++pipeI)
	{
		(*pipeI)->draw();
		/*Bound Boxes of Pipes and Space in between*/
		if (debugMode)
		{
			al_draw_filled_rectangle((*pipeI)->getX() - (*pipeI)->getBoundXup(),
				(*pipeI)->getY() - (*pipeI)->getBoundFreeY() - (*pipeI)->getBoundYup(),
				(*pipeI)->getX() + (*pipeI)->getBoundXup(),
				(*pipeI)->getY() - (*pipeI)->getBoundFreeY(),
				al_map_rgb(255, 0, 0));

			al_draw_filled_rectangle((*pipeI)->getX() - (*pipeI)->getBoundXdown(),
				(*pipeI)->getY() + (*pipeI)->getBoundFreeY(),
				(*pipeI)->getX() + (*pipeI)->getBoundXdown(),
				(*pipeI)->getY() + (*pipeI)->getBoundFreeY() + 2 * (*pipeI)->getBoundYdown(),
				al_map_rgb(0, 0, 255));

			al_draw_filled_rectangle((*pipeI)->getX() - (*pipeI)->getBoundFreeX(),
				(*pipeI)->getY() - (*pipeI)->getBoundFreeY(),
				(*pipeI)->getX() + (*pipeI)->getBoundFreeX(),
				(*pipeI)->getY() + (*pipeI)->getBoundFreeY(),
				al_map_rgb(255, 0, 255));

			al_draw_filled_rectangle((*pipeI)->getX() - 5,
				(*pipeI)->getY() - 5,
				(*pipeI)->getX() + 5,
				(*pipeI)->getY() + 5,
				al_map_rgb(255, 0, 0));

			al_draw_filled_rectangle(player->getX() - player->getWidth() / 2,
				player->getY() - player->getHeight() / 2,
				player->getX() + player->getBoundX(),
				player->getY() + player->getBoundY(),
				al_map_rgb(255, 0, 0));

			al_draw_textf(font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) - 20, ALLEGRO_ALIGN_LEFT, "Player");
			al_draw_textf(font, al_map_rgb(255, 0, 0), 0, SCREEN_H / 2, ALLEGRO_ALIGN_LEFT, "X: %.3f", player->getX());
			al_draw_textf(font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 20, ALLEGRO_ALIGN_LEFT, "Y: %.3f", player->getY());
			al_draw_textf(font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 40, ALLEGRO_ALIGN_LEFT, "Bound X: %d", player->getBoundX());
			al_draw_textf(font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 60, ALLEGRO_ALIGN_LEFT, "Bound Y: %d", player->getBoundY());

			al_draw_textf(font, al_map_rgb(255, 125, 0), (*pipeI)->getX(), 30, ALLEGRO_ALIGN_CENTER, "%.3f", (*pipeI)->getX());
		}
	}
	al_draw_filled_rectangle(player->getX(),
		player->getY(),
		player->getX(),
		player->getY(),
		al_map_rgb(0, 0, 255));
	//Draw Score
	al_draw_textf(font, al_map_rgb(255, 255, 255), win->getWidth() / 2, 20, ALLEGRO_ALIGN_CENTRE, "%i", player->getScore());
	al_draw_textf(font, al_map_rgb(255, 255, 255), win->getWidth() - 20, 20, ALLEGRO_ALIGN_RIGHT, "High Score: %i", player->getHighscore());
}

/*Draws Time*/
void FBGame::TellTime(ALLEGRO_FONT* font, int sec, Window* win)
{
	int minutes = (sec / 60);
	if (sec >= 60)
	{		// 60 secs go back to count 0
		sec = sec % 60;
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, ALLEGRO_ALIGN_LEFT, "Time: %.2i:%.2i", minutes, (int)sec);
}

bool FBGame::GetFullscreenValue(const char* c)
{
	bool tmp = false;

	if (strcmp(c, "FALSE") == 0)
	{
		tmp = false;
	}
	else if (strcmp(c, "TRUE") == 0)
	{
		tmp = false;
	}

	return tmp;
}

void FBGame::ActsPlayLoop()
{
	Background bg(gameData.background, al_get_bitmap_width(gameData.background), displayWindow->getHeight(), displayWindow);
	GroundBk groundbk(gameData.ground, al_get_bitmap_width(gameData.ground), al_get_bitmap_height(gameData.ground), displayWindow);
	PipeBk *bg_pipes = new PipeBk();
	Player *player = new Player(gameData.playerBmp);

	float gameTime = 0.0;

	al_start_timer(gameData.timer);
	gameTime = al_current_time();

	player->setHighscore(configData->GetHighScore());

	soundManager->playThemeSong();

	while (!gameModes.running)
	{
		ALLEGRO_EVENT ev;
		al_wait_for_event(gameData.event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
		{
			gameModes.running = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN)
		{
			switch (ev.keyboard.keycode)
			{
			case ALLEGRO_KEY_P:
			{
				if (gameModes.pause)
				{
					gameModes.pause = false;
				}
				else
				{
					gameModes.pause = true;
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
				if (gameModes.debug)
				{
					gameModes.debug = false;
				}
				else
				{
					gameModes.debug = true;
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
			gameModes.pause = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			gameModes.pause = false;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			if (!player->isGameOver())
			{
				if (!gameModes.pause)
				{
					bool isMoved = false;

					player->updatePlayer();
					player->gravityPull(groundbk.getY());

					bg.update();

					groundbk.update();

					gameTime = al_current_time();

					if (pipeCount < 10)
					{
						bg_pipes = new PipeBk(gameData.pipes, al_get_bitmap_width(gameData.pipes), al_get_bitmap_height(gameData.pipes), displayWindow);
						pipeList.push_back(bg_pipes);
						bg_pipes->startPipes(bg, pipeCount++);
					}

					for (PipeBk* pipe : pipeList)
					{
						bool hit = player->passMark(pipe);
						if (player->collidePipes(pipe) && (!player->getGodMode()))
						{
							soundManager->playCollisionSound();
							player->setGameOver();
						}

						if (player->passMark(pipe))
						{
							soundManager->playSuccessSound();
							player->addScore();
							pipe->setScored(true);
						}

						if (pipe->getX() < -pipe->getWidth() * 2)
						{
							PipeBk* firstPipe = pipeList.front();
							PipeBk* lastPipe = pipeList.back();

							firstPipe->setX(lastPipe->getX() + firstPipe->getPipeDistance());
							/*pipeList.push_back(firstPipe);
							pipeList.pop_front();*/
							isMoved = true;
						}
						else
						{
							pipe->updatePipes();
						}
					}

					if (isMoved)
					{
						PipeBk* firstPipe = pipeList.front();

						firstPipe->setScored(false);

						pipeList.pop_front();
						pipeList.push_back(firstPipe);

						isMoved = false;
					}
				}
			}

			gameModes.redraw = true;
		}

		if ((gameModes.redraw && al_event_queue_is_empty(gameData.event_queue)) && (!gameModes.pause))
		{

			gameModes.redraw = false;

			//Draws Every Element of the Game
			DrawGameAspects(
				bg,
				player,
				pipeI,
				pipeList,
				gameData.font,
				displayWindow,
				gameTime,
				gameModes.debug
			);

			//Draws Time
			TellTime(gameData.font, gameTime, displayWindow);

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

	if (player->getScore() > player->getHighscore())
	{
		al_set_config_value(gameData.config, "GameSettings", "HIGHSCORE", std::to_string(player->getScore()).c_str());
		al_save_config_file("config_file.cfg", gameData.config);
	}
}

void FBGame::ActsProgramme()
{

}

void FBGame::PauseAct()
{

}

void FBGame::CheatTheGame()
{

}

void FBGame::DebugAct()
{

}

void FBGame::OpenCurtains()
{

}

void FBGame::CloseCurtains()
{

}