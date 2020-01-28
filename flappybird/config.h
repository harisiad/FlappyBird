#pragma once

class ConfigAPI {
private:
	struct Data {
		int winWidth;
		int winHeight;
		bool fullscreen;

		float difficulty;

		int highscore;
	};
protected:
	Data	configData;
public:
	ConfigAPI();
	ConfigAPI(int, int, bool, float, int);
	Data&	GetData() { return configData; }

	int		WinWidth() { return configData.winWidth; }
	int		WinHeight() { return configData.winHeight; }
	bool	WinFullscreen() { return configData.fullscreen; }
	float	GetDifficulty() { return configData.difficulty; }
	int		GetHighScore() { return configData.highscore; }
};