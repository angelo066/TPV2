#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include"../sdlutils/SDLUtils.h"

class Follow : public Component {
public:
	Follow(Vector2D* playerP) :
		tr_(nullptr), playerPos(playerP){
	}
	virtual ~Follow() {
	}


	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr); 
		auto& vel = tr_->getVel();
		vel.set(Vector2D(1, 1));				//Inicializamos la velocidad porque si no es 0
	}

	void update() override {
		auto& vel = tr_->getVel();
		Vector2D p = tr_->getPos();

		//Fórmula del pdf         Este question mark significa que si la variable se cumple se aplica lo de la izquierda y si no lo de la derecha
		vel.set(vel.rotate(vel.angle(*playerPos - p) > 0 ? 1.0f : -1.0f));
	}

private:
	Transform* tr_;
	Vector2D* playerPos;
}
;