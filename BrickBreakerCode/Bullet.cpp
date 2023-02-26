#include "Bullet.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventTurn.h"
#include "EventView.h"

void Bullet::hit(const df::EventCollision* p_c) {
	if ((p_c->getObject1()->getType() == "Brick") || (p_c->getObject2()->getType() == "Brick")) {
		//code so that when all bricks are destroyed it'll automatically destroy all bullets so dont have to sit through animation of them bouncing down
		//currently doesn't work
		/*df::ObjectList bricks = WM.objectsOfType("Brick");
		if (bricks.getCount() == 1) {
			LM.writeLog("list is empty");
			df::ObjectList bullets = WM.objectsOfType("Bullet");
			df::ObjectListIterator li(&bullets);
			while (!li.isDone()) {
				WM.markForDelete(li.currentObject());
				li.next();
			}
		}*/
		if (p_c->getPosition().getY() != getDirection().getY()) {
			verticalBounce();
		}
		if (p_c->getPosition().getX() != getDirection().getX()) {
			horizontalBounce();
		}
	}
}

void Bullet::horizontalBounce() {
	df::Vector v = getDirection();
	float x = v.getX();
	v.setX(x * -1);
	setDirection(v);
}

void Bullet::verticalBounce() {
	df::Vector v = getDirection();
	float y = v.getY();
	v.setY(y * -1);
	setDirection(v);
}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		df::Vector v = getPosition();
		if (v.getX() > DM.getHorizontal() || v.getX() < 0)
			horizontalBounce();
		if (v.getY() < 0)
			verticalBounce();
		else if (v.getY() > DM.getVertical())
			WM.markForDelete(this);
		return(1);
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return(1);
	}
	return(0);
}

Bullet::~Bullet() {
	LM.writeLog("destroying a bullet");
	if (WM.objectsOfType("Bullet").getCount()==1) {
		EventTurn turn;
		WM.onEvent(&turn);
		df::EventView ev("Turn", -1, true);
		WM.onEvent(&ev);
	}
}

Bullet::Bullet(df::Vector shooter_pos) {
	setSprite("ball");
	setType("Bullet");
	setSolidness(df::SOFT);
	df::Vector p(shooter_pos.getX(), shooter_pos.getY());
	setPosition(p);
	setSpeed(1);
	LM.writeLog("bullet");
}