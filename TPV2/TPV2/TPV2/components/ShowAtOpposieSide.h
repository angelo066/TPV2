#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "..//sdlutils/SDLUtils.h"

class ShowAtOpposieSide : public Component {
public:
	ShowAtOpposieSide() :
		tr_(nullptr) {
	}
	virtual ~ShowAtOpposieSide() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		if (tr_->getPos().getX() > sdlutils().width()) {
			tr_->getPos().setX(0 - tr_->getW());		//Le restamos su anchura porque si no aparece automáticamente en pantalla	
		}
		else if (tr_->getPos().getX() < 0 - tr_->getW()) {	//Le restamos su anchura porque si no se trigerea en cuanto toca el borde
			tr_->getPos().setX(sdlutils().width());
		}
		else if(tr_->getPos().getY() < 0 - tr_->getH()){//Le restamos su altura porque si no aparece automáticamente en pantalla	
			tr_->getPos().setY(sdlutils().height());
		}
		else if (tr_->getPos().getY() > sdlutils().height() + tr_->getH()) {//Le sumamos su altura sporque si no se trigerea en cuanto toca el borde
			tr_->getPos().setY(0 - tr_->getH());
		}
	}

private:
	Transform* tr_;
}
;