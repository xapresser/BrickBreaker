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

void startUp();

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

    RM.loadSprite("sprites/ship-spr.txt", "ship");
    RM.loadSprite("sprites/bullet-spr.txt", "ball");

    startUp();

    // Shut everything down.
    GM.shutDown();
    return 0;
}

void startUp() {
    //df::Vector corner(0, 0);
    //df::Box world_boundary(corner, 20, 30);
    //WM.setBoundary(world_boundary);
    //df::Box view(corner, 20, 30);
    //WM.setView(view);

    new Shooter;
    GM.run();
    //LM.writeLog("hewwo");
    Sleep(1000);
}