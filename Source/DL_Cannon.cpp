#include <SDL.h>
#include <iostream>

#include "DL_Renderer.h"
#include "DL_Cannon.h"

DL_Cannon::DL_Cannon()
{
    setType( 'C' );

    Cannon = NULL;

    Cannons_Amount = 0;

    Map = NULL;

    Map_Columns = 0;

    Map_Rows = 0;
}

DL_Cannon::~DL_Cannon()
{
    if ( Cannon != NULL )
    {
        /// releasing the memory
        delete [] Cannon;

        Cannon = NULL;
        Cannons_Amount = 0;
    }



    Map = NULL;

    Map_Columns = 0;

    Map_Rows = 0;
}

void DL_Cannon::RenderTexture( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P )
{
    SDL_Rect *Tile = getTile();

    SDL_Texture *Texture = getTexture();

    SDL_Rect RenderQuad = { 0 };

    int i = 0;

    if ( Tile != NULL && Texture != NULL )
    {
        while ( i < Cannons_Amount )
        {
            switch ( Cannon[i].Type )
            {
            case 'N':
                {
                    RenderQuad = { Cannon[i].Position.x, Cannon[i].Position.y, Tile[0].w, Tile[0].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[0], &RenderQuad );
                    break;
                }
            case 'R':
                {
                    RenderQuad = { Cannon[i].Position.x, Cannon[i].Position.y, Tile[1].w, Tile[1].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[1], &RenderQuad );
                    break;
                }
            case 'G':
                {
                    RenderQuad = { Cannon[i].Position.x, Cannon[i].Position.y, Tile[2].w, Tile[2].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[2], &RenderQuad );
                    break;
                }
            case 'B':
                {
                    RenderQuad = { Cannon[i].Position.x, Cannon[i].Position.y, Tile[3].w, Tile[3].h };
                    SDL_RenderCopy ( mainRenderer, Texture, &Tile[3], &RenderQuad );
                    break;
                }
            }
            i++;
        }

    } else std::cout<<"Failed to assign tile and texture addresses for cannons' usage.\n";


    Tile = NULL;
    Texture = NULL;
    RenderQuad = {0};
    i = 0;
}

void DL_Cannon::setMap( char* M )
{
    Map = M;
}

void DL_Cannon::setMapColumns( int C )
{
    Map_Columns = C;
}

void DL_Cannon::setMapRows( int R )
{
    Map_Rows = R;
}

void DL_Cannon::CountCannons()
{
    if ( Map != NULL )
    {
        for ( int i = 0; i < Map_Rows; i++ )
            {
                for ( int j = 0; j < Map_Columns; j++ )
                {
                    switch ( Map[ (i * Map_Columns ) + j] )
                    {
                    case 'N':
                    case 'R':
                    case 'B':
                    case 'G':
                        {
                            Cannons_Amount++;
                        }
                    }
                }

            }
    }
    else std::cout<<"Failed to assign map address for cannons usage.\n";


}

bool DL_Cannon::AllocateCannons()
{
    CountCannons();

    //std::cout<<Cannons_Amount<<std::endl;

    Cannon = new Cannon_Info[Cannons_Amount];

    return Cannon != NULL;
}

void DL_Cannon::setCannonsInfo( const int SCREEN_W, const int SCREEN_H )
{
    if ( AllocateCannons() )
    {
        int k = 0;

        while ( k < Cannons_Amount )
        {
            for ( int i = 0; i < Map_Rows; i++ )
                {
                    for ( int j = 0; j < Map_Columns; j++ )
                    {
                        //std::cout<<Map[ (i * Map_Columns ) + j];
                    switch ( Map[ (i * Map_Columns ) + j] )
                        {
                        case 'N':
                        case 'R':
                        case 'B':
                        case 'G':
                            {
                                Cannon[k].Position.x = (j * 32) + (( SCREEN_W - ( Map_Columns*32 )) /2) ;
                                Cannon[k].Position.y = (i * 32) + (( SCREEN_H - ( Map_Rows * 32 )) /2 );
                                Cannon[k].Type = Map[ (i * Map_Columns ) + j];


                                //std::cout<<"X: "<<Cannon[k].Position.x<<" Y: "<<Cannon[k].Position.y<<" T: "<<Cannon[k].Type<<std::endl;
                                k++;
                                break;
                            }
                        }
                    }
                }
        }
    } else std::cout<<"Failed to allocate memory for cannons' info.\n";


}

Cannon_Info* DL_Cannon::getCannonInfo()
{
    return Cannon;
}

int DL_Cannon::getCannonsAmount()
{
    return Cannons_Amount;
}


