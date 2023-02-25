#include "Object.h"
#include "EventCollision.h"
#include "EventOut.h"

class Bullet : public df::Object {
private:
	void hit(const df::EventCollision* p_c);
	void bounce();
public:
	Bullet(df::Vector shooter_pos);
	int eventHandler(const df::Event* p_e) override;
};