
#include <SDL.h>
#include <SDL_image.h>

#include <iostream>
#include <string>

#include "DL_Renderer.h"

using namespace std;

DL_Texture::DL_Texture()
{
    /// setting the default type to zero
    Type = '0';

    /// setting the pointers to NULLs
    Texture = NULL;

    Tile = NULL;

    /// tiles amount to zero
    Tiles_Amount = 0;

    /// texture width and height to zeros
    //Texture_Width = 0;

    //Texture_Height = 0;
}

DL_Texture::~DL_Texture()
{
    /// freeing texture
    FreeTexture();
}

void DL_Texture::FreeTexture()
{
    /// destroying the texture
    if ( Texture != NULL )
    {
        SDL_DestroyTexture( Texture );
        Texture = NULL;
    }

    /// deleting the tiles
    if ( Tile != NULL )
    {
        delete [] Tile;
        Tile = NULL;
    }

    /// resetting variables
    Tiles_Amount = 0;

    Type = '0';

    //Texture_Width = 0;
    //Texture_Height = 0;
}

bool DL_Texture::LoadTexture( string path, SDL_Renderer *&mainRenderer )
{
    /// loading the png file to the surface
    SDL_Surface *LoadedSurface = IMG_Load ( path.c_str());

    /// check for success
    if ( LoadedSurface == NULL )
    {
        cout<<"Could not load image: "<<path.c_str()<<" as surface.\nError: "<<IMG_GetError();
    }
    else
    {
        /// creating texture from surface
        Texture = SDL_CreateTextureFromSurface( mainRenderer, LoadedSurface );

        /// check for success
        if ( Texture == NULL )
        {
            cout<< "Could not create texture from: "<<path.c_str()<<endl<<"Error: "<<SDL_GetError()<<endl;
        }/*
        else
        {
            SDL_QueryTexture( Texture, NULL, NULL, &Texture_Width, &Texture_Height );
        }*/
        /// freeing the surface
        SDL_FreeSurface( LoadedSurface );
    }

    /// return texture success
    return Texture != NULL;
}



bool DL_Texture::CreateTiles( int a )
{
    /// allocating memory for tiles array of size 'a'
    Tile = new SDL_Rect [a];

    /// check for success
    if ( Tile == NULL )
    {
        cout<<"Failed to allocate memory for tiles.\n";
    }
    else
    {
        /// assign the tiles amount
        Tiles_Amount = a;

        /// switch of object type
        switch (Type)
        {
        case 'M': /// map type
        case 'C': /// cannon type
            {
                Tile[0].x = 0;
                Tile[0].y = 0;
                Tile[0].w = 32;
                Tile[0].h = 32;

                Tile[1].x = 32;
                Tile[1].y = 0;
                Tile[1].w = 32;
                Tile[1].h = 32;

                Tile[2].x = 64;
                Tile[2].y = 0;
                Tile[2].w = 32;
                Tile[2].h = 32;

                Tile[3].x = 96;
                Tile[3].y = 0;
                Tile[3].w = 32;
                Tile[3].h = 32;

                break;
            }
        case 'P': /// player type
            {
                /// horizontal movement
                Tile[0].x = 0;
                Tile[0].y = 0;
                Tile[0].w = 9;
                Tile[0].h = 21;

                Tile[1].x = 9;
                Tile[1].y = 0;
                Tile[1].w = 11;
                Tile[1].h = 21;

                Tile[2].x = 20;
                Tile[2].y = 0;
                Tile[2].w = 11;
                Tile[2].h = 21;

                Tile[3].x = 31;
                Tile[3].y = 0;
                Tile[3].w = 11;
                Tile[3].h = 21;

                Tile[4].x = 42;
                Tile[4].y = 0;
                Tile[4].w = 11;
                Tile[4].h = 21;

                /// vertical movement
                Tile[5].x = 0;
                Tile[5].y = 22;
                Tile[5].w = 21;
                Tile[5].h = 9;

                Tile[6].x = 21;
                Tile[6].y = 21;
                Tile[6].w = 21;
                Tile[6].h = 11;

                Tile[7].x = 42;
                Tile[7].y = 21;
                Tile[7].w = 21;
                Tile[7].h = 11;

                Tile[8].x = 21;
                Tile[8].y = 32;
                Tile[8].w = 21;
                Tile[8].h = 11;

                Tile[9].x = 42;
                Tile[9].y = 32;
                Tile[9].w = 21;
                Tile[9].h = 11;

                break;
            }
        case 'R': /// projectile type
            {
                Tile[0].x = 0;
                Tile[0].y = 0;
                Tile[0].w = 7;
                Tile[0].h = 7;

                Tile[1].x = 7;
                Tile[1].y = 0;
                Tile[1].w = 7;
                Tile[1].h = 7;

                Tile[2].x = 14;
                Tile[2].y = 0;
                Tile[2].w = 7;
                Tile[2].h = 7;

                Tile[3].x = 21;
                Tile[3].y = 0;
                Tile[3].w = 7;
                Tile[3].h = 7;

                break;
            }
        case 'B': /// bonus type
            {
                Tile[0].x = 0;
                Tile[0].y = 0;
                Tile[0].w = 10;
                Tile[0].h = 10;

                Tile[1].x = 10;
                Tile[1].y = 0;
                Tile[1].w = 10;
                Tile[1].h = 10;

                Tile[2].x = 20;
                Tile[2].y = 0;
                Tile[2].w = 10;
                Tile[2].h = 10;

                Tile[3].x = 30;
                Tile[3].y = 0;
                Tile[3].w = 10;
                Tile[3].h = 10;

                break;
            }
        case 'U': /// UI type
            {
                Tile[0].x = 0;
                Tile[0].y = 0;
                Tile[0].w = 178;
                Tile[0].h = 51;

                Tile[1].x = 178;
                Tile[1].y = 0;
                Tile[1].w = 149;
                Tile[1].h = 51;

                Tile[2].x = 327;
                Tile[2].y = 0;
                Tile[2].w = 153;
                Tile[2].h = 51;

                Tile[3].x = 0;
                Tile[3].y = 51;
                Tile[3].w = 508;
                Tile[3].h = 51;

                Tile[4].x = 0;
                Tile[4].y = 102;
                Tile[4].w = 209;
                Tile[4].h = 51;

                Tile[5].x = 209;
                Tile[5].y = 102;
                Tile[5].w = 225;
                Tile[5].h = 51;

                break;
            }
        }

    }
    /// return success
    return Tile != NULL;

}
void DL_Texture::setType( char T )
{
    /// set the object's type
    Type = T;
}

SDL_Rect* DL_Texture::getTile()
{
    /// tile array getter
    return Tile;
}

int DL_Texture::getTilesAmount()
{
    /// tile amount getter
    return Tiles_Amount;
}

SDL_Texture* DL_Texture::getTexture()
{
    /// texture getter
    return Texture;
}

