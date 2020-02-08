#pragma once

#include <vector>

#ifndef DL_PROJECTILE_H_INCLUDED
#define DL_PROJECTILE_H_INCLUDED

#include "DL_Renderer.h"
#include "DL_Cannon.h"
//#include "DL_Map_Handler.h"
#include "DL_Player.h"

typedef struct
{
    float x;
    float y;
} SDL_fPoint;


typedef struct
{
    SDL_fPoint Position;
    SDL_fPoint Direction;
    char Type;
} Projectile_Info;


class DL_Projectile: public DL_Texture
{
public:

    DL_Projectile();
    ~DL_Projectile();

    void RenderTexture( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P );

    void MoveProjectile( int P );

    void MoveNRender ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H );

    void CreateProjectile( int Cannons_Amount, Cannon_Info *Cannon, int Player_PosX, int Player_PosY );

    void AddProjectile( Projectile_Info New_Projectile );

    int getProjectilePosX();
    int getProjectilePosY();

    char getProjectileType();

    void Collision( DL_Player *Player1, const int MAP_W, const int MAP_H, const int SCREEN_W, const int SCREEN_H );

    float getVecLength( SDL_fPoint P );

private:

    std::vector<Projectile_Info> Projectile;

    const int PROJECTILE_RADIUS = 3;

};

#endif // DL_PROJECTILE_H_INCLUDED
