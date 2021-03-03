// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"

class FighterCtrl: public Component {
public:
	FighterCtrl(const float spd = 10.0f, const float thr = 0.2f) :
			tr_(nullptr), speed_(spd), thrust_(thr), speedLimit_(3.0f){
	}
	virtual ~FighterCtrl() {
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
				vel = vel + Vector2D(0, -1).rotate(tr_->getRot()) * thrust_;
			}
		}

		if (vel.magnitude() >= speedLimit_)
		{
			vel = vel.normalize()* speedLimit_;
		}
	}

private:
	Transform *tr_;
	float speed_, thrust_, speedLimit_;
}
;

