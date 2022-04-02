#include "object.h"

object2D background = object2D();
std::vector<object2D> resources;

void gameInit() {
	background.loadImage(_T("img\\background.png"));


	initgraph(background.getWidth(), background.getHeight(), 1);
	resources.push_back(background);
}

void gameDraw() {
	BeginBatchDraw();                                               // Start drawing

	for (object2D obj : resources) {
		obj.draw();
	}

	EndBatchDraw();
}

void gameUpdate() {

}

int main() {
	gameInit();
	while (1) {
		gameDraw();
	}
}
