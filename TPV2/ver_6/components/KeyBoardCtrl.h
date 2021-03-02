// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class KeyBoardCtrl: public Component {
public:
	KeyBoardCtrl() :
			KeyBoardCtrl(SDL_SCANCODE_UP, SDL_SCANCODE_DOWN, SDL_SCANCODE_LEFT,
					10.0f) //
	{
	}
	KeyBoardCtrl(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop,
			float speed) :
			up_(up), //
			down_(down), //
			stop_(stop), //
			speed_(speed), //
			tr_(nullptr) //
	{
	}
	virtual ~KeyBoardCtrl() {
	}

	inline void setKeys(SDL_Scancode up, SDL_Scancode down, SDL_Scancode stop) {
		up_ = up;
		down_ = down;
		stop_ = stop;
	}

	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			auto &vel = tr_->getVel();
			if (ih().isKeyDown(up_)) {
				vel.setY(-speed_);
			} else if (ih().isKeyDown(down_)) {
				vel.setY(speed_);
			} else if (ih().isKeyDown(stop_)) {
				vel.setY(0.0f);
			}
		}
	}

private:
	SDL_Scancode up_;
	SDL_Scancode down_;
	SDL_Scancode stop_;
	float speed_;
	Transform *tr_;
}
;

