#include "Shooter.h"
#include "EventTurn.h"
#include "WorldManager.h"
#include "EventView.h"
#include "Bullet.h"
#include "Windows.h"
#include "LogManager.h"
#include "EventStep.h"
#include "ResourceManager.h"

void Shooter::mouse(const df::EventMouse* p_mouse_event) {
	if ((p_mouse_event->getMouseAction() == df::CLICKED) && (p_mouse_event->getMouseButton() == df::Mouse::LEFT)) {
		isFiring = true;
		aim = p_mouse_event->getMousePosition();
		//Change this so has limited angle range and can’t affect depth range
	}
}

void Shooter::fire() {
	if (isFiring) {
		fire_countdown--;
		if (fire_countdown <= 0) {
			if (shotBullets < bullets) {
				df::Vector v = aim - getPosition();
				v.normalize();
				v.scale(1);
				Bullet* p = new Bullet(getPosition());
				p->setVelocity(v);
				shotBullets++;

				// Play fire sound
				df::Sound* p_sound = RM.getSound("fire");
				if (p_sound)
					p_sound->play();
			}
			else {
				isFiring = false;
			}
			fire_countdown = fire_cooldown;
		}
	}

}

void Shooter::nextTurn() {
	bullets++;
	shotBullets = 0;
}

int Shooter::eventHandler(const df::Event* p_e) {
	if (p_e->getType() == df::MSE_EVENT) {
		const df::EventMouse* p_mouse_event = dynamic_cast <const df::EventMouse*> (p_e);
		mouse(p_mouse_event);
		return 1;
	}
	if (p_e->getType() == df::STEP_EVENT) {
		fire();
		return(1);
	}
	if (p_e->getType() == TURN_EVENT) {
		nextTurn();
		return(1);
	}
	return(0);
}

Shooter::Shooter() {
	registerInterest(df::MSE_EVENT);
	setSolidness(df::SOFT);
	setType("Shooter");
	//temp sprite
	setSprite("ship");
	registerInterest(df::STEP_EVENT);
	registerInterest(TURN_EVENT);
	bullets = 1;
	shotBullets = 0;
	fire_cooldown = 5;
	fire_countdown = fire_cooldown;
	isFiring = false;
	df::Vector p(WM.getBoundary().getHorizontal() / 2, 50);
	setPosition(p);
	p_reticle = new Reticle();
	p_reticle->draw();
	LM.writeLog("shooter spawned in");
}