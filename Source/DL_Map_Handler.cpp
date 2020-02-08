
#include <SDL.h>

#include <iostream>
#include <stdio.h>
#include <fstream>
//#include <math.h>

#include "DL_Map_Handler.h"
#include "DL_Renderer.h"

using namespace std;

DL_Map::DL_Map()
{
    /// setting the type of the object to 'M' - map
    setType( 'M' );

    /// initialization of variables
    Map = NULL;

    Map_Rows = 0;

    Map_Columns = 0;

    MAP_H = 0;

    MAP_W = 0;

    //Bonuses_Amount = 0;
}

DL_Map::~DL_Map()
{
    //FreeTexture();
    /// freeing the txt map
    FreeMap();

}

void DL_Map::FreeMap()
{
    /// checking the pointer's address
    if ( Map != NULL )
    {
        /// releasing the memory
        delete [] Map;

        Map = NULL;
    }

    /// setting the map variables to zeros
    Map_Rows = 0;
    Map_Columns = 0;

    MAP_W = 0;
    MAP_H = 0;
}

bool DL_Map::AllocateMap( int x, int y )
{
    /// setting the map rows and columns
    Map_Rows = x;
    Map_Columns = y;

    MAP_W = y * 32;
    MAP_H = x * 32;

    /// allocating the memory for the map
    Map = new char [ Map_Rows * Map_Columns ];

    /// returning success or failure
    return Map != NULL;
}

bool DL_Map::LoadMap( string path, int x, int y )
{
    /// freeing the previous map
    FreeMap();

    /// success flag
    bool s = true;

    /// allocation of new txt map
    if ( !AllocateMap( x, y) )
    {
        /// failure == resetting the values and returning failure flag
        cout<<"Could not allocate memory for map.\n";
        Map_Rows = 0;
        Map_Columns = 0;

        s = false;
    }
    else
    {
        /// txt variable
        ifstream mapa;

        /// opening the txt file
        mapa.open ( path.c_str(), ifstream::in );

        /// checking the success of opening
        if ( mapa == NULL )
        {
            /// failure sets the flag
            cout<<"Could not open map file.\n";
            s = false;
        }
        else
        {
            /// character handling variable
            char k;

            /// loops for loading characters from txt file
            for ( int i = 0; i < Map_Rows; i++ )
            {
                for ( int j = 0; j < Map_Columns; j++ )
                {
                    mapa.get( k );



                    /// until EOF is not reached we check for the '\n' characters and store the others in the char table
                    if ( k != EOF )
                    {
                        if ( k != '\n' )
                        {
                            Map[ (i * Map_Columns ) + j] = k;
                        }
                        else j--;
                    }



                }
            }
            /// closing the txt file
            mapa.close();

        }
    }
    /// returning the success flag
    return s;

}

char *DL_Map::getMap()
{
    /// txt map getter
    return Map;
}

void DL_Map::RenderTexture ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P )
{
    /// setting the map position to the center of the window
    int Map_PosX = (SCREEN_W - MAP_W) /2;
    int Map_PosY = (SCREEN_H - MAP_H) /2;

    /// getting the tiles of the map
    SDL_Rect *Tile = getTile();

    /// getting the texture of the map
    SDL_Texture *Texture = getTexture();

    /// setting the destination rectangle ( x, y, w, h )
    SDL_Rect RenderQuad = { Map_PosX, Map_PosY, Tile[0].w, Tile[0].h };


    if ( Tile != NULL && Texture != NULL )
    {
        /// loops for rendering the map
        for ( int i = 0; i < Map_Rows; i++ )
        {
            for ( int j = 0; j < Map_Columns; j++ )
            {
                /// getting the current character in the txt map
                char T = Map[ (i*Map_Columns) + j ];

                switch ( T )
                {

                case 'H': /// 'H' == health bonus
                case 'S': /// 'S' == speed bonus
                case 'I': /// 'I' == invulnerability bonus
                case 'F': /// 'F' == freezing bonus
                case '0': /// '0' == path
                    {
                        /// render it all as path tile ( bonuses need path background )
                        RenderQuad = { (Map_PosX + (j*Tile[0].w)), (Map_PosY + (i*Tile[0].h)), Tile[0].w, Tile[0].h };
                        SDL_RenderCopy ( mainRenderer, Texture, &Tile[0], &RenderQuad );
                        break;
                    }

                case 'N': /// 'N' == normal cannon: normal dmg
                case 'R': /// 'R' == red cannon: double dmg
                case 'G': /// 'G' == green cannon: slow effect
                case 'B': /// 'B' == blue cannon: freeze effect
                case '1': /// '1' == background
                default:
                    {
                        /// render it all as background ( cannons need this background )
                        RenderQuad = { (Map_PosX + (j*Tile[1].w)), (Map_PosY + (i*Tile[1].h)), Tile[1].w, Tile[1].h };
                        SDL_RenderCopy ( mainRenderer, Texture, &Tile[1], &RenderQuad );
                        break;
                    }
                case '2':
                    {
                        /// tree or some other decoration tile
                        RenderQuad = { (Map_PosX + (j*Tile[2].w)), (Map_PosY + (i*Tile[2].h)), Tile[2].w, Tile[2].h };
                        SDL_RenderCopy ( mainRenderer, Texture, &Tile[2], &RenderQuad );
                        break;
                    }
                case '3':
                    {
                        /// swamp or some other decoration tile
                        RenderQuad = { (Map_PosX + (j*Tile[3].w)), (Map_PosY + (i*Tile[3].h)), Tile[3].w, Tile[3].h };
                        SDL_RenderCopy ( mainRenderer, Texture, &Tile[3], &RenderQuad );
                        break;
                    }

                }




            }
        }
    } else cout<<"Failed to assign tile and texture addresses for map usage.\n";


    /// setting the pointers to NULLs
    Tile = NULL;
    Texture = NULL;

}

int DL_Map::getMapColumns()
{
    /// map columns getter
    return Map_Columns;
}

int DL_Map::getMapRows()
{
    /// map rows getter
    return Map_Rows;
}

const int DL_Map::getMAP_H()
{
    /// map height getter
    return MAP_H;
}

const int DL_Map::getMAP_W()
{
    /// map width getter
    return MAP_W;
}

int DL_Map::getMapStartingPosition( const int SCREEN_H, int Player_Height )
{
    /// loop for searching through the first column of txt map
    for ( int i = 0; i < Map_Rows; i++ )
    {
        /// character handler
        char T = Map[ i*Map_Columns ];

        /// if '0' character found ( path )
        if ( T == '0' )
        {
            /// set the i variable to i times tile height plus the difference between the screen height and map height plus center the player's position according to the tile
            i = (i*32) + ((SCREEN_H - MAP_H)/2) + ((32 - Player_Height)/2);
            /// return the position i
            return i;
        }

    }
}
/*
/// getters for cannons and bonuses amount
int DL_Map::getBonusesAmount()
{
    return Bonuses_Amount;
}

int DL_Map::getCannonsAmount()
{
    return Cannons_Amount;
}*/


