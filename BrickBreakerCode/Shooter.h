#include "Object.h"
#include "EventMouse.h"
#include "Reticle.h"

class Shooter : public df::Object {
private:
	Reticle* p_reticle;
	bool isFiring;
	int bullets;
	int shotBullets;
	int fire_cooldown;
	int fire_countdown;
	df::Vector aim;
	void mouse(const df::EventMouse* p_mouse_event);
	void fire();
	void nextTurn();
public:
	Shooter();
	int eventHandler(const df::Event* p_e) override;
};