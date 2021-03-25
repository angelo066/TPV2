#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "..//sdlutils/SDLUtils.h"

enum States {NEWGAME, PAUSED, RUNNING, GAMEOVER};

class State : public Component {
public:
	State() :
		s(NEWGAME) {
	}

	virtual ~State() {
	}


	void init() override {

	}

	void render() override {
		// message when game is not running
		

		if (s != RUNNING) {
			//auto gm = static_cast<GameManager*>(c);
			//auto& state = gm->getState();

			// game over message
			if (s == GAMEOVER) {
				auto& t = sdlutils().msgs().at("gameover");
				t.render((sdlutils().width() - t.width()) / 2,
					(sdlutils().height() - t.height()) / 2);
			}

			// new game message
			if (s == NEWGAME) {
				auto& t = sdlutils().msgs().at("start");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 );
			}
			else {
				auto& t = sdlutils().msgs().at("continue");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2);
			}
		}

	}

	States getStates()
	{
		return s;
	}
	
	void setStates(States stat)
	{
		s = stat;
	}

private:
	States s;
}
;