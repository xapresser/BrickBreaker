#pragma once
#include "Object.h"
#include "EventCollision.h"

class Brick : public df::Object
{
public:
    Brick();
    ~Brick();
    int eventHandler(const df::Event* p_e) override;

private:

    void out();
    void moveToStart();
    void hit(const df::EventCollision* p_collision_event);
};
