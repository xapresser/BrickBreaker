#include "Object.h"

class Spawner : public df::Object {
private:
	int turn;
public:
	Spawner();
	void start();
	int eventHandler(const df::Event* p_e) override;
	void newRow();
	void fillBoard();
};