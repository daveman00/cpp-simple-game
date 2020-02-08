#pragma once

#ifndef DL_MAP_HANDLER_H_INCLUDED
#define DL_MAP_HANDLER_H_INCLUDED

#include "DL_Renderer.h"

/// map handling class with inheritance of a texture handling class
class DL_Map : public DL_Texture
{
public:
    /// constructor & destructor
    DL_Map();
    ~DL_Map();

    /// allocation of the memory for storing the txt map
    bool AllocateMap( int x, int y );

    /// freeing the memory for storing the txt map
    void FreeMap();

    /// loading the txt map ( path, rows, columns )
    bool LoadMap ( std::string path, int x, int y );

    /// getter for the txt map
    char *getMap();

    /// overwritten function used for rendering the map
    void RenderTexture ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P = 0 );

    /// getters for map columns and rows
    int getMapRows();
    int getMapColumns();

    /// getters for map width and height
    const int getMAP_W();
    const int getMAP_H();

    /// function finds the occurrence of '0' character in the txt map in the first column which indicates the starting position of the player
    int getMapStartingPosition( const int SCREEN_H, int Player_Height );

    //int getCannonsAmount();

    //int getBonusesAmount();

private:
    /// map constants
    int MAP_W;
    int MAP_H;

    /// pointer to txt map
    char *Map;

    /// amount of map rows
    int Map_Rows;

    /// amount of map columns
    int Map_Columns;

    //int Cannons_Amount;

    //int Bonuses_Amount;

};

#endif // DL_MAP_HANDLER_H_INCLUDED
