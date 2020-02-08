#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>

#include <iostream>
#include <string>

#include "DL_Game.h"
//#include "DL_Menu.h"

using namespace std;


DL_Game::DL_Game()
{
    mainFrame = NULL;
    mainRenderer = NULL;

    Map1 = NULL;
    Player1 = NULL;
    Cannon1 = NULL;
    Projectile1 = NULL;
    Menu1 = NULL;

    quit = false;
    gameover = false;
    win = false;

    keyState[6] = { false };
}

DL_Game::~DL_Game()
{
    CloseSDL();
}

bool DL_Game::Allocate()
{
    Map1 = new DL_Map;
    Player1 = new DL_Player;
    Cannon1 = new DL_Cannon;
    Projectile1 = new DL_Projectile;
    Menu1 = new DL_Menu;

    if ( Map1 != NULL && Player1 != NULL && Cannon1 != NULL && Projectile1 != NULL && Menu1 != NULL ) return true;
    else return false;
}

bool DL_Game::InitializeSDL()
{
    /// success flag
    bool s = true;

    /// video subsystems initialization
    if ( SDL_Init ( SDL_INIT_VIDEO ) < 0 )
    {
        cout<<"Could not initialize SDL.\nError: "<<SDL_GetError()<<endl;
        s = false;
    }
    else
    {
        /// creating main window
        mainFrame = SDL_CreateWindow ( "DeadlyLabyrinth", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN );

        if ( mainFrame == NULL )
        {
            cout<<"Window could not be created.\nError: "<<SDL_GetError()<<endl;
            s = false;
        }
        else
        {
            /// setting the linear filtering for textures
            if ( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) )
            {
                cout<<"Warning: Linear texture filtering not enabled.\n";
            }

            /// creating the main renderer with hardware acceleration
            mainRenderer = SDL_CreateRenderer( mainFrame, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

            if ( mainRenderer == NULL )
            {
                cout<<"Could not create main renderer.\nError: "<<SDL_GetError();
                s = false;
            }
            else
            {
                /// initialization of PNG files loading systems
                int img = IMG_INIT_PNG;
                if( !( IMG_Init( img ) & img ) )
                {
                    cout<<"Could not intitialize SDL_Image.\nError: "<<IMG_GetError()<<endl;
                    s = false;
                }

                 //Initialize SDL_ttf
                if( TTF_Init() == -1 )
                {
                    cout<< "Could not initialize SDL_ttf.\nError: "<<TTF_GetError()<<endl;
                    s = false;
                }

            }


        }
    }
    /// return success flag
    return s;
}


void DL_Game::CloseSDL()
{

    delete Projectile1;
    Projectile1 = NULL;

    delete Cannon1;
    Cannon1 = NULL;

    delete Player1;
    Player1 = NULL;

    delete Map1;
    Map1 = NULL;

    delete Menu1;
    Menu1 = NULL;

    /// destroying main window
    SDL_DestroyWindow( mainFrame );
	mainFrame = NULL;

    /// destroying the main renderer
	SDL_DestroyRenderer( mainRenderer );
	mainRenderer = NULL;



    /// quiting the IMG, TTF and SDL systems
    TTF_Quit();
    IMG_Quit();
	SDL_Quit();
}




void DL_Game::MainLoop()
{
    SDL_RenderClear( mainRenderer );
    /// filling the renderer with white color
    SDL_SetRenderDrawColor( mainRenderer, 0x00,0x00,0x00,0xFF );

    /// time variables used for animation of the player
    Uint32 StartTick = SDL_GetTicks();
    Uint32 CurrentTick = 0;


    /// game loop
    while( !quit )
    {
        CollisionDetector();

        FireNRun( &CurrentTick, &StartTick );

        RenderScene();

        quit = GameOver();
        quit = Winner();

        EventQueue();

    }
}

bool DL_Game::GameOver()
{
    if ( quit == false )
    {
        if ( Player1->getPlayerHealth() < 1 )
        {
            Player1->setPlayerHealth( 0 );
            Menu1->pause();

            Menu1->RenderText( mainRenderer, Player1->getPlayerHealth());

            SDL_RenderClear( mainRenderer );

            Menu1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 5 );

            SDL_RenderPresent( mainRenderer );
            SDL_Delay( 3000 );
            return true;
        }
        else return false;
    }
    else return true;

}

bool DL_Game::Winner()
{
    if ( quit == false )
    {
        if ( (Player1->getPlayerPosX() + Player1->getPlayerWidth()) == ( (SCREEN_W - Map1->getMAP_W())/2 + Map1->getMAP_W() -1))
        {
            SDL_RenderClear( mainRenderer );

            Menu1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 4 );

            SDL_RenderPresent( mainRenderer );
            SDL_Delay( 3000 );

            return true;
        }
        else return false;
    }
    else return true;


}

void DL_Game::RenderScene()
{
    /// clearing the renderer
    SDL_RenderClear( mainRenderer );

    /// rendering the map
    Map1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H );

    ///rendering the cannons
    Cannon1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H );

    Menu1->RenderText( mainRenderer, Player1->getPlayerHealth());

    Menu1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 1 );

    Projectile1->MoveNRender( mainRenderer, SCREEN_W, SCREEN_H );

    /// rendering the player
    Player1->AnimatePlayer( mainRenderer, SCREEN_W, SCREEN_H, keyState );

    /// rendering all to the screen
    SDL_RenderPresent( mainRenderer );
}

