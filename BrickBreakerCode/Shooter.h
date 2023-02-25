#include "Object.h"
#include "EventMouse.h"
#include "Reticle.h"

class Shooter : public df::Object {
private:
	Reticle* p_reticle;
	bool isFiring;
	int bullets;
	int fire_cooldown;
	void mouse(const df::EventMouse* p_mouse_event);
	void fire(df::Vector target);
	void nextTurn();
public:
	Shooter();
	int eventHandler(const df::Event* p_e) override;
};