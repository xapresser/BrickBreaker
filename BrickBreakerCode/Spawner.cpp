#include "Spawner.h"
#include "Brick.h"
#include "EventTurn.h"
#include "LogManager.h"

//necessary bcz if clear board wont be able to make new row

void Spawner::start() {
    newRow();
    //fillBoard();
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

void Spawner::fillBoard() {
    LM.writeLog("filling");
    for (int i = 4;i <= 58;i += 9) {
        for (int j = 1;j <= 45;j += 5) {
            //LM.writeLog("x: %d, y: %d", i, j);
            df::Vector v;
            v.setX(i);
            v.setY(j);
            //LM.writeLog("spawner x: %f, y: %f", v.getX(), v.getY());
            new Brick(v);
        }
    }
    /*df::Vector v;
    v.setX(4);
    v.setY(1);
    new Brick(v);*/
}

Spawner::Spawner() {
    registerInterest(TURN_EVENT);
    turn = 1;
}