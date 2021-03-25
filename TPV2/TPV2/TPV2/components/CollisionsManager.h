// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Transform.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"

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


	}

	void render() override {

	}

	void update() override {
		for (Entity* e : entities_){
			//if(e->hasGroup<Asteroid_grp>())
			/*if (Collisions::collidesWithRotation()){

			}*/
		}
	}

private:
	std::vector<Entity*> entities_;
	Manager* mngr_;

	Entity* player;
};