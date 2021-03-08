#pragma once
#include <SDL.h>
#include <cassert>

#include "..//components/DisableOnExit.h"
#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "..//sdlutils/SDLUtils.h"

#include "../ecs/Manager.h"


class Gun : public Component {
public:
	Gun(const float& t = 0.25f) :
		tr_(nullptr), h(), w(), r(), lastTime(), timer(t){
	}

	virtual ~Gun() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		lastTime = sdlutils().currRealTime() - timer; //la resta es para que deje disparar al principio del juego
		mngr = entity_->getMngr();
		assert(tr_ != nullptr);
	}

	void update() override {

		//Disparo
		if (ih().keyDownEvent()) {
			if (ih().isKeyDown(SDLK_s)) {
				if (sdlutils().currRealTime() - lastTime  > timer)
				{
					lastTime = sdlutils().currRealTime();

					w = tr_->getW();
					h = tr_->getH();
					r = tr_->getRot();
					auto* bala = mngr->addEntity();

					Vector2D bPos = tr_->getPos() + Vector2D(w / 2.0f, h / 2.0f) - Vector2D(0.0f, h / 2.0f + 5.0f + 12.0f).rotate(r) - Vector2D(2.0f, 10.0f);
					Vector2D bVel = Vector2D(0.0f, -1.0f).rotate(r) * (tr_->getVel().magnitude() + 5.0f);
					bala->addComponent<Transform>(bPos, bVel, 5.0f, 20.0f, r);
					bala->addComponent<Image>(&sdlutils().images().at("bullet"));
					bala->addComponent<DisableOnExit>();
					sdlutils().soundEffects().at("fire").play();

					bala->setGroup<Bullet_grp>(true);
				}
			}
		}
	}

private:
	Transform* tr_;
	Manager* mngr;
	float w, h, r, timer, lastTime;

}
;