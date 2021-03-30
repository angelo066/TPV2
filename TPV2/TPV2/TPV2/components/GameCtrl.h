#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/ecs.h"
#include "..//sdlutils/SDLUtils.h"

#include "../components/ShowAtOpposieSide.h"
#include "../components/CollisionsManager.h"
#include "../components/AsteroidManager.h"
#include "../components/DeAcceleration.h"
#include "../components/CollideBounds.h"
#include "../components/FighterCtrl.h"
#include "../components/FrameImage.h"
#include "../components/Transform.h"
#include "../components/Health.h"
#include "../components/Rotate.h"
#include "../components/Follow.h"
#include "../components/State.h"
#include "../components/State.h"
#include "../components/Image.h"
#include "../components/Gun.h"

class GameCtrl : public Component {
public:
	GameCtrl() : state_(nullptr), astMngr_(nullptr) {}

	virtual ~GameCtrl() {
	}

	void init() override {
		state_ = entity_->getComponent<State>();
		astMngr_ = entity_->getComponent<AsteroidManager>();
	}

	void update() override {
		if (ih().keyDownEvent()) {
			//Si el jugador presiona la tecla espacio y no está jugando, cambia de estado 
			if (ih().isKeyDown(SDL_SCANCODE_SPACE) && state_->getStates() != RUNNING){
				if (state_->getStates() == GAMEOVER && !state_->getWin()) {
					//volvemos a crear el player ya que ha sido desactivado al perder
					createPlayer();					
					//Actualizamos los parametros que usa el CollisionManager
					entity_->getComponent<CollisionsManager>()->ActPlayer();
					state_->setStates(NEWGAME);
				}
				else {
					state_->setStates(RUNNING);
					//Se instancian 10 asteroides posicionados aleatoriamente en los bordes de la pantalla
					astMngr_->startGame();
				}			
			}
		}
	}

	/// <summary>
	/// Inicializamos al Jugador con los parámetros adecuados
	/// </summary>
	void createPlayer(){
		auto* mngr_ = entity_->getMngr();
		auto* caza = mngr_->addEntity();
		float size = 50.0f;
		//Pos															//vel		//width, height, rotation
		caza->addComponent<Transform>(Vector2D((float)sdlutils().width() / 2.0f - size / 2.0f, (float)sdlutils().height() / 2.0f - size / 2.0f), Vector2D(), size, size, 0.0f);
		caza->addComponent<Image>(&sdlutils().images().at("fighter"));
		caza->addComponent<FighterCtrl>(10.0f, 0.4);
		caza->addComponent<DeAcceleration>(0.95f);
		caza->addComponent<Rotate>();
		caza->addComponent<Gun>();
		caza->addComponent<ShowAtOpposieSide>(Vector2D((float)sdlutils().width(), (float)sdlutils().height()));
		caza->addComponent<Health>();
		//Asignamos el Handler al Manager
		mngr_->setHandler<Player>(caza);
	}

private:
	State* state_;
	AsteroidManager* astMngr_;
};