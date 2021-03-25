// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Transform.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"


#include "Health.h"
#include "State.h"
#include "../sdlutils/SDLUtils.h"

#include "../utils/Collisions.h"


class CollisionManager : public Component {
public:
	CollisionManager(){

	}

	virtual ~CollisionManager() {

	}

	void init() override {
		mngr_ = entity_->getComponent<Manager>();
		entities_ = mngr_->getEnteties();
		player = mngr_->getHandler<Player>();
		playerT_ = player->getComponent<Transform>();
		health_ = player->getComponent<Health>();


		state_ = entity_->getComponent<State>();
	}

	void render() override {

	}

	void update() override {
		for (Entity* e : entities_){
			if (e->hasGroup<Asteroid_grp>())
			{
				Transform* t = e->getComponent<Transform>();
				for (Entity* e : entities_){
					if (e->hasGroup<Bullet_grp>()){

					}
				}

				if (Collisions::collidesWithRotation(t->getPos(), t->getW(), t->getH(),t->getRot() ,
									playerT_->getPos(), playerT_->getW(), playerT_->getH(), playerT_->getRot()))
				{
					if (health_->getLives() > 0){
						state_->setStates(PAUSED);
						health_->loseLife();

						playerT_->getPos().set(sdlutils().width()/2, sdlutils().height() / 2);
						playerT_->setRot(0);
						playerT_->getVel().set(0.0f, 0.0f);
					}
					else{
						state_->setStates(GAMEOVER);
						player->setActive(false);
					}

					for (Entity* enti : entities_) {
						if (enti->hasGroup<Asteroid_grp>() || enti->hasGroup<Bullet_grp>()) enti->setActive(false);
					}
				}
			}
		}
	}

	void asteroidCollides(Entity* e)
	{

	}

private:
	std::vector<Entity*> entities_;
	Manager* mngr_;

	Entity* player;
	Health* health_;
	State* state_;
	Transform* playerT_;
};