#include <SDL.h>
#include <string>
#include <stdio.h>
#include <sstream>

#include "DL_Menu.h"
#include "DL_Renderer.h"

template <typename T>
std::string NumberToString ( T Number )
{
    std::ostringstream ss;
    ss << Number;
    return ss.str();
}

DL_Menu::DL_Menu()
{
    setType( 'U' );

    Font = NULL;

    Health = NULL;

    Time = NULL;
}

DL_Menu::~DL_Menu()
{
    FreeText();

    TTF_CloseFont( Font );
	Font = NULL;
}

void DL_Menu::FreeText()
{
    /// destroying the texture
    if ( Health != NULL )
    {
        SDL_DestroyTexture( Health );
        Health = NULL;
    }

    /// destroying the texture
    if ( Time != NULL )
    {
        SDL_DestroyTexture( Time );
        Time = NULL;
    }
}

bool DL_Menu::LoadFont( std::string path, SDL_Renderer *&mainRenderer )
{
    Font = TTF_OpenFont( path.c_str(), 45 );

    return Font != NULL;
}

bool DL_Menu::RenderText ( SDL_Renderer *&mainRenderer, int H )
{
    FreeText();

    SDL_Color textColor = { 255, 255, 255 };

    //printf( "%f\n", (getTicks() / 1000.f));

    SDL_Surface* textHealth = TTF_RenderText_Solid( Font, (NumberToString<int>( H ).c_str()), textColor );
    SDL_Surface* textTime = TTF_RenderText_Solid( Font, (NumberToString<float>( getTicks() / 1000.f ).c_str()), textColor );

    if( textHealth == NULL )
	{
		printf( "Could not render health text info.\nError: %s\n", TTF_GetError() );
	}
	else
	{
		//Create texture from surface pixels
        Health = SDL_CreateTextureFromSurface( mainRenderer, textHealth );
		if( Health == NULL )
		{
			printf( "Could not create texture from rendered text.\nSDL Error: %s\n", SDL_GetError() );
		}

		//Get rid of old surface
		SDL_FreeSurface( textHealth );
	}

	if ( textTime == NULL )
    {
        printf( "Could not render time text info.\nError: %s\n", TTF_GetError() );
    }
    else
    {
        //Create texture from surface pixels
        Time = SDL_CreateTextureFromSurface( mainRenderer, textTime );
        if( Time == NULL )
		{
			printf( "Could not create texture from rendered text.\nSDL Error: %s\n", SDL_GetError() );
		}

		//Get rid of old surface
		SDL_FreeSurface( textTime );
	}

	//Return success
	return ( Health != NULL && Time != NULL );
}

void DL_Menu::RenderTexture ( SDL_Renderer *&mainRenderer, const int SCREEN_W , const int SCREEN_H , int P )
{
    SDL_Rect RenderQuad = { 0 };

    switch ( P )
    {
    case 2: /// pause
    case 3: /// start
    case 4: /// win
    case 5: /// lose
        {
            //printf( "%d %d\n", SCREEN_CENTER.x, SCREEN_CENTER.y );
            RenderQuad = { (SCREEN_CENTER.x - ((Tile[P].w)/2) ), ( SCREEN_CENTER.y - ((Tile[P].h)/2) ), Tile[P].w, Tile[P].h };
            SDL_RenderCopy ( mainRenderer, Texture, &Tile[P], &RenderQuad );
            if ( P == 3 ) break;
        }
    case 0: /// health
    case 1: /// time
        {
            RenderQuad = { Health_Pos.x, Health_Pos.y - Tile[0].h, Tile[0].w, Tile[0].h };
            SDL_RenderCopy ( mainRenderer, Texture, &Tile[0], &RenderQuad );

            int w = 0, h = 0;
            SDL_QueryTexture( Health, NULL, NULL, &w, &h );

            RenderQuad = { Health_Pos.x + Tile[0].w, Health_Pos.y - Tile[0].h, w, h };
            SDL_RenderCopy ( mainRenderer, Health, NULL, &RenderQuad );

            SDL_QueryTexture( Time, NULL, NULL, &w, &h );

            RenderQuad = { Time_Pos.x - 2*Tile[1].w, Time_Pos.y - Tile[1].h, Tile[1].w, Tile[1].h };
            SDL_RenderCopy ( mainRenderer, Texture, &Tile[1], &RenderQuad );

            RenderQuad = { Time_Pos.x - Tile[1].w, Time_Pos.y - Tile[1].h, w, h };
            //printf("%d %d\n", w, h );
            SDL_RenderCopy ( mainRenderer, Time, NULL, &RenderQuad );
            break;
        }

    }
}

void DL_Menu::setHPos( int x, int y )
{
    Health_Pos.x = x;
    Health_Pos.y = y;
}
void DL_Menu::setTPos ( int x, int y )
{
    Time_Pos.x = x;
    Time_Pos.y = y;
}

void DL_Menu::setSCenter ( int x, int y )
{
    SCREEN_CENTER.x = x;
    SCREEN_CENTER.y = y;
}
