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
	ShowAtOpposieSide(Vector2D winProps) :
		tr_(nullptr), windowProps(winProps) {
	}
	virtual ~ShowAtOpposieSide() {
	}



	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
	}

	void update() override {
		Vector2D pos = tr_->getPos();

		//Guardamos las posición
		float x = pos.getX();
		float y = pos.getY();

		//Guardamos las propiedades de la ventana
		float windowW = windowProps.getX();
		float windowH = windowProps.getY();

		//Guardamos la altura y anchura del jugador
		float w = tr_->getW();
		float h = tr_->getH();

		if (x > windowW) {
			tr_->getPos().setX(0 - w);		//Le restamos su anchura porque si no aparece automáticamente en pantalla	
		}
		else if (x < 0 - w) {	//Le restamos su anchura porque si no se trigerea en cuanto toca el borde
			tr_->getPos().setX(windowW);
		}
		else if(y < 0 - h){//Le restamos su altura porque si no aparece automáticamente en pantalla	
			tr_->getPos().setY(windowH);
		}
		else if (y > windowH + h) {//Le sumamos su altura sporque si no se trigerea en cuanto toca el borde
			tr_->getPos().setY(0 - h);
		}
	}

private:
	Transform* tr_;
	Vector2D windowProps;
}
;