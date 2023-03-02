#include "Bullet.h"
#include "LogManager.h"
#include "DisplayManager.h"
#include "WorldManager.h"
#include "EventTurn.h"
#include "EventView.h"
#include "ResourceManager.h"

void Bullet::hit(const df::EventCollision* p_c) {
	//if object colliding with is brick (bounces for when colliding with edge of screen are handled by OUT_EVENT in eventhandler
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

		//if collision is diff y than bullet, means hitting smthing above or below so should change y direction of velocity
		//LM.writeLog("collision x: %d, c y: %d",(int)p_c->getPosition().getX(), (int)p_c->getPosition().getY());
		//LM.writeLog("pos x: %d, pos y: %d", (int)getPosition().getX(), (int)getPosition().getY());
		
		/*LM.writeLog("collision x: %f, c y: %f", p_c->getPosition().getX(), p_c->getPosition().getY());
		LM.writeLog("pos x: %f, pos y: %f", getPosition().getX(), getPosition().getY());
		LM.writeLog("direction x: %f, y: %f", getDirection().getX(), getDirection().getY());
		if ((p_c->getPosition().getY()) != getPosition().getY()) {
			df::Vector v = getDirection();
			float y = v.getY();
			v.setY(abs(p_c->getPosition().getY() - getPosition().getY()) * -1 * y);
			setDirection(v);
			LM.writeLog("vertical: %f", abs(p_c->getPosition().getY() - getPosition().getY()));
		}

		//if collision is diff x than bullet, means hitting smthing left or right so should change x direction of velocity
		if ((p_c->getPosition().getX()) != getPosition().getX()) {
			df::Vector v = getDirection();
			float x = v.getX();
			v.setX(abs(p_c->getPosition().getX() - getPosition().getX()) * -1 * x);
			setDirection(v);
			LM.writeLog("horizontal: %f", abs(p_c->getPosition().getX() - getPosition().getX()));
		}*/
		LM.writeLog("hit");
		if ((int)(p_c->getPosition().getX()) != (int)getPosition().getX()) {
			LM.writeLog("horizontal");
			horizontalBounce();
		}
		if ((int)(p_c->getPosition().getY()) != (int)getPosition().getY()) {
			LM.writeLog("vertical");
			verticalBounce();
		}

	}
}

void Bullet::horizontalBounce() {
	df::Vector v = getDirection();
	float x = v.getX();
	v.setX(x * -1);
	setDirection(v);

	// Play fire sound
	df::Sound* p_sound = RM.getSound("bounce");
	if (p_sound)
		p_sound->play();
}

void Bullet::verticalBounce() {
	df::Vector v = getDirection();
	float y = v.getY();
	v.setY(y * -1);
	setDirection(v);

	// Play fire sound
	df::Sound* p_sound = RM.getSound("bounce");
	if (p_sound)
		p_sound->play();

}

int Bullet::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::OUT_EVENT) {
		df::Vector v = getPosition();
		//LM.writeLog("out");
		//if hitting left or right side of screen
		if (v.getX() > DM.getHorizontal() || v.getX() < 0)
			horizontalBounce();

		//if hitting top of screen
		if (v.getY() < 0)
			verticalBounce();

		//if hitting bottom of screen
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

//destructor
Bullet::~Bullet() {
	//if this is only bullet in world
	if (WM.objectsOfType("Bullet").getCount()==1) {
		//turn ends, sends out eventturn
		EventTurn turn;
		WM.onEvent(&turn);
		//df::EventView ev("Turn", -1, true);
		//WM.onEvent(&ev);
	}
}

Bullet::Bullet(df::Vector shooter_pos) 
{
	setSprite("ball");
	setType("Bullet");
	setSolidness(df::SOFT);
	df::Vector p(shooter_pos.getX(), shooter_pos.getY());
	setPosition(p);
	setSpeed(2);
	//LM.writeLog("bullet");
}