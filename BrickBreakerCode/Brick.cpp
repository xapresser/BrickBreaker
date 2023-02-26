#include "Brick.h"
#include "EventTurn.h"
#include "WorldManager.h"
#include <stdlib.h>
#include "DisplayManager.h"
#include "LogManager.h"

int Brick::eventHandler(const df::Event* p_e) {
    //if collision event, sends event to hit method to be handled
    if (p_e->getType() == df::COLLISION_EVENT) {
        const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
        hit(p_collision_event);
        return(1);
    }
    if (p_e->getType() == TURN_EVENT) {
        //do movedown stuff for all bricks and create new row at top
        moveDown();
        return(1);
    }
    return(0);
}

void Brick::moveDown() {
    df::Vector v = getPosition();
    v.setY(v.getY() + 4);
    WM.moveObject(this, v);
    WM.moveObject(hp, v);
    //newRow();
    if (v.getY() > 45) {
       //end game you die call gameover class here later once have that set up
    }
}

void Brick::newRow() {
    new Brick;
    new Brick;
    new Brick;
    new Brick;
    new Brick;
    new Brick;
}

void Brick::moveToStart() {
    //7 slots in a row where a brick can generate
    //at x position 4, 12, 20, 28, 36, 44, or 52
    //bricks always start at y position 1
    df::Vector v(((rand() % (int)7) * 8) + 4, 1);
    WM.moveObject(this, v);

    //checks for overlap with other bricks
    df::ObjectList collision_list = WM.getCollisions(this, v);
    if (!collision_list.isEmpty())
        WM.markForDelete(this);

    //moves the hitpoints number
    WM.moveObject(hp, v);
}

void Brick::hit(const df::EventCollision* p_c) {
    //takes 1 damage per bullet hit by
    if ((p_c->getObject1()->getType() == "Bullet") || (p_c->getObject2()->getType() == "Bullet")) {
        hp->setValue(hp->getValue() - 1);
    }

    //when hitpoints are 0, brick is destroyed
    if (hp->getValue() == 0) {
        WM.markForDelete(this);
    }
}

Brick::~Brick() {
    //marks the hitpoints viewobject for delete
    WM.markForDelete(hp);
}

Brick::Brick() {
    setType("Brick");
    setSprite("brick");
    registerInterest(TURN_EVENT);
    hp = new Hitpoints(1);
    moveToStart();
}

Brick::Brick(df::Vector v) {
    setType("Brick");
    setSprite("brick");
    registerInterest(TURN_EVENT);
    hp = new Hitpoints(1);
    setPosition(v);
    hp->setPosition(v);
}

Brick::Brick(int health) {
    setType("Brick");
    setSprite("brick");
    registerInterest(TURN_EVENT);
    hp = new Hitpoints(health);
    moveToStart();
}