#include <iostream>
#include "engine.h"

void Render(Renderer& r) {
	std::cout << "RENDER";
}

void Update() {
	std::cout << "UPDATE";
}

int main() {

	engine Engine = engine("Hello World", 500, 500);
	Engine.setRenderCallback(Render);
	Engine.setUpdateCallback(Update);
	Engine.run();





	return 1;
}
