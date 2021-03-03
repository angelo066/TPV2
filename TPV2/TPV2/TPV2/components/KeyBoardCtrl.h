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
	KeyBoardCtrl(const float value = 0.5f) :
			tr_(nullptr), speed_(10.0),thurst(value), maxSpeed(3) {
	}
	virtual ~KeyBoardCtrl() {
	}


	inline void setSpeed(float speed) {
		speed_ = speed;
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto &vel = tr_->getVel();
		if (ih().keyDownEvent()) {
			
			if (ih().isKeyDown(SDL_SCANCODE_UP)) {
				Vector2D newVel = vel + Vector2D(0, -1).rotate(tr_->getRot()) * thurst;

				if (vel.magnitude() >= maxSpeed)vel = newVel.normalize() * maxSpeed;
				else vel = newVel;
			}
		}
	}

private:
	Transform *tr_;
	float speed_, thurst;
	float maxSpeed;
}
;

