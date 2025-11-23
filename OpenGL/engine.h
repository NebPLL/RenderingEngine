#pragma once
#include "Renderer.h"
#include <functional>

class engine
{

public:

	using RenderFunc = std::function<void(Renderer&)>;
	using UpdateFunc = std::function<void()>;

	engine(const char* title, int width, int height);

	void setRenderCallback(RenderFunc func) {
		renderCallback = func;
	}

	void setUpdateCallback(UpdateFunc func) {
		updateCallback = func;
	}

	void run();

private:
	bool running;
	RenderFunc renderCallback;
	UpdateFunc updateCallback;


};

