#include "Brick.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventView.h"

#include<stdlib.h>

Brick::Brick()
{
	setSprite("brick");
	setType("Brick");
	setVelocity(df::Vector(0, -0.25));
	registerInterest(EventTurn);
}

Brick::~Brick()
{
	// add 10 points when destroyed
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);

}