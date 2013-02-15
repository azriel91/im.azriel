/*
 * Main.cpp
 *
 *  Created on: 4/11/2012
 *      Author: azriel
 */

#include "Main.h"

#ifdef _WIN32
int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
#else
#ifdef __linux__
int main(int argc, char **argv) {
#endif
#endif

	HeroQuestApplication* const app = new HeroQuestApplication(1024, 768);
	app->start();
	app->mainLoop();

	return 0;
}
