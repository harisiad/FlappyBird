#include "fb_bitmap.h"
#include "Globals.h"

Window::Window(){
	width = 0;
	height = 0;

	fullscreen = false;
}

void Window::init(int _width, int _height, bool _fullscreen){
	width = _width;
	height = _height;

	fullscreen = _fullscreen;
}

FbBackground::FbBackground(){
	x = 0;
	y = 0;
	velX = -0.3;
	velY = 0;

	bg = (ALLEGRO_BITMAP*)0;

	win = new Window();
}

FbBackground::FbBackground(ALLEGRO_BITMAP* image,int width, int height, Window *_win){
	x = 0;
	y = 0;
	velX = -0.3;
	velY = 0;

	bgwidth = width;
	bgheight = height;
	
	bg = image;

	win = _win;
}

void FbBackground::setX(int x){
	FbBackground::x = x;
}
float FbBackground::getX(){
	return FbBackground::x;
}
void FbBackground::setvelX(float x){
	velX = x;
}
float FbBackground::getvelX(){
	return velX;
}

void FbBackground::setY(float diry){
	y = diry;
}
float FbBackground::getY(){ return y; }
void FbBackground::setvelY(float){}
float FbBackground::getvelY(){ return velY; }

void FbBackground::setBgWidth(int width){
	bgwidth = width;
}
int FbBackground::getBgWidth(){
	return bgwidth;
}
void FbBackground::setBgHeight(int height){
	bgheight = height;
}
int FbBackground::getBgHeight(){
	return bgheight;
}

void FbBackground::setImage(ALLEGRO_BITMAP* image){
	bg = image;
}
ALLEGRO_BITMAP* FbBackground::getImage(){
	return bg;
}

void FbBackground::updateBackground(){
	x += velX;
	if (x + bgwidth <= 0){
		x = 0;
	}
}
void FbBackground::drawBackground(){
	al_draw_scaled_bitmap(bg, 0, 0, 
		al_get_bitmap_width(bg),
		al_get_bitmap_height(bg),
		x,y,
		al_get_bitmap_width(bg), win->getHeight(), 0);

	if (x + bgwidth < SCREEN_W){
		al_draw_scaled_bitmap(bg, 0, 0, 
			al_get_bitmap_width(bg),
			al_get_bitmap_height(bg),
			x + bgwidth, y,
			al_get_bitmap_width(bg), win->getHeight(), 0);
	}
}

GroundBk::GroundBk(){
	x = 0;
	y = SCREEN_H - 50;
	velX = -1.0;
	velY = 0;

	bg = (ALLEGRO_BITMAP*)0;

	boundx = SCREEN_W;
	boundy = 0;
}

GroundBk::GroundBk(ALLEGRO_BITMAP* image, int width, int height, Window *_win){
	x = 0;
	
	velX = -1.0;
	velY = 0;

	bgwidth = width;
	bgheight = height;

	bg = image;

	win = _win;

	y = win->getHeight() - 50;

	boundx = SCREEN_W;
	boundy = height;
}


void GroundBk::setBoundX(int x){
	boundx = x; 
}
int GroundBk::getBoundX(){
	return boundx;
}
void GroundBk::setBoundY(int y){
	boundy = y;
}
int GroundBk::getBoundY(){
	return boundy;
}

void GroundBk::drawGround(){
	al_draw_scaled_bitmap(bg, 0, 0,
		al_get_bitmap_width(bg),
		al_get_bitmap_height(bg),
		x, y,
		win->getWidth(), al_get_bitmap_height(bg), 0);

	if (x + bgwidth < SCREEN_W){
		al_draw_scaled_bitmap(bg, 0, 0,
			al_get_bitmap_width(bg),
			al_get_bitmap_height(bg),
			x + bgwidth, y,
			win->getWidth(), al_get_bitmap_height(bg), 0);
	}
}

bool GroundBk::groundCollision(int x, int y){
	return false;
}

PipeBk::PipeBk(){
	x = 0;
	y = 0;
	velX = -1.0;
	velY = 0;

	bgwidth = 0;
	bgheight = 0;

	bg = (ALLEGRO_BITMAP*)0;

	boundXup = 0;
	boundYup = 0;

	boundXdown = 0;
	boundYdown = 0;

	alive = true;
}
PipeBk::PipeBk(ALLEGRO_BITMAP* image, int width, int height, Window *_win){
	x = 0;
	y = 0;
	velX = -3.0;
	velY = 0;

	bgwidth = width;
	bgheight = height;

	bg = image;

	win = _win;

	boundXup = 25;
	boundYup = height;

	boundXdown = 25;
	boundYdown = height;

	boundFreeX = 20;
	boundFreeY = 50;

	alive = true;
}

void PipeBk::setBoundXup(int x){
	boundXup = x;
}
int PipeBk::getBoundXup(){
	return boundXup;
}
void PipeBk::setBoundYup(int y){
	boundYup = y;
}
int PipeBk::getBoundYup(){
	return boundYup;
}

void PipeBk::setBoundXdown(int x){
	boundXdown = x;
}
int PipeBk::getBoundXdown(){
	return boundXdown;
}
void PipeBk::setBoundYdown(int y){
	boundYdown = y;
}
int PipeBk::getBoundYdown(){
	return boundYdown;
}

void PipeBk::startPipes(FbBackground back, int mul){
	x = win->getWidth() + mul * 300;
	y = win->getHeight() / 4 + (rand() % (int)((win->getHeight() - 2 * win->getHeight() / 5) - win->getHeight() / 4 + 1));
}

void PipeBk::drawPipes(){
	al_draw_scaled_bitmap(bg,
		0, 0,
		bgwidth, bgheight,
		x - bgwidth/2, y - boundFreeY - bgheight,
		bgwidth, bgheight,
		0);
	al_draw_scaled_bitmap(bg,
		0, 0,
		bgwidth, bgheight, 
		x - bgwidth / 2, y + boundFreeY,
		bgwidth, bgheight,
		-1);

	if (x < 0 - bgwidth - 5) {
		alive = false;
	}
}

void PipeBk::updatePipes(){
	x += velX;
}

bool PipeBk::groundCollision(int x, int y){
	return false;
}