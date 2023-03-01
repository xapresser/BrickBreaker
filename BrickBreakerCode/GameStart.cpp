#include "GameStart.h"
#include "GameOver.h"
#include "LogManager.h"
#include "EventStep.h"
#include "WorldManager.h"
#include "ResourceManager.h"
#include "GameManager.h"
#include "Shooter.h"
#include "Brick.h"
#include "Points.h"
#include "Spawner.h"



GameStart::GameStart() {
    setType("GameStart");

    // Link to "message" sprite.
    setSprite("gamestart");

    // Put in center of window.
    setLocation(df::CENTER_CENTER);

    //to register for the keyboard event
    registerInterest(df::KEYBOARD_EVENT);

    // Play start music.
    p_music = RM.getMusic("start music");
    playMusic();
}

// Play start music.
void GameStart::playMusic()
{
    p_music->play();
}


int GameStart::eventHandler(const df::Event* p_e) {
    if (p_e->getType() == df::KEYBOARD_EVENT) {
        df::EventKeyboard* p_keyboard_event = (df::EventKeyboard*)p_e;
        switch (p_keyboard_event->getKey()) {
        case df::Keyboard::P: 			// play
            start();
            break;
        case df::Keyboard::Q:			// quit
            GM.setGameOver();
            break;
        default:
            break;
        }
        return 1;
    }

    // If get here, have ignored this event.
    return 0;
}

void GameStart::start() {
    new Shooter;
    new Spawner;
    new Points;

    // Pause start music.
    p_music->pause();

    // When game starts, become inactive.
    setActive(false);
}

// Override default draw so as not to display "value".
int GameStart::draw() {
    return df::Object::draw();
}