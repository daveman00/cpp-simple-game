#ifndef DL_GAME_H_INCLUDED
#define DL_GAME_H_INCLUDED

#include "DL_Renderer.h"
#include "DL_Map_Handler.h"
#include "DL_Player.h"
#include "DL_Cannon.h"
#include "DL_Projectile.h"
#include "DL_Menu.h"

class DL_Game
{
    const int SCREEN_W = 800;
    const int SCREEN_H = 600;
    //const SDL_Point SCREEN_CENTER = { SCREEN_W/2, SCREEN_H/2 };

    SDL_Window *mainFrame;
    SDL_Renderer *mainRenderer;

    DL_Map *Map1;
    DL_Player *Player1;
    DL_Cannon *Cannon1;
    DL_Projectile *Projectile1;
    DL_Menu *Menu1;


    bool quit;
    bool gameover;
    bool win;

    bool keyState[6]; /// keypressed; 0:up, 1:down, 2:left, 3:right; 4:movement: horizontal-false, vertical-true; 5: animation flag

    SDL_Event e;

    bool InitializeSDL();

    bool Allocate();

    bool Load();

    void Set();

    void CloseSDL();

    bool GameOver();

    bool Winner();

    void MainLoop();

    void CollisionDetector ();

    void RenderScene();

    void FireNRun ( Uint32 *CurrentTick, Uint32 *StartTick );

    void EventQueue();

    bool Start();

public:

    DL_Game();
    ~DL_Game();

    void Run();


};

#endif // DL_GAME_H_INCLUDED
