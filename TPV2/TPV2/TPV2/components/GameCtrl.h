#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/ecs.h"
#include "..//sdlutils/SDLUtils.h"

#include "../components/State.h"

class GameCtrl : public Component {
public:
	GameCtrl() : state_(nullptr), astMngr_(nullptr) {

	}

	virtual ~GameCtrl() {
	}


	void init() override {
		state_ = entity_->getComponent<State>();
		astMngr_ = entity_->getComponent<AsteroidManager>();
	
	}

	void update() {
		if (ih().keyDownEvent()) {
			//Si el jugador presiona la tecla espacio y no está jugando, cambia de estado 
			if (ih().isKeyDown(SDL_SCANCODE_SPACE) && state_->getStates() != RUNNING){
				state_->setStates(RUNNING);
				//Se instancian 10 asteroides posicionados aleatoriamente en los bordes de la pantalla
				astMngr_->startGame();
			}
		}
	}

private:
	State* state_;
	AsteroidManager* astMngr_;
};