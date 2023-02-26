#include "Spawner.h"
#include "Brick.h"
#include "EventTurn.h"

//necessary bcz if clear board wont be able to make new row

void Spawner::start() {
    newRow();
}

int Spawner::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == TURN_EVENT) {
        //create new row at top
        turn++;
        newRow();
        return(1);
    }
    return(0);
}

void Spawner::newRow() {
    new Brick(turn);
    new Brick(turn);
    new Brick(turn);
    new Brick(turn);
    new Brick(turn);
    new Brick(turn);
}

Spawner::Spawner() {
    registerInterest(TURN_EVENT);
    turn = 1;
}