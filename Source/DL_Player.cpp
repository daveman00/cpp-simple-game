
#include <SDL.h>

#include <iostream>
#include <stdio.h>
#include <math.h>

#include "DL_Renderer.h"
#include "DL_Player.h"

using namespace std;

DL_Player::DL_Player( )
{
    /// setting player's type
    setType( 'P' );

    /// initialization of variables
    Player_PosX = 0;
    Player_PosY = 0;

    /// setting the default player's dimensions
    Player_Width = 9;
    Player_Height = 21;

    /// setting player's position change
    Player_Speed_X = 0;
    Player_Speed_Y = 0;

    /// setting the default player's effects
    Player_Health = 100;
    Player_Speed_Modifier = 1;
    Player_Freeze = false;
    Player_Invulnerability = false;
}

DL_Player::~DL_Player()
{
    /// resetting player's variables
    Player_PosX = 0;
    Player_PosY = 0;

    Player_Width = 0;
    Player_Height = 0;

    Player_Speed_X = 0;
    Player_Speed_Y = 0;

    Player_Health = 0;
    Player_Speed_Modifier = 0;
    Player_Freeze = false;
    Player_Invulnerability = false;
}

void DL_Player::HandleInput ( SDL_Event &e, bool *keyState )
{
    /// looking for keydown event and key repetition
    if( e.type == SDL_KEYDOWN && e.key.repeat == 0 )
    {
        /// switch for the ARROW keys
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                {
                    /// adjust speed in Y axis
                    Player_Speed_Y -= PLAYER_VEL * Player_Speed_Modifier;

                    /// reset the X axis movement
                    Player_Speed_X = 0;

                    /// set the UP arrow flag
                    /// reset to false
                    keyState[0] = true;
                    keyState[1] = false;
                    keyState[2] = false;
                    keyState[3] = false;

                   break;
                }
            case SDLK_DOWN:
                {
                    /// adjust the speed in Y axis
                    Player_Speed_Y += PLAYER_VEL * Player_Speed_Modifier;

                    /// reset the X axis movement
                    Player_Speed_X = 0;

                    /// set the DOWN arrow flag
                    /// rest to false
                    keyState[0] = false;
                    keyState[1] = true;
                    keyState[2] = false;
                    keyState[3] = false;

                    break;
                }
            case SDLK_LEFT:
                {
                    /// adjust the speed in X axis
                    Player_Speed_X -= PLAYER_VEL * Player_Speed_Modifier;

                    /// reset the Y axis movement
                    Player_Speed_Y = 0;

                    /// set the LEFT arrow flag
                    /// rest to false
                    keyState[0] = false;
                    keyState[1] = false;
                    keyState[2] = true;
                    keyState[3] = false;

                    break;
                }
            case SDLK_RIGHT:
                {
                    /// adjust speed in X axis
                    Player_Speed_X += PLAYER_VEL * Player_Speed_Modifier;

                    /// reset the Y axis movement
                    Player_Speed_Y = 0;

                    /// set the RIGHT arrow flag
                    /// rest to false
                    keyState[0] = false;
                    keyState[1] = false;
                    keyState[2] = false;
                    keyState[3] = true;

                    break;
                }
        }

    }

    /// looking for keyup event and key repetition
    else if( e.type == SDL_KEYUP && e.key.repeat == 0 )
    {
        /// switch of ARROW keys
        switch( e.key.keysym.sym )
        {
            case SDLK_UP:
                {
                    /// reset the Y axis movement
                    Player_Speed_Y = 0;

                    /// reset the UP arrow flag
                    keyState[0] = false;

                    break;
                }
            case SDLK_DOWN:
                {
                    /// reset the Y axis movement
                    Player_Speed_Y = 0;

                    /// reset the DOWN arrow flag
                    keyState[1] = false;
                    break;
                }

            case SDLK_LEFT:
                {
                    /// reset the X axis movement
                    Player_Speed_X = 0;

                    /// reset the LEFT arrow flag
                    keyState[2] = false;

                    break;
                }
            case SDLK_RIGHT:
                {
                    /// reset the X axis movement
                    Player_Speed_X = 0;

                    /// reset the RIGHT arrow flag
                    keyState[3] = false;

                    break;
                }
        }


    }
}

void DL_Player::MovePlayer( const int SCREEN_W, const int SCREEN_H, DL_Map *Map1 )
{
    /// change player's position in X axis
    Player_PosX += Player_Speed_X;

    /// change player's position in Y axis
    Player_PosY += Player_Speed_Y;


    if ( Collision( SCREEN_W, SCREEN_H, Map1 ) )
    {
        /// change player's position in X axis
    Player_PosX -= Player_Speed_X;
    //cout<<"Collision!\n";
    /// change player's position in Y axis
    Player_PosY -= Player_Speed_Y;
    }


}

bool DL_Player::Collision ( const int SCREEN_W, const int SCREEN_H, DL_Map *Map1 )
{
    int MAP_W = Map1->getMAP_W();
    int MAP_H = Map1->getMAP_H();

    if ( ( Player_PosX + Player_Width ) > ( MAP_W + ( SCREEN_W - MAP_W ) /2 ) )
        {
            /// if true: setting the position next to the to edge
            setPlayerPosX( MAP_W + (( SCREEN_W - MAP_W ) /2) - Player_Width );
        }
    /// checking the collision with left border of the map
    if ( Player_PosX <  ( ( SCREEN_W - MAP_W ) /2 ) )
        {
            /// if true: setting the position next to the to edge
            setPlayerPosX( ( SCREEN_W - MAP_W ) /2 );
        }
    /// checking the collision with upper border of the map
    if ( Player_PosY <  ( SCREEN_H - MAP_H ) /2 )
        {
            /// if true: setting the position next to the to edge
            setPlayerPosY( ( SCREEN_H - MAP_H ) /2 );
        }
    /// checking the collision with lower border of the map
    if ( ( Player_PosY + Player_Height ) > ( MAP_H + ( SCREEN_H - MAP_H ) /2 ) )
        {
            /// if true: setting the position next to the to edge
            setPlayerPosY( MAP_H + ( ( SCREEN_H - MAP_H ) /2 ) - Player_Height );
        }



    int i = floor( ( Player_PosX - (( SCREEN_W - MAP_W )/2) )/32 ); /// col
    int j = floor( ( Player_PosY - (( SCREEN_H - MAP_H )/2) )/32 ); /// row
    int k = floor( ( Player_PosX + Player_Width - (( SCREEN_W - MAP_W )/2) )/32 ); /// col
    int l = floor( ( Player_PosY + Player_Height - (( SCREEN_H - MAP_H )/2) )/32 ); /// row

    int Map_Columns = Map1->getMapColumns();
    char *Map = Map1->getMap();

    //cout<<i<<"\t"<<j<<"\t"<<k<<"\t"<<l<<"\n";

    //cout<<Map[ (j*Map_Columns) + i ]<<"\t"<<Map[ (j*Map_Columns) + k ]<<"\t"<<Map[ (l*Map_Columns) + i ]<<"\t"<<Map[ (l*Map_Columns) + k ]<<endl;

    if ( Map[ (j*Map_Columns) + i ] == '0'
        && Map[ (j*Map_Columns) + k ] == '0'
        &&Map[ (l*Map_Columns) + i ] == '0'
        && Map[ (l*Map_Columns) + k ] == '0' )
    {
        return false;
    }
    else
    {
        return true;
    }

}

void DL_Player::AnimatePlayer (SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, bool *keyState )
{
    /// get the tiles of the player
    SDL_Rect *Tile = getTile();

    if ( Tile != NULL )
    {
        /// all keys are up and the vertical movement flag is false
        if ( !keyState[0] && !keyState[1] && !keyState[2] && !keyState[3] && !keyState[4] )
        {
            /// set player's dimensions according to current tile
            setPlayerWidth( Tile[0].w );
            setPlayerHeight( Tile[0].h );

            /// render current tile
            RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 0 );
        }

        /// all keys are up and the vertical movement flag is true
        else if ( !keyState[0] && !keyState[1] && !keyState[2] && !keyState[3] && keyState[4] )
        {
            /// set player's dimensions according to current tile
            setPlayerWidth( Tile[5].w );
            setPlayerHeight( Tile[5].h );

            /// render current tile
            RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 5 );
        }

        /// movement UP
        else if ( keyState[0] )
        {
            /// set player's dimensions according to current tile
            setPlayerWidth( Tile[4].w );
            setPlayerHeight( Tile[4].h );

            /// according to animation flag render appropriate movement tile
            if ( keyState[5] )
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 6 );
            else
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 7 );

            /// set vertical movement flag
            keyState[4] = true;
        }

        /// movement down
        else if ( keyState[1] )
        {
            /// set player's dimensions according to current tile
            setPlayerWidth( Tile[8].w );
            setPlayerHeight( Tile[8].h );

            /// according to animation flag render appropriate movement tile
            if ( keyState[5] )
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 8 );
            else
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 9 );

            /// set vertical movement flag
            keyState[4] = true;
        }

        /// movement to the left
        else if ( keyState[2] )
        {
            /// set player's dimensions according to current tile
            setPlayerWidth( Tile[3].w );
            setPlayerHeight( Tile[3].h );

            /// according to animation flag render appropriate movement tile
            if ( keyState[5] )
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 3 );
            else
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 4 );

            /// reset the vertical movement flag
            keyState[4] = false;
        }

        /// movement to the right
        else if ( keyState[3] )
        {
            /// set player's dimensions according to current tile
            setPlayerWidth( Tile[1].w );
            setPlayerHeight( Tile[1].h );

            /// according to animation flag render appropriate movement tile
            if ( keyState[5] )
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 1 );
            else
                RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 2 );

            /// reset the vertical movement flag
            keyState[4] = false;
        }
    } else cout<<"Failed to assign address of tile for player's animation.\n";


}

