#ifndef DL_MENU_H_INCLUDED
#define DL_MENU_H_INCLUDED

#include "DL_Renderer.h"
#include "DL_Timer.h"
#include <SDL_ttf.h>

class DL_Menu: public DL_Texture, public DL_Timer
{
    TTF_Font *Font;

    SDL_Texture *Health;

    SDL_Texture *Time;

    SDL_Point SCREEN_CENTER;

    SDL_Point Health_Pos;
    SDL_Point Time_Pos;

public:

    DL_Menu();
    ~DL_Menu();

    bool LoadFont ( std::string path, SDL_Renderer *&mainRenderer );

    bool RenderText( SDL_Renderer *&mainRenderer, int H );

    void FreeText();

    void RenderTexture( SDL_Renderer *&mainRenderer, const int SCREEN_W , const int SCREEN_H , int P = 0 );

    void setHPos( int x, int y );

    void setTPos ( int x, int y );

    void setSCenter ( int x, int y );
};


#endif // DL_MENU_H_INCLUDED
