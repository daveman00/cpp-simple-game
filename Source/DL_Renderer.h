#pragma once

#ifndef DL_RENDERER_H_INCLUDED
#define DL_RENDERER_H_INCLUDED


/// class used for texture management
class DL_Texture
{
public:
    /// constructor & destructor
    DL_Texture ();
    ~DL_Texture ();

    /// loading texture from png file
    bool LoadTexture ( std::string path, SDL_Renderer *&mainRenderer );

    /// freeing texture
    void FreeTexture ();

    /// pure virtual render function
    virtual void RenderTexture ( SDL_Renderer *&mainRenderer, const int SCREEN_W , const int SCREEN_H , int P ) = 0;

    /// cutting the texture into tiles ( amount of tiles )
    bool CreateTiles( int a );

    /// setter for type of the object ( type )
    void setType( char T );

    /// getter for tiles
    SDL_Rect *getTile();

    /// getter for tiles amount
    int getTilesAmount();

    /// texture getter
    SDL_Texture *getTexture();

protected:
    /// type of object variable
    char Type;

    /// texture variable
    SDL_Texture *Texture;

    /// pointer to tile array
    SDL_Rect *Tile;

    /// tiles amount variable
    int Tiles_Amount;

};

#endif // DL_RENDERER_H_INCLUDED
