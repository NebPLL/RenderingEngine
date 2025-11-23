#include "engine.h"
#include <iostream>

engine::engine(const char* title, int width, int height)
{
	std::cout << "Hello World";
}

void engine::run()
{
	Renderer renderer;

	while (running) {

		if (renderCallback) renderCallback(renderer);
		if (updateCallback) updateCallback();
	}

}
