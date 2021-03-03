// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DeAcceleration : public Component {
public:
	DeAcceleration(const float value = 0.995f) :
		tr_(nullptr), deaccelerate(value) {
	}
	virtual ~DeAcceleration() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		auto& vel = tr_->getVel();

		vel.set(vel.getX() * deaccelerate, vel.getY() * deaccelerate);
	}

private:
	Transform* tr_;
	float deaccelerate;
};

