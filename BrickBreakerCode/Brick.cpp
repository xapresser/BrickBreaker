#include "Brick.h"
#include "ResourceManager.h"
#include "LogManager.h"
#include "WorldManager.h"
#include "EventOut.h"
#include "EventCollision.h"
#include "EventView.h"
#include "EventTurn.h"

#include<stdlib.h>

Brick::Brick()
{
	// to setup brick sprite. It also by default sets object's bounding box used for collision to the size of sprite and centers the object loaction
	setSprite("brick");

	//to set the object type
	setType("Brick");

	// to register for interest in the turn event
	registerInterest(EventTurn);
}

Brick::~Brick()
{
	// add 10 points when destroyed
	df::EventView ev(POINTS_STRING, 10, true);
	WM.onEvent(&ev);

}
int Brick::eventHandler(const df::Event* p_e)
{

	if (p_e->getType() == df::OUT_EVENT)
	{
		out();
		return 1;
	}

	if (p_e->getType() == df::COLLISION_EVENT)
	{
		const df::EventCollision* p_collision_event = dynamic_cast <df::EventCollision const*> (p_e);
		hit(p_collision_event);
		return 1;
	}
	// to check for the turn event in the event handler
	if (p_e->getType() == TURN_EVENT)
	{


	}

	return 0;
}

// to check if the ball hit the brick
void Brick::hit(const df::EventCollision* p_collision_event)
{

	// If brick on brick, ignore.
	if ((p_collision_event->getObject1()->getType() == "Brick") &&
		(p_collision_event->getObject2()->getType() == "Brick"))
		return;

	// If Bullet, create explosion and make new brick.
	if ((p_collision_event->getObject1()->getType() == "Bullet") ||
		(p_collision_event->getObject2()->getType() == "Bullet"))
	{

		// Create an explosion.
		Explosion* p_explosion = new Explosion;
		p_explosion->setPosition(this->getPosition());

		// Saucers appear stay around perpetually.
		new Brick;
	}
}
// used to move the brick to starting location 
void Brick::moveToStart()
{
	df::Vector temp_pos;

	float world_horiz = WM.getBoundary().getHorizontal();
	float world_vert = WM.getBoundary().getVertical();

	// x is off right side of window
	temp_pos.setX(world_horiz + rand() % (int)world_horiz + 3.0f);

	// y is in vertical range
	temp_pos.setY(rand() % (int)(world_vert - 4) + 4.0f);

	// to tell the WorldManager to move brick to starting position
	WM.moveObject(this, temp_pos);

	// If collision, move right slightly until empty space.
	df::ObjectList collision_list = WM.getCollisions(this, temp_pos);
	while (!collision_list.isEmpty())
	{
		temp_pos.setX(temp_pos.getX() + 1);
		collision_list = WM.getCollisions(this, temp_pos);
	}
}