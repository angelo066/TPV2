#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "..//sdlutils/SDLUtils.h"

class Gun : public Component {
public:
	Gun() :
		tr_(nullptr) {
	}
	virtual ~Gun() {
	}

	inline void setSpeed(float speed) {
		
	}


	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (ih().keyDownEvent()) {
			//auto& vel = tr_->getVel();
			if (ih().isKeyDown(SDLK_s)) {
				sdlutils().soundEffects().at("fire").play();
				
			}
		}
	}

private:
	Transform* tr_;
}
;