void DL_Game::EventQueue()
{
    /// event loop
    while ( SDL_PollEvent(&e) != 0 )
        {
        /// quit check
            if ( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE )
            {
                quit = true;
                break;
            }

            if ( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE )
            {
                Menu1->pause();

                SDL_RenderClear( mainRenderer );

                Menu1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 2 );

                SDL_RenderPresent( mainRenderer );

                Player1->setPlayerSpeedX( 0 );
                Player1->setPlayerSpeedY( 0 );
                keyState[0] = 0; keyState[1] = 0; keyState [2] = 0; keyState[3] = 0;

                while (1)
                {
                    if ( SDL_PollEvent( &e ) != 0 )
                    {
                        if ( e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_SPACE )
                            break;
                    }

                }


                Menu1->unpause();
            }

            //Projectile1->Collision( Player1, Map1->getMAP_W(), Map1->getMAP_H(), SCREEN_W, SCREEN_H );
            /// player's movement handler
            Player1->HandleInput( e, keyState );
        }
}

bool DL_Game::Start()
{
    while ( 1 )
        {
            SDL_RenderClear( mainRenderer );

            /// filling the renderer with white color
            SDL_SetRenderDrawColor( mainRenderer, 0x00,0x00,0x00,0xFF );

            Menu1->RenderTexture( mainRenderer, SCREEN_W, SCREEN_H, 3 );

            SDL_RenderPresent( mainRenderer );
            while ( SDL_PollEvent( &e ) != 0 )
                   {
                       /// quit check
                        if ( e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE )
                        {
                            return false;

                        }
                        else if ( e.type == SDL_KEYDOWN )
                        {
                            Menu1->start();
                            return true;

                        }
                   }

        }
}

void DL_Game::CollisionDetector ()
{
    Projectile1->Collision( Player1, Map1->getMAP_W(), Map1->getMAP_H(), SCREEN_W, SCREEN_H );
}

void DL_Game::FireNRun ( Uint32 *CurrentTick, Uint32 *StartTick )
{
    /// getting the actual ticks
    (*CurrentTick) = SDL_GetTicks();


    /// checking the amount of passed time; used for animation only; firing projectiles;
    if ( ((*CurrentTick) - (*StartTick)) > ( 500 ) )
    {
        Projectile1->CreateProjectile( Cannon1->getCannonsAmount(),Cannon1->getCannonInfo(), Player1->getPlayerPosX(), Player1->getPlayerPosY() );

        (*StartTick) = (*CurrentTick);

        /// set the animation flag, or reset
        if ( keyState[5] == false ) keyState[5] = true;
        else keyState[5] = false;
    }

    Player1->MovePlayer( SCREEN_W, SCREEN_H, Map1 );
}

void DL_Game::Run()
{
    if ( !InitializeSDL() )
    {
        cout<<"Failed to initialize.\n";
    }
    else
    {
        if ( !Allocate() )
        {
            cout<<"Failed to allocate memory.\n";
        }
        else
        {
            if ( !Load() )
            {
                cout<< "Failed to load media.\n";
            }
            else
            {
                Set();

                if ( Start() )
                    MainLoop();
            }
        }


        //CloseSDL();

    }
}

bool DL_Game::Load()
{
    bool s = true;

    if ( !Map1->LoadMap( "maps/map1.txt", 15, 20 ) ) s = false;
    if ( !Menu1->LoadFont("fonts/Georgia_Bold.ttf", mainRenderer )) s = false;

    DL_Texture *Pointer = Map1;

    if ( !Pointer->LoadTexture( "images/swamp.png", mainRenderer ) )
    {
        s = false;
    } else
        if ( !Pointer->CreateTiles( 4 ) ) s = false;

    Pointer = Player1;

    if ( !Pointer->LoadTexture( "images/ichigo2.png", mainRenderer ) )
    {
        s = false;
    }
    else
        if ( !Pointer->CreateTiles( 10 ) ) s = false;

    Pointer = Cannon1;

    if ( !Pointer->LoadTexture( "images/cannons.png", mainRenderer ) )
    {
        s = false;
    }
    else
        if ( !Pointer->CreateTiles( 4 ) ) s = false;

    Pointer = Projectile1;

    if ( !Pointer->LoadTexture( "images/projectiles.png", mainRenderer ) )
    {
        s = false;
    }
    else
        if ( !Pointer->CreateTiles( 4 ) ) s = false;

    Pointer = Menu1;

    if ( !Pointer->LoadTexture( "images/menu.png", mainRenderer ))
    {
        s = false;
    }
    else
        if ( !Pointer->CreateTiles( 6 ) ) s = false;

    return s;
}

void DL_Game::Set()
{
    /// setting the starting position according to the map scheme
    Player1->setPlayerPosY( Map1->getMapStartingPosition( SCREEN_H, Player1->getPlayerHeight() ) );
    Player1->setPlayerPosX( (SCREEN_W - Map1->getMAP_W())/2 );

    Cannon1->setMap( Map1->getMap() );
    Cannon1->setMapColumns( Map1->getMapColumns() );
    Cannon1->setMapRows( Map1->getMapRows() );
    Cannon1->setCannonsInfo( SCREEN_W, SCREEN_H );

    Menu1->setHPos( (SCREEN_W - Map1->getMAP_W())/2, (SCREEN_H - Map1->getMAP_H())/2 );
    Menu1->setTPos( ((SCREEN_W - Map1->getMAP_W())/2)+Map1->getMAP_W(), (SCREEN_H - Map1->getMAP_H())/2 );
    Menu1->setSCenter( SCREEN_W/2, SCREEN_H /2);


}

