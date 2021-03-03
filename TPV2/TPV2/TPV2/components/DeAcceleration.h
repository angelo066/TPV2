#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

class DeAcceleration : public Component {
public:
	DeAcceleration() :
		tr_(nullptr) {
	}
	virtual ~DeAcceleration() {
	}
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		
		auto& vel = tr_->getVel();

		vel.set(vel.getX() * 0.95f, vel.getY() * 0.95f);
	}

private:
	Transform* tr_;
};