// This file is part of the course TPV2@UCM - Samir Genaim
#include "Game.h"

//Incluimos todos los componentes en el GameCtrl, ya que es el controlador principal del juego.
#include "../components/GameCtrl.h"

#include "../ecs/Manager.h"

#include "../ecs/ecs.h"

#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {
	SDLUtils::init("How mad are the Asteroids?", 800, 600, "resources/config/asteroids.resources.json");

	auto* gM = createManagerNPlayer();
}

void Game::start() {
	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();

		while (SDL_PollEvent(&event)) ih().update(event);

		if (ih().isKeyDown(SDL_SCANCODE_ESCAPE)) {
			exit = true;
			continue;
		}

		mngr_->update();
		mngr_->refresh();

		sdlutils().clearRenderer();
		mngr_->render();
		sdlutils().presentRenderer();

		Uint32 frameTime = sdlutils().currRealTime() - startTime;

		if (frameTime < 20)
			SDL_Delay(20 - frameTime);
	}

}

Entity* Game::createManagerNPlayer(){
	auto* gM = mngr_->addEntity();
	gM->addComponent<State>();
	gM->addComponent<AsteroidManager>();
	gM->addComponent<GameCtrl>()->createPlayer();
	gM->addComponent<CollisionsManager>();

	return gM;
}


