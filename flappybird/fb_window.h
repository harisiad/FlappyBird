#ifndef _FLAPPYBIRD_DISPLAY_WINDOW_H_
#define _FLAPPYBIRD_DISPLAY_WINDOW_H_

class Window
{
protected:
	int width;
	int height;

	bool fullscreen;
public:
	Window();

	void init(int, int, bool);
	void setWidth(int _width) { width = _width; }
	int getWidth() { return width; }
	void setHeight(int _height) { height = _height; }
	int getHeight() { return height; }

	bool getFullScreen() { return fullscreen; }
};

#endif