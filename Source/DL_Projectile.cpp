#include <SDL.h>
#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>
#include <math.h>

#include "DL_Renderer.h"
#include "DL_Projectile.h"
#include "DL_Cannon.h"

DL_Projectile::DL_Projectile()
{
    setType('R');

    std::vector<Projectile_Info>().swap(Projectile);

    //Projectiles_Amount = 0;
}

DL_Projectile::~DL_Projectile()
{
    std::vector<Projectile_Info>().swap(Projectile);

    //Projectiles_Amount = 0;

}

void DL_Projectile::RenderTexture( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P )
{
    SDL_Rect *Tile = getTile();

    SDL_Texture *Texture = getTexture();

    SDL_Rect RenderQuad = { 0 };

    if ( Tile != NULL && Texture != NULL && P < Projectile.size() )
    {
            switch ( Projectile[P].Type )
            {
            case 'N':
                {
                    RenderQuad = { Projectile[P].Position.x + PROJECTILE_RADIUS, Projectile[P].Position.y + PROJECTILE_RADIUS, Tile[0].w, Tile[0].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[0], &RenderQuad );
                    break;
                }
            case 'R':
                {
                    RenderQuad = { Projectile[P].Position.x + PROJECTILE_RADIUS, Projectile[P].Position.y + PROJECTILE_RADIUS, Tile[1].w, Tile[1].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[1], &RenderQuad );
                    break;
                }
            case 'G':
                {
                    RenderQuad = { Projectile[P].Position.x + PROJECTILE_RADIUS, Projectile[P].Position.y + PROJECTILE_RADIUS, Tile[2].w, Tile[2].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[2], &RenderQuad );
                    break;
                }
            case 'B':
                {
                    RenderQuad = { Projectile[P].Position.x + PROJECTILE_RADIUS, Projectile[P].Position.y + PROJECTILE_RADIUS, Tile[3].w, Tile[3].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[3], &RenderQuad );
                    break;
                }
            }

    } else std::cout<<"Could not assign adresses of tiles and texture for projectiles' usage.\n";
}


void DL_Projectile::MoveProjectile( int P )
{
    Projectile[P].Position.x += PROJECTILE_RADIUS*Projectile[P].Direction.x;
    Projectile[P].Position.y += PROJECTILE_RADIUS*Projectile[P].Direction.y;


}

void DL_Projectile::MoveNRender ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H )
{
    for ( int i = 0; i < Projectile.size(); i++ )
    {
        MoveProjectile( i );

        RenderTexture ( mainRenderer, SCREEN_W, SCREEN_H, i );
    }
}

void DL_Projectile::CreateProjectile( int Cannons_Amount, Cannon_Info *Cannon, int Player_PosX, int Player_PosY )
{
    srand(time(NULL));

    int t = rand() % (2*Cannons_Amount) + 1;

    if ( t > 0 && t < Cannons_Amount )
    {
        Projectile_Info New_Projectile;

        New_Projectile.Type = Cannon[t].Type;
        New_Projectile.Position.x = Cannon[t].Position.x + 10;
        New_Projectile.Position.y = Cannon[t].Position.y  + 10;


        New_Projectile.Direction.x = Player_PosX - New_Projectile.Position.x;
        New_Projectile.Direction.y = Player_PosY - New_Projectile.Position.y;

        float Length = getVecLength( New_Projectile.Direction );

        New_Projectile.Direction.x = ( New_Projectile.Direction.x ) / Length;
        New_Projectile.Direction.y = ( New_Projectile.Direction.y ) / Length;

        AddProjectile( New_Projectile );
    }


}

void DL_Projectile::AddProjectile( Projectile_Info New_Projectile )
{
    Projectile.push_back( New_Projectile );
    //Projectiles_Amount = Projectile.size();
}

float DL_Projectile::getVecLength( SDL_fPoint P )
{
    return ( sqrt( (P.x*P.x) + (P.y*P.y) ) );
}

void DL_Projectile::Collision( DL_Player *Player1, const int MAP_W, const int MAP_H, const int SCREEN_W, const int SCREEN_H )
{
    for ( int i = 0; i < Projectile.size(); i++ )
    {
        /// map collision
        if (       ( ( Projectile[i].Position.x + 3*PROJECTILE_RADIUS ) > ( ( SCREEN_W - MAP_W )/2 + MAP_W ) )
                || ( ( Projectile[i].Position.x + PROJECTILE_RADIUS ) < ( ( SCREEN_W - MAP_W )/2 ) )
                || ( ( Projectile[i].Position.y + 3*PROJECTILE_RADIUS ) > ( ( SCREEN_H - MAP_H )/2 + MAP_H ) )
                || ( ( Projectile[i].Position.y + PROJECTILE_RADIUS ) < ( SCREEN_H - MAP_H )/2 )
            )
        {
            Projectile.erase( Projectile.begin() + i );
        }

        if (         ( ( Projectile[i].Position.x + 3*PROJECTILE_RADIUS ) > ( Player1->getPlayerPosX() ) )
                &&   ( ( Projectile[i].Position.y + 3*PROJECTILE_RADIUS ) > ( Player1->getPlayerPosY() ) )
                &&   ( ( Projectile[i].Position.x + PROJECTILE_RADIUS ) < ( Player1->getPlayerPosX() + Player1->getPlayerWidth() ) )
                &&   ( ( Projectile[i].Position.y + PROJECTILE_RADIUS ) < ( Player1->getPlayerPosY() + Player1->getPlayerHeight() ) )

            )
        {
            switch ( Projectile[i].Type )
            {
            case 'N':
                {
                    Player1->setPlayerHealth( Player1->getPlayerHealth() - 5 );
                    break;
                }
            case 'R':
                {
                    Player1->setPlayerHealth( Player1->getPlayerHealth() - 20 );
                    break;
                }
            case 'B':
                {
                    Player1->setPlayerHealth( Player1->getPlayerHealth() - 10 );
                    //Player1->setPlayerSpeedModifier( 0 );
                    break;
                }
            case 'G':
                {
                    Player1->setPlayerHealth( Player1->getPlayerHealth() - 15 );
                    //Player1->setPlayerSpeedModifier( 2 );
                    break;
                }
            }
            //Player1->setPlayerHealth( Player1->getPlayerHealth() - 20 );
            Projectile.erase( Projectile.begin() + i );
        }

    }
}




