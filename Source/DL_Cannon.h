#pragma once

#include <vector>

#ifndef DL_CANNON_H_INCLUDED
#define DL_CANNON_H_INCLUDED

#include "DL_Renderer.h"


typedef struct
{
    SDL_Point Position;
    char Type;
} Cannon_Info;

class DL_Cannon: public DL_Texture
{
public:

    DL_Cannon();
    ~DL_Cannon();

    void RenderTexture ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P = 0 );

    void setMap ( char *M );
    void setMapColumns ( int C );
    void setMapRows ( int R );

    void CountCannons();

    bool AllocateCannons();

    void setCannonsInfo( const int SCREEN_W, const int SCREEN_H );

    Cannon_Info *getCannonInfo();
    int getCannonsAmount();

private:

    Cannon_Info *Cannon;
    int Cannons_Amount;

    char *Map;
    int Map_Columns;
    int Map_Rows;
};

#endif // DL_CANNON_H_INCLUDED
