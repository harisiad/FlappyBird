#include "pub_funcs.h"

bool GetFullscreenValue(const char* c)
{
	bool tmp = false;

	if (strcmp(c, "FALSE") == 0) {
		tmp = false;
	}
	else if (strcmp(c, "TRUE") == 0) {
		tmp = false;
	}

	return tmp;
}

void installAddons()
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

void installSound(SoundManager* target)
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
	target->initSManager(themesong, flapSound, hitPipeSound, pointSound, mixer);
	target->initMixer(voice);
	target->attach_Samples_to_Instances(themedata,
		flapdata,
		hitdata,
		pointdata);
	target->attach_Instances_to_Mixer();
}

void drawGameAspects(FbBackground bg, Player* player, std::list<PipeBk *>::iterator pipeI, std::list<PipeBk *> pipeList, ALLEGRO_FONT* font, Window* win, int time){
	
	bg.drawBackground(); //Draw Background
	
	player->drawPlayer(); //Draw Flappy
	

	for (pipeI = pipeList.begin(); pipeI != pipeList.end(); ++pipeI){
		(*pipeI)->drawPipes();
		/*Bound Boxes of Pipes and Space in between*/

		/*al_draw_filled_rectangle((*pipeI)->getX() - (*pipeI)->getBoundXup(),
		(*pipeI)->getY() - (*pipeI)->getBoundFreeY() - (*pipeI)->getBoundYup(),
		(*pipeI)->getX() + (*pipeI)->getBoundXup(),
		(*pipeI)->getY() - (*pipeI)->getBoundFreeY(),
		al_map_rgb(255,0,0));

		al_draw_filled_rectangle((*pipeI)->getX() - (*pipeI)->getBoundXdown(),
		(*pipeI)->getY() + (*pipeI)->getBoundFreeY(),
		(*pipeI)->getX() + (*pipeI)->getBoundXdown(),
		(*pipeI)->getY() + (*pipeI)->getBoundFreeY() + 2*(*pipeI)->getBoundYdown(),
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
		al_map_rgb(255, 0, 0));*/
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
void tellTime(ALLEGRO_FONT* font, int sec, Window* win){
	int minutes = (sec / 60);
	if (sec >= 60) {		// 60 secs go back to count 0
		sec = sec % 60;
	}
	al_draw_textf(font, al_map_rgb(255, 255, 255), 10, 20, ALLEGRO_ALIGN_LEFT, "Time: %.2i:%.2i",minutes, (int)sec);
}

std::string const highscore_string(int x){
	std::string str = std::to_string(x);
	return str;
}
