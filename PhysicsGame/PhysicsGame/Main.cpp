#include "stdafx.h"
#include "Game.h"
#include <stdio.h>      /* printf, NULL */
#include <stdlib.h>     /* srand, rand */
#include <time.h> 

int main()
{
	srand(time(NULL));

	Game game;

	game.Run();

	return 0;
}