// Include libraries
#define _CRT_SECURE_NO_WARNINGS/////////////////////////////////////
// Include
#include "game.h"
#include <stdio.h>

// Pragma
#ifndef _DEBUG
#	pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
#endif

// Main
int main()
{
	Game game;

	game.setupSystem();
	game.initialize();

	while (game.loop());

	game.shutdown();

	return 0;
}
