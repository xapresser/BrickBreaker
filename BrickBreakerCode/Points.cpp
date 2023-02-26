#include "Points.h"
#include "EventTurn.h"

int Points::eventHandler(const df::Event* p_e) {
	// Parent handles event if score update.
	if (df::ViewObject::eventHandler(p_e)) {
		return 1;
	}
	// If step, increment score every second (30 steps).
	if (p_e->getType() == TURN_EVENT) {
		setValue(getValue() + 1);
		return 1;
	}
	// If get here, have ignored this event.
	return 0;
}

Points::Points() {
	setLocation(df::TOP_RIGHT);
	setViewString(POINTS_STRING);
	setColor(df::YELLOW);
	registerInterest(TURN_EVENT);
}