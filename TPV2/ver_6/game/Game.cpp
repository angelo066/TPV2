// This file is part of the course TPV2@UCM - Samir Genaim

#include "Game.h"

#include "../components/AICtrl.h"
#include "../components/BallPhysics.h"
#include "../components/GameLogic.h"
#include "../components/Image.h"
#include "../components/KeyBoardCtrl.h"
#include "../components/MouseCtrl.h"
#include "../components/PaddlePhysics.h"
#include "../components/Rectangle.h"
#include "../components/State.h"
#include "../components/Transform.h"
#include "../ecs/ecs.h"
#include "../ecs/Entity.h"
#include "../sdlutils/InputHandler.h"
#include "../sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"
#include "../utils/Vector2D.h"

Game::Game() {
	mngr_.reset(new Manager());
}

Game::~Game() {
}

void Game::init() {

	SDLUtils::init("Ping Pong", 800, 600,
			"resources/config/pingpong.resources.json");

	auto *ball = mngr_->addEntity();
	ball->addComponent<Transform>(
			Vector2D(sdlutils().width() / 2.0f, sdlutils().height() / 2.0f),
			Vector2D(), 10.0f, 10.0f, 0.0f);
	//ball->addComponent<Rectangle>(build_sdlcolor(0x112233ff));
	ball->addComponent<Image>(&sdlutils().images().at("tennis_ball"));
	ball->addComponent<BallPhysics>();
	mngr_->setHandler<Ball>(ball);

	auto *leftPaddle = mngr_->addEntity();
	leftPaddle->addComponent<Transform>(
			Vector2D(10.0, sdlutils().height() / 2.0f - 25.0f), Vector2D(),
			10.0f,
			50.0f, 0.0f);
	leftPaddle->addComponent<Rectangle>(build_sdlcolor(0x4466aaff));
	//leftPaddle->addComponent<AICtrl>();
	leftPaddle->addComponent<MouseCtrl>();
	leftPaddle->addComponent<PaddlePhysics>();

	mngr_->setHandler<LeftPaddle>(leftPaddle);

	auto *rightPaddle = mngr_->addEntity();
	rightPaddle->addComponent<Transform>(
			Vector2D(sdlutils().width() - 10.0f - 10.0f,
					sdlutils().height() / 2.0f - 25.0f), Vector2D(), 10.0f,
			50.0f,
			0.0f);
	rightPaddle->addComponent<Rectangle>(build_sdlcolor(0xaa0011ff));
	rightPaddle->addComponent<KeyBoardCtrl>();
	//rightPaddle->addComponent<AICtrl>();
	rightPaddle->addComponent<PaddlePhysics>();
	mngr_->setHandler<RightPaddle>(rightPaddle);

	auto *gameMngr = mngr_->addEntity();
	gameMngr->addComponent<State>();
	gameMngr->addComponent<GameLogic>();
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

