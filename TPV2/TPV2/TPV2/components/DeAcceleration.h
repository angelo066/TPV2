#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DeAcceleration : public Component {
public:
	DeAcceleration(const float deacc = 0.95f) :
		tr_(nullptr), deacceleration_(deacc) {
	}
	virtual ~DeAcceleration() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		
		auto& vel = tr_->getVel();

		vel.set(vel.getX() * deacceleration_, vel.getY() * deacceleration_);
	}

private:
	Transform* tr_;
	float deacceleration_;
};