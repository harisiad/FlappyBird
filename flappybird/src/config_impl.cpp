#include "config.h"

ConfigAPI::ConfigAPI() {
	configData.winWidth = 800;
	configData.winHeight = 460;
	configData.fullscreen = false;
	configData.difficulty = 0;
	configData.highscore = 0;
}

ConfigAPI::ConfigAPI(int _width, int _height, bool _fullscreen, float _difficulty, int _highscore){
	configData.winWidth = _width;
	configData.winHeight = _height;
	configData.fullscreen = _fullscreen;
	configData.difficulty = _difficulty;
	configData.highscore = _highscore;
}