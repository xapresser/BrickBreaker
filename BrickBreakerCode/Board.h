#include "Object.h"

class Board : public df::Object {
public:
	Board();
	void newRow();
private:
	int hitpoints;
};