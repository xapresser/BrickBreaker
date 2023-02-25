#include "Bullet.h"
#include "LogManager.h"

void Bullet::hit(const df::EventCollision* p_c) {
	if ((p_c->getObject1()->getType() == "Brick") || (p_c->getObject2()->getType() == "Brick")) {
		bounce();
	}
}

void Bullet::bounce() {
	df::Vector v = getDirection();
	v.scale(-1);
	setDirection(v);
}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		bounce();
		return(1);
	}
	if (p_e->getType() == df::COLLISION_EVENT) {
		const df::EventCollision* p_collision_event = dynamic_cast <const df::EventCollision*> (p_e);
		hit(p_collision_event);
		return(1);
	}
	return(0);
}

Bullet::Bullet(df::Vector shooter_pos) {
	//setSprite("bullet");
	setType("Bullet");
	//setSolidness(df::SOFT);
	df::Vector p(shooter_pos.getX(), shooter_pos.getY() + 3);
	setPosition(p);
	setSpeed(1);
	LM.writeLog("bullet");
}