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
    RM.loadSprite("sprites/brick-spr.txt", "brick");

    startUp();

    // Shut everything down.
    GM.shutDown();
    return 0;
}

void startUp() {
    new Shooter;
    new Points;
    Spawner* s = new Spawner();
    s->start();
    GM.run();
}