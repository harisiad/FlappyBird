#include "pub_funcs.h"

bool GetFullscreenValue(const char* c){
	bool tmp = false;

	if (strcmp(c, "FALSE") == 0) {
		tmp = false;
	}
	else if (strcmp(c, "TRUE") == 0) {
		tmp = false;
	}

	return tmp;
}

void installAddons(){
	al_install_keyboard();
	al_init_image_addon();
	al_init_primitives_addon();
	al_install_mouse();
	if (!al_install_audio()){
		std::cout << "Failed to install audio!" << std::endl;
	}
	if (!al_init_acodec_addon()){
		std::cout << "Failed to init acodec addon!" << std::endl;
	}
	al_init_font_addon();
	al_init_ttf_addon();
	
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
