#include "fb_game.h"

int main(int argc, char **argv)
{
	FBGame* game = new FBGame();

	game->InitializeGameData();
	game->InitializeWindow();
	game->InstallSound();
	game->RegisterEventSources();

	game->ActsPlayLoop();

	game->DestroyGameData();

	return 0;
}