#include "Shooter.h"
#include "EventTurn.h"
#include "WorldManager.h"
#include "EventView.h"
#include "Bullet.h"
#include "Windows.h"
#include "LogManager.h"

void Shooter::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		fire(p_mouse_event->getMousePosition());
		//Change this so has limited angle range and can’t affect depth range
	}
}

void Shooter::fire(df::Vector target) {
	if (!isFiring) {
		isFiring = true;
		for (int i = bullets; i > 0; i--) {
			df::Vector v = target - getPosition();
			v.normalize();
			v.scale(1);
			Bullet* p = new Bullet(getPosition());
			p->setVelocity(v);
			Sleep(fire_cooldown);
		}
		nextTurn();
		isFiring = false;
	}
	//LM.writeLog("%d", getPosition());
}

void Shooter::nextTurn() {
	EventTurn turn;
	WM.onEvent(&turn);
	df::EventView ev("Turn", -1, true);
	WM.onEvent(&ev);
}

int Shooter::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	return(0);
}

Shooter::Shooter() {
	registerInterest(df::MSE_EVENT);
	setType("Shooter");
	//temp sprite
	setSprite("ship");
	bullets = 1;
	fire_cooldown = 100;
	isFiring = false;
	df::Vector p(WM.getBoundary().getHorizontal() / 2, 50);
	setPosition(p);
	p_reticle = new Reticle();
	p_reticle->draw();
	LM.writeLog("shooter spawned in");
}