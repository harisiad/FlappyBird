#include "fb_bitmap.h"
#include "PlayerCS.h"
#include "config.h"
#include "pub_funcs.h"
#include "SoundManager.h"

using namespace std;

/*****************************/
/*-----------GLOBALS---------*/
enum FLAP{ UP };
bool FLAPS[1] = { false };

list<PipeBk *> pipeList;
list<PipeBk *>::iterator pipeI;
/*****************************/

int main(int argc, char **argv)
{
	ALLEGRO_CONFIG *config = (ALLEGRO_CONFIG*)0;							//CONFIGURATION ALLEGRO VAR
	ALLEGRO_DISPLAY *display = (ALLEGRO_DISPLAY*)0;							//DISPLAY ALLEGRO VAR
	ALLEGRO_EVENT_QUEUE *event_queue = (ALLEGRO_EVENT_QUEUE*)0;				//EVENT QUEUE ALLEGRO VAR
	ALLEGRO_TIMER *timer = (ALLEGRO_TIMER*)0;								//ALLEGRO TIMER VAR
	ALLEGRO_BITMAP *background = (ALLEGRO_BITMAP*)0;						//ALLEGRO BITMAP BACKGROUND
	ALLEGRO_BITMAP *ground = (ALLEGRO_BITMAP*)0;							//ALLEGRO BITMAP GROUND
	ALLEGRO_BITMAP *pipes = (ALLEGRO_BITMAP*)0;								//ALLEGRO BITMAP PIPES
	ALLEGRO_BITMAP *playerBM = (ALLEGRO_BITMAP*)0;							//ALLEGRO BITMAP FLAPPY
	ALLEGRO_BITMAP *gameoverscreen = (ALLEGRO_BITMAP*)0;					//ALLEGRO BITMAP GAMEOVER DISPLAY
	ALLEGRO_FONT *font = (ALLEGRO_FONT*)0;									//ALLEGRO FONT FOR SCORE HIGHSCORE
	ALLEGRO_FONT *GOFont = (ALLEGRO_FONT*)0;								//ALLEGRO GAMEOVER SCORE DISPLAY
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


	bool redraw = true;
	bool isPaused = false;
	bool done = false;

	float gameTime = 0;

	int backw, backh, grow, groh;
	int pcount = 0;
	int highscoreNum = 0;

	ConfigAPI *configD;														//CONFIGURATION CLASS
	Window *win;															//DISPLAY CLASS
	SoundManager *sManager = new SoundManager();

	config = al_load_config_file("config_file.cfg");

	configD = new ConfigAPI(
		atoi(al_get_config_value(config, NULL, "WIDTH")),
		atoi(al_get_config_value(config, NULL, "HEIGHT")),
		GetFullscreenValue(al_get_config_value(config, NULL, "FULLSCREEN")),
		stof(al_get_config_value(config, "GameSettings", "DIFFICULT")),
		atoi(al_get_config_value(config, "GameSettings", "HIGHSCORE")));

	highscoreNum = configD->GetHighScore();

	win = new Window();

	win->init(configD->WinWidth(), configD->WinHeight(), configD->WinFullscreen());

	if (!al_init()) {
		fprintf(stderr, "failed to initialize allegro!\n");
		return -1;
	}

	timer = al_create_timer(1.0 / FPS);
	if (!timer) {
		fprintf(stderr, "failed to create timer!\n");
		return -1;
	}

	display = al_create_display(configD->WinWidth(), configD->WinHeight());
	if (!display) {
		fprintf(stderr, "failed to create display!\n");
		al_destroy_timer(timer);
		return -1;
	}

	event_queue = al_create_event_queue();
	if (!event_queue) {
		fprintf(stderr, "failed to create event_queue!\n");
		al_destroy_display(display);
		al_destroy_timer(timer);
		return -1;
	}

	installAddons();
	
	background = al_load_bitmap("bkflappy.png");
	if (!background){
		al_destroy_bitmap(background);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	ground = al_load_bitmap("ground.png");
	if (!ground){
		al_destroy_bitmap(background);
		al_destroy_bitmap(ground);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	pipes = al_load_bitmap("pipes.png");
	if (!pipes){
		al_destroy_bitmap(pipes);
		al_destroy_bitmap(background);
		al_destroy_bitmap(ground);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		return -1;
	}

	playerBM = al_load_bitmap("bird.png");
	if (!playerBM){
		al_destroy_bitmap(playerBM);
		al_destroy_bitmap(pipes);
		al_destroy_bitmap(background);
		al_destroy_bitmap(ground);
		al_destroy_timer(timer);
		al_destroy_display(display);
		al_destroy_event_queue(event_queue);
		return -1;
	}
	/*----------------------------------------------*/
	/*---------------SOUND INSTALLATION-------------*/
	if (!al_reserve_samples(4)) {
		cout << "Failed to reserve audio samples!" << endl;
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
	sManager->initSManager(themesong, flapSound, hitPipeSound, pointSound, mixer);
	sManager->initMixer(voice);
	sManager->attach_Samples_to_Instances(themedata,
		flapdata,
		hitdata,
		pointdata);
	sManager->attach_Instances_to_Mixer();
	/*----------------------------------------------*/
	/*--------------BITMAP INSTALLATIONS------------*/
	gameoverscreen = al_load_bitmap("gameover.png");				//Game Over Bitmap Load
	//=-------Background Bitmap Width Height---------=//
	backw = al_get_bitmap_width(background);
	backh = al_get_bitmap_height(background);
	//=-------Ground Bitmap Width Height---------=//
	grow = al_get_bitmap_width(ground);
	groh = al_get_bitmap_height(ground);

	srand(time(NULL));//Random Generation Initialization with Time
	FbBackground bg(background, backw, win->getHeight(),win);
	GroundBk groundbk(ground, grow, groh, win);
	PipeBk *bg_pipes = new PipeBk();
	Player *player = new Player(playerBM);

	player->setHighscore(highscoreNum);

	font = al_load_ttf_font("arial.ttf", 18, 0);
	GOFont = al_load_ttf_font("arial.ttf", 35, 0);
	/*=--------------------------------------------------------------=*/
	/*=--------------EVENT QUEUE REGISTERING EVENTS------------------=*/
	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_keyboard_event_source());
	al_register_event_source(event_queue, al_get_mouse_event_source());
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	al_start_timer(timer);
	gameTime = al_current_time();

	sManager->playThemeSong();
	/*=---------------------------------------=*/
	/*=----------------Game Loop--------------=*/
	while (!done) {
		ALLEGRO_EVENT ev;
		al_wait_for_event(event_queue, &ev);

		if (ev.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
			done = true;
		}
		else if (ev.type == ALLEGRO_EVENT_KEY_DOWN){
			switch (ev.keyboard.keycode) {
			case ALLEGRO_KEY_P:
			{
				cout << "isPaused: " << isPaused;
				if (isPaused){
					isPaused = false;
				}
				else {
					isPaused = true;
				}
				break;
			}
			case ALLEGRO_KEY_G:{
				if (player->getGodMode()){
					player->setGodModeOff();
				}
				else {
					player->setGodModeOn();
				}
				break;
			}
			case ALLEGRO_KEY_ESCAPE:
				break;
			}
			
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
			if (ev.mouse.button & 1){
				if (!player->isGameOver()){
					sManager->playFlapSound();
					player->gainHeight();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP){
			if (ev.mouse.button & 1){
				if (!player->isGameOver()){
					//player->resetAnimation();
				}
			}
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_LEAVE_DISPLAY) {
			isPaused = true;
		}
		else if (ev.type == ALLEGRO_EVENT_MOUSE_ENTER_DISPLAY) {
			isPaused = false;
		}
		else if (ev.type == ALLEGRO_EVENT_TIMER){
			if (!player->isGameOver()){
				if (!isPaused){
					player->updatePlayer();
					player->gravityPull(groundbk.getY());
					bg.updateBackground();
					groundbk.updateBackground();
					gameTime = al_current_time();
					if ((int)gameTime % 5 == 0 && pcount < 100){
						bg_pipes = new PipeBk(pipes, al_get_bitmap_width(pipes), al_get_bitmap_height(pipes),win);
						bg_pipes->setvelX(-configD->GetDifficulty());
						pipeList.push_back(bg_pipes);
						bg_pipes->startPipes(bg, pcount++);
						//cout << "PIPE LIST SIZE: " << pipeList.size() << endl;
					}

					for (pipeI = pipeList.begin(); pipeI != pipeList.end();){
						if (player->collidePipes((*pipeI), groundbk, win) && (!player->getGodMode())){
							sManager->playCollisionSound();
							player->setGameOver();
						}
						if (player->passMark((*pipeI))){
							
							sManager->playSuccessSound();
							player->addScore();
						}
						
						if (!(*pipeI)->getAlivePipe()){
							delete (*pipeI);
							pipeI = pipeList.erase(pipeI);
							--pcount;
						}
						else {
							(*pipeI)->updatePipes();
							pipeI++;
						}
					}

				}
			}
			
			redraw = true;
		} 

		if ((redraw && al_event_queue_is_empty(event_queue)) &&
			(!isPaused)){

			redraw = false;
			
			//Draws Every Element of the Game
			drawGameAspects(
				bg,
				player,
				pipeI,
				pipeList,
				font,
				win,
				gameTime
				);

			//Draws Time
			tellTime(font, gameTime, win);

			if (player->isGameOver()){
				al_draw_bitmap(gameoverscreen, win->getWidth() / 2 - al_get_bitmap_width(gameoverscreen) / 2, win->getHeight() / 2 - al_get_bitmap_height(gameoverscreen) / 2, 0);
				al_draw_textf(GOFont, al_map_rgb(194, 152, 45), win->getWidth() / 2 + 69, win->getHeight() / 2 - 15, ALLEGRO_ALIGN_CENTRE, "%i", player->getScore());
				
			}
			groundbk.drawGround();
			al_flip_display();
			al_map_rgb(0, 0, 0);
		}
		
	}
	/*=---------------------Keep Highscore in configuration file-------------------------=*/
	if (player->getScore() > player->getHighscore()){
		//const char* highscore = highscore_string(player->getScore()).c_str();
		cout << "NEW HIGHSCORE: " << to_string(player->getScore()).c_str() << " !!!" << endl;
		al_set_config_value(config, "GameSettings", "HIGHSCORE", to_string(player->getScore()).c_str());
		al_save_config_file("config_file.cfg", config);
	}
	/*=-------------------Destroy All and Free memory-----------------------=*/
	for (pipeI = pipeList.begin(); pipeI != pipeList.end();){
		delete (*pipeI);
		pipeI = pipeList.erase(pipeI);
	}

	al_destroy_bitmap(background);
	al_destroy_bitmap(ground);
	al_destroy_timer(timer);
	al_destroy_display(display);
	al_destroy_event_queue(event_queue);
	al_destroy_config(config);

	return 0;
}