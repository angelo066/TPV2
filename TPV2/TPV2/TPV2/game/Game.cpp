// This file is part of the course TPV2@UCM - Samir Genaim
#include "Game.h"

#include "../components/ShowAtOpposieSide.h"
#include "../components/AsteroidManager.h"
#include "../components/DeAcceleration.h"
#include "../components/CollideBounds.h"
#include "../components/FighterCtrl.h"
#include "../components/FrameImage.h"
#include "../components/Transform.h"
#include "../components/GameCtrl.h"
#include "../components/Health.h"
#include "../components/Rotate.h"
#include "../components/Follow.h"
#include "../components/State.h"
#include "../components/Image.h"
#include "../components/Gun.h"

#include "../ecs/Manager.h"
#include "../ecs/Entity.h"
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

	SDLUtils::init("How mad are the Asteroids?", 800, 600,
		"resources/config/asteroids.resources.json");

	createGameManager();

	createPlayer();

	createManager();
}

void Game::start() {

	// a boolean to exit the loop
	bool exit = false;
	SDL_Event event;

	while (!exit) {
		Uint32 startTime = sdlutils().currRealTime();

		ih().clearState();
		while (SDL_PollEvent(&event))
			ih().update(event);

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

void Game::createPlayer(){
	auto* caza = mngr_->addEntity();
	//Pos															//vel		//width, height, rotation
	caza->addComponent<Transform>(Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f), Vector2D(), 50.0f, 50.0f, 0.0f);
	caza->addComponent<Image>(&sdlutils().images().at("fighter"));
	caza->addComponent<FighterCtrl>(10.0f, 0.4);
	caza->addComponent<DeAcceleration>(0.95f);
	caza->addComponent<Rotate>();
	caza->addComponent<Gun>(2000);
	caza->addComponent<ShowAtOpposieSide>(Vector2D(sdlutils().width(), sdlutils().height()));
	caza->addComponent<Health>();

	mngr_->setHandler<Player>(caza);
}

void Game::createManager(){
	auto* gM = mngr_->addEntity();
	gM->addComponent<AsteroidManager>();
	gM->addComponent<State>();
}

void Game::createGameManager(){

	auto* gM = mngr_->addEntity();

	gM->addComponent<AsteroidManager>();
	gM->addComponent<State>();
	gM->addComponent<GameCtrl>();
}

