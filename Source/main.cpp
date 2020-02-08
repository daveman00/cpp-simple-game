#include <SDL.h>

#include <string>
#include <windows.h>

#include "DL_Game.h"

/**
 *  Deadly Labyrinth
 *
 *  Graphics, Programming by
 *
 *  Dawid Czyrny
 *  czyrny.dawid@gmail.com
 */


int main ( int argc, char *argv[] )
{
    DL_Game *DeadlyLabyrinth = new DL_Game;

    DeadlyLabyrinth->Run();

    delete DeadlyLabyrinth;

    system("Pause");

    return 0;
}

