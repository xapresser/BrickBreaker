//temporary code

#include "Brick.h"
#include "EventTurn.h"
#include "WorldManager.h"
#include <stdlib.h>
#include "DisplayManager.h"
#include "LogManager.h"

int Brick::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
        hit(p_collision_event);
        return(1);
    }
    if (p_e->getType() == TURN_EVENT)
        //do movedown stuff for all bricks and create new row at top
        return(1);
    return(0);
}

void Brick::moveDown() {
    //
}

void Brick::hit(const df::EventCollision* p_c) {
    if ((p_c->getObject1()->getType() == "Bullet") || (p_c->getObject2()->getType() == "Bullet")) {
        hitpoints--;
    }
    if (hitpoints == 0) {
        new Brick;
        WM.markForDelete(this);
    }
}

Brick::Brick() {
    setType("Brick");
    setSprite("brick");
    registerInterest(TURN_EVENT);
    hitpoints = 1;
    df::Vector v((rand()%(int)5)*10, 10);
    //df::Vector v(25, 25);
    //df::Vector e(10, 10);
    setPosition(v);
    //LM.writeLog("drawch success %d", DM.drawCh(e, '1', df::GREEN));
}