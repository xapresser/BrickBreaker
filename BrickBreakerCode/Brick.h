#include "Object.h"
#include "EventCollision.h"

class Brick : public df::Object {
private:
	int hitpoints;
	void moveDown();
public:
	Brick(int start_col);
	int eventHandler(const df::Event* p_e) override;
	void hit(const df::EventCollision* p_c);
	//~Brick();
};