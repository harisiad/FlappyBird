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

	gameData.replayButton = al_load_bitmap("replay.png");				//Game Over Bitmap Load
	if (!gameData.replayButton)
	{
		fprintf(stderr, "failed to load replay button!\n");
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

void FBGame::DrawGameAspects()
{
	scene.bg.draw(); //Draw Background

	scene.player->drawPlayer(); //Draw Flappy

	for (pipeI = pipeList.begin(); pipeI != pipeList.end(); ++pipeI)
	{
		(*pipeI)->draw();
		/*Bound Boxes of Pipes and Space in between*/
		if (gameModes.debug)
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

			al_draw_filled_rectangle(scene.player->getX() - scene.player->getWidth() / 2,
				scene.player->getY() - scene.player->getHeight() / 2,
				scene.player->getX() + scene.player->getBoundX(),
				scene.player->getY() + scene.player->getBoundY(),
				al_map_rgb(255, 0, 0));

			al_draw_textf(gameData.font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) - 20, ALLEGRO_ALIGN_LEFT, "Player");
			al_draw_textf(gameData.font, al_map_rgb(255, 0, 0), 0, SCREEN_H / 2, ALLEGRO_ALIGN_LEFT, "X: %.3f", scene.player->getX());
			al_draw_textf(gameData.font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 20, ALLEGRO_ALIGN_LEFT, "Y: %.3f", scene.player->getY());
			al_draw_textf(gameData.font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 40, ALLEGRO_ALIGN_LEFT, "Bound X: %d", scene.player->getBoundX());
			al_draw_textf(gameData.font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 60, ALLEGRO_ALIGN_LEFT, "Bound Y: %d", scene.player->getBoundY());
			al_draw_textf(gameData.font, al_map_rgb(255, 0, 0), 0, (SCREEN_H / 2) + 80, ALLEGRO_ALIGN_LEFT, "Velocity Y: %.8f", scene.player->getVelY());

			al_draw_textf(gameData.font, al_map_rgb(255, 125, 0), (*pipeI)->getX(), 30, ALLEGRO_ALIGN_CENTER, "%.3f", (*pipeI)->getX());
		}
	}
	scene.groundbk.drawGround();

	//Draw Score
	al_draw_textf(gameData.font, al_map_rgb(255, 255, 255), displayWindow->getWidth() / 2, 20, ALLEGRO_ALIGN_CENTRE, "%i", scene.player->getScore());
	al_draw_textf(gameData.font, al_map_rgb(255, 255, 255), displayWindow->getWidth() - 20, 20, ALLEGRO_ALIGN_RIGHT, "High Score: %i", scene.player->getHighscore());
	
	//Draws Time
	TellTime();
}

/*Draws Time*/
void FBGame::TellTime()
{
	int sec = gameTime;
	int minutes = (sec / 60);
	if (sec >= 60)
	{		// 60 secs go back to count 0
		sec = sec % 60;
	}
	al_draw_textf(gameData.font, al_map_rgb(255, 255, 255), 10, 20, ALLEGRO_ALIGN_LEFT, "Time: %.2i:%.2i", minutes, (int)sec);
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

void FBGame::CountDown()
{

}

void FBGame::MainGame()
{
	if (!scene.player->isGameOver())
	{
		if (!gameModes.pause)
		{
			bool isMoved = false;
			pipeCount = pipeList.size();
			
			scene.player->updatePlayer();

			scene.bg.update();

			scene.groundbk.update();

			gameTime = al_current_time();

			if (pipeCount < 10)
			{
				scene.bg_pipes = new PipeBk(gameData.pipes, al_get_bitmap_width(gameData.pipes), al_get_bitmap_height(gameData.pipes), displayWindow);
				pipeList.push_back(scene.bg_pipes);
				scene.bg_pipes->startPipes(scene.bg, pipeCount++);
			}

			for (PipeBk* pipe : pipeList)
			{
				if ((scene.player->collidePipes(pipe) && (!scene.player->getGodMode())) || 
					scene.player->gravityPull(scene.groundbk.getY()))
				{
					soundManager->playCollisionSound();
					scene.player->setGameOver();
					break;
				}

				bool pipeHit = scene.player->passMark(pipe);
				if (pipeHit)
				{
					soundManager->playSuccessSound();
					scene.player->addScore();
					pipe->setScored(true);
				}

				if (pipe->getX() < -pipe->getWidth() * 2)
				{
					PipeBk* firstPipe = pipeList.front();
					PipeBk* lastPipe = pipeList.back();

					firstPipe->setX(lastPipe->getX() + firstPipe->getPipeDistance());

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

	if ((gameModes.redraw && al_event_queue_is_empty(gameData.event_queue)) && (!gameModes.pause))
	{

		gameModes.redraw = false;

		//Draws Every Element of the Game
		DrawGameAspects();

		if (scene.player->isGameOver())
		{
			currentStage = Stages::GameOver;
		}

		al_flip_display();
		al_map_rgb(0, 0, 0);
	}
}

void FBGame::ActsPlayLoop()
{
	scene.bg = Background(gameData.background, al_get_bitmap_width(gameData.background), displayWindow->getHeight(), displayWindow);
	scene.groundbk = GroundBk(gameData.ground, al_get_bitmap_width(gameData.ground), al_get_bitmap_height(gameData.ground), displayWindow);
	scene.bg_pipes = new PipeBk();
	scene.player = new Player(gameData.playerBmp);

	al_start_timer(gameData.timer);
	gameTime = al_current_time();

	if (currentStage == Stages::MainGame)
	{
		scene.player->setHighscore(configData->GetHighScore());

		soundManager->playThemeSong();
	}

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
				PauseAct();
				break;
			}
			case ALLEGRO_KEY_G:
			{
				CheatTheGame();
				break;
			}
			case ALLEGRO_KEY_D:
			{
				DebugAct();
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
				break;
			}

		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN)
		{
			if (ev.mouse.button & 1)
			{
				if (!scene.player->isGameOver() &&
					currentStage == Stages::MainGame)
				{
					if (!gameModes.pause)
					{
						soundManager->playFlapSound();
					}
					else
					{
						PauseAct();
					}
					scene.player->gainHeight();
				}
				else if (scene.player->isGameOver() &&
					currentStage == Stages::GameOver)
				{
					ALLEGRO_MOUSE_STATE mouseState;

					al_get_mouse_state(&mouseState);
					if ((mouseState.x >= displayWindow->getWidth() / 2 - 65 &&
						mouseState.x <= displayWindow->getWidth() / 2 + 65) &&
						(mouseState.y >= displayWindow->getHeight() / 2 + 75 &&
							mouseState.y <= displayWindow->getHeight() / 2 + 105))
					{
						currentStage = Stages::MainGame;
						ResetPlay();
					}
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
		{
			if (ev.mouse.button & 1)
			{
				if (!scene.player->isGameOver())
				{
					//player->resetAnimation();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_AXES)
		{
			ALLEGRO_MOUSE_STATE mouseState;

			al_get_mouse_state(&mouseState);
			if ((mouseState.x >= displayWindow->getWidth() / 2 - 65 &&
				mouseState.x <= displayWindow->getWidth() / 2 + 65) &&
				(mouseState.y >= displayWindow->getHeight() / 2 + 75 &&
					mouseState.y <= displayWindow->getHeight() / 2 + 105))
			{
				al_draw_textf(
					gameData.gameOverFont,
					al_map_rgb(0, 0, 0),
					displayWindow->getWidth() / 2 + 6,
					displayWindow->getHeight() / 2 + 55,
					ALLEGRO_ALIGN_CENTER,
					"Replay?"
				);
			}
			else
			{
				al_draw_textf(
					gameData.gameOverFont,
					al_map_rgb(255, 255, 255),
					displayWindow->getWidth() / 2 + 6,
					displayWindow->getHeight() / 2 + 55,
					ALLEGRO_ALIGN_CENTER,
					"Replay?"
				);
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY)
		{
			if (!gameModes.pause &&
				currentStage == Stages::MainGame)
			{
				PauseAct();
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY)
		{
			// PauseAct();
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER)
		{
			ActsProgramme();
		}

	}

	if (scene.player->getScore() > scene.player->getHighscore())
	{
		al_set_config_value(gameData.config, "GameSettings", "HIGHSCORE", std::to_string(scene.player->getScore()).c_str());
		al_save_config_file("config_file.cfg", gameData.config);
	}
}

void FBGame::ActsProgramme()
{
	switch (currentStage)
	{
		case Stages::StartMenu:
		{
			break;
		}
		case Stages::CountDown:
		{
			CountDown();
			break;
		}
		case Stages::MainGame:
		{
			MainGame();
			break;
		}
		case Stages::GameOver:
		{
			CloseCurtains();
			break;
		}
	}
}

void FBGame::PauseAct()
{
	if (gameModes.pause)
	{
		gameModes.pause = false;
	}
	else
	{
		gameModes.pause = true;
	}
}

void FBGame::CheatTheGame()
{
	if (scene.player->getGodMode())
	{
		scene.player->setGodModeOff();
	}
	else
	{
		scene.player->setGodModeOn();
	}
}

void FBGame::DebugAct()
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

void FBGame::OpenCurtains()
{

}

void FBGame::CloseCurtains()
{
	al_draw_bitmap(
		gameData.gameOverScreen,
		displayWindow->getWidth() / 2 - al_get_bitmap_width(gameData.gameOverScreen) / 2,
		displayWindow->getHeight() / 2 - al_get_bitmap_height(gameData.gameOverScreen) / 2, 
		0
	);
	al_draw_textf(
		gameData.gameOverFont,
		al_map_rgb(194, 152, 45),
		displayWindow->getWidth() / 2 + 69,
		displayWindow->getHeight() / 2 - 15,
		ALLEGRO_ALIGN_CENTRE, "%i",
		scene.player->getScore()
	);

	al_flip_display();
	al_map_rgb(0, 0, 0);
}

void FBGame::ResetPlay()
{
	scene.bg.resetPlay();
	scene.groundbk.resetPlay();
	gameTime = 0.0f;

	scene.player->resetPlayer();

	for (pipeI = pipeList.begin(); pipeI != pipeList.end();)
	{
		delete (*pipeI);
		pipeI = pipeList.erase(pipeI);
	}
	
	scene.bg_pipes->resetPlay();

	al_clear_to_color(al_map_rgba_f(0, 0, 0, 0.2));
	al_flip_display();
	
	al_rest(0.001);
}