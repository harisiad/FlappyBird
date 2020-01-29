#include "fb_window.h"

Window::Window()
{
	width = 0;
	height = 0;

	fullscreen = false;
}

void Window::init(int _width, int _height, bool _fullscreen)
{
	width = _width;
	height = _height;

	fullscreen = _fullscreen;
}
