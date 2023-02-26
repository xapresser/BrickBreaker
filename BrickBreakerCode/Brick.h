#include "Object.h"
#include "EventCollision.h"
#include "Hitpoints.h"

class Brick : public df::Object {
private:
	Hitpoints* hp;
	void moveDown();
	void newRow();
	void moveToStart();
public:
	Brick();
	Brick(df::Vector v);
	int eventHandler(const df::Event* p_e) override;
	void hit(const df::EventCollision* p_c);
	~Brick();
};