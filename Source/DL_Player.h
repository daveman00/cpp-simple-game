#pragma once

#ifndef DL_PLAYER_H_INCLUDED
#define DL_PLAYER_H_INCLUDED

#include "DL_Renderer.h"
#include "DL_Map_Handler.h"

/// player management class inheriting from texture class
class DL_Player: public DL_Texture
{
public:
    /// constructor & destructor
    DL_Player();
    ~DL_Player();

    /// rendering function ( P - tile number )
    void RenderTexture ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P );

    /// input handling function ( e - event handler, keyState - pointer to the state of arrow keys, movement axis and animation status
    void HandleInput( SDL_Event &e, bool *keyState );

    /// function used for player movement
    void MovePlayer( const int SCREEN_W, const int SCREEN_H, DL_Map *Map1 );

    /// animation of the player
    void AnimatePlayer ( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, bool *keyState );
    bool Collision ( const int SCREEN_W, const int SCREEN_H, DL_Map *Map1 );

    /// player's positon getters
    int getPlayerPosX();
    int getPlayerPosY();

    /// player's position setters
    void setPlayerPosX( int X );
    void setPlayerPosY( int Y );

    /// player's dimensions getters
    int getPlayerWidth();
    int getPlayerHeight();

    /// player's dimensions setters
    void setPlayerWidth( int W );
    void setPlayerHeight( int H );

    /// player's speed getters
    int getPlayerSpeedX();
    int getPlayerSpeedY();

    /// player's speed setters
    void setPlayerSpeedX( int S );
    void setPlayerSpeedY( int S );

    /// player's effect getters
    int getPlayerHealth();
    int getPlayerSpeedModifier();
    bool getPlayerFreeze();
    bool getPlayerInvulnerability();

    /// player's effect setters
    void setPlayerHealth( int H );
    void setPlayerSpeedModifier ( int SM );
    void setPlayerFreeze( bool F );
    void setPlayerInvulnerability( bool I );

private:

    /// player's velocity
    static const int PLAYER_VEL = 1;

    /// player's position
    int Player_PosX;
    int Player_PosY;

    /// player's dimensions
    int Player_Width;
    int Player_Height;

    /// player's position change
    int Player_Speed_X;
    int Player_Speed_Y;

    /// player's effect handlers
    int Player_Health;
    int Player_Speed_Modifier;
    bool Player_Freeze;
    bool Player_Invulnerability;
};

#endif // DL_PLAYER_H_INCLUDED
