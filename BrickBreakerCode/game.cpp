//
// game.cpp
// 

// Engine includes.
#include "GameManager.h"
#include "LogManager.h"
#include "Shooter.h"
#include "Vector.h"
#include "WorldManager.h"
#include "Windows.h"
#include "ResourceManager.h"
#include "Brick.h"
#include "DisplayManager.h"
#include "Points.h"
#include "Spawner.h"
#include "GameStart.h"
#include "Pause.h"

//void startUp();
// Function prototypes.
//void loadResources(void);
//void populateWorld(void);


void loadResources(void)
{
    RM.loadSprite("sprites/ship-spr.txt", "ship");
    RM.loadSprite("sprites/bullet-spr.txt", "ball");
    RM.loadSprite("sprites/brick-spr.txt", "brick");

    //to load the game start sprites
    RM.loadSprite("sprites/gamestart-spr.txt", "gamestart");
    RM.loadSprite("sprites/gameover-spr.txt", "gameover");
}

void populateWorld(void) {
    // to load music for the game
    RM.loadMusic("sounds/start-music.wav", "start music");
    // Create GameStart object.
    new GameStart();
}

int main(int argc, char* argv[]) {
    // Start up game manager.
    if (GM.startUp()) {
        LM.writeLog("Error starting game manager!");
        GM.shutDown();
        return 1;
    }

    // Set flush of logfile during development (when done, make false).
    LM.setFlush(true);

    // Show splash screen.
    df::splash();

    // Load game resources.
    loadResources();

    // Populate game world with some objects.
    populateWorld();
    //new df::Pause(df::Keyboard::F10);
    // Run game (this blocks until game loop is over).
    GM.run();
   
    //startUp();

    // Shut everything down.
    GM.shutDown();
    return 0;
}


void startUp() 
{
    new Shooter;
    new Points;
    Spawner* s = new Spawner();
    s->start();
    GM.run();
}