void DL_Player::RenderTexture( SDL_Renderer *&mainRenderer, const int SCREEN_W, const int SCREEN_H, int P )
{
    /// get player's tiles
    SDL_Rect* Tile = getTile();

    /// get player's texture
    SDL_Texture *Texture = getTexture();

    if ( Tile != NULL && Texture != NULL )
    {
        /// set target render rectangle dimensions
        SDL_Rect RenderQuad = { 0, 0, Tile[P].w, Tile[P].h };

        /// set target render rectangle position
        RenderQuad.x = Player_PosX;
        RenderQuad.y = Player_PosY;

        /// render the texture's tile
        SDL_RenderCopy( mainRenderer, Texture, &Tile[P], &RenderQuad );


    } else cout<<"Failed to assign addresses of tile and texture for player's usage.\n";

    /// set pointers to NULLs
    Tile = NULL;
    Texture = NULL;
}

void DL_Player::setPlayerSpeedModifier( int SM )
{
    /// set player's speed coefficient
    Player_Speed_Modifier = SM;
}

int DL_Player::getPlayerSpeedModifier()
{
    /// get player's speed coefficient
    return Player_Speed_Modifier;
}

void DL_Player::setPlayerPosX( int X )
{
    /// set player's position in X axis
    Player_PosX = X;
}

int DL_Player::getPlayerPosX()
{
    /// get player's position in X axis
    return Player_PosX;
}

void DL_Player::setPlayerPosY( int Y )
{
    /// set player's position in Y axis
    Player_PosY = Y;
}

int DL_Player::getPlayerPosY()
{
    /// get player's position in Y axis
    return Player_PosY;
}

void DL_Player::setPlayerWidth( int W )
{
    /// set player's width
    Player_Width = W;
}

int DL_Player::getPlayerWidth()
{
    /// get player's width
    return Player_Width;
}

void DL_Player::setPlayerHeight ( int H )
{
    /// set player's height
    Player_Height = H;
}

int DL_Player::getPlayerHeight()
{
    /// get player's height
    return Player_Height;
}

void DL_Player::setPlayerHealth ( int H )
{
    /// set player's health
    Player_Health = H;
}

int DL_Player::getPlayerHealth ()
{
    /// get player's health
    return Player_Health;
}

void DL_Player::setPlayerSpeedX ( int S )
{
    /// set player's speed in X axis
    Player_Speed_X = S;
}

void DL_Player::setPlayerSpeedY( int S )
{
    /// set player's speed in Y axis
    Player_Speed_Y = S;
}

int DL_Player::getPlayerSpeedX ()
{
    /// get player's speed in X axis
    return Player_Speed_X;
}

int DL_Player::getPlayerSpeedY()
{
    /// get player's speed in Y axis
    return Player_Speed_Y;
}

void DL_Player::setPlayerInvulnerability ( bool I )
{
    /// set player's inv effect
    Player_Invulnerability = I;
}

bool DL_Player::getPlayerInvulnerability ()
{
    /// get player's inv effect
    return Player_Invulnerability;
}

void DL_Player::setPlayerFreeze ( bool F )
{
    /// set player's freeze effect
    Player_Freeze = F;
}

bool DL_Player::getPlayerFreeze ()
{
    /// get player's freeze effect
    return Player_Freeze;
}
