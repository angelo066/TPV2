// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../ecs/Manager.h"


#include "Transform.h"
#include "Health.h"
#include "State.h"
#include "AsteroidManager.h"
#include "../sdlutils/SDLUtils.h"

#include "../utils/Collisions.h"


class CollisionsManager : public Component {
public:
	CollisionsManager(): playerT_(nullptr), player(nullptr), astMngr_(nullptr), health_(nullptr), mngr_(nullptr),
						 state_(nullptr){};

	virtual ~CollisionsManager() {

	}

	void init() override {
		mngr_ = entity_->getMngr();
		ActPlayer();
		astMngr_ = entity_->getComponent<AsteroidManager>();

		state_ = entity_->getComponent<State>();
	}

	void ActPlayer() {
		player = mngr_->getHandler<Player>();
		assert(player != nullptr);
		playerT_ = player->getComponent<Transform>();
		assert(playerT_ != nullptr);
		health_ = player->getComponent<Health>();
		assert(health_ != nullptr);
	}

	void update() override {
		entities_ = mngr_->getEnteties();
		for (Entity* e : entities_){
			if (e->hasGroup<Asteroid_grp>()){
				Transform* t = e->getComponent<Transform>();
				for (Entity* bala : entities_){
					if (bala->hasGroup<Bullet_grp>()){
						Transform* balaT = bala->getComponent<Transform>();
						if(checkCollision(t, balaT)){
							e->setActive(false);
							bala->setActive(false);
							astMngr_->onCollision(e);
						}
					}
				}

				if (checkCollision(t, playerT_)){
					health_->loseLife();
					sdlutils().soundEffects().at("explosion").play();
					if (health_->getLives() > 0){
						state_->setStates(PAUSED);
						playerT_->getPos().set(sdlutils().width()/2 - playerT_->getW()/2.0f, sdlutils().height() / 2 - playerT_->getH() / 2.0f);
						playerT_->setRot(0);
						playerT_->getVel().set(0.0f, 0.0f);
					}
					else{
						state_->setStates(GAMEOVER);
						player->getComponent<Health>()->restoreLife();
						player->setActive(false);
					}
					for (Entity* enti : entities_)
						if (enti->hasGroup<Asteroid_grp>() || enti->hasGroup<Bullet_grp>()) enti->setActive(false);
				}
			}
		}
		entities_ = mngr_->getEnteties();
	}
	/// <summary>
	/// 
	/// </summary>
	/// <param name="t"></param>
	/// <param name="other"></param>
	/// <returns></returns>
	bool checkCollision(Transform* t, Transform* other){
		return (Collisions::collidesWithRotation(t->getPos(), t->getW(), t->getH(), t->getRot(),
			other->getPos(), other->getW(), other->getH(), other->getRot()));
	}
	
private:
	std::vector<Entity*> entities_;
	Manager* mngr_;
	Entity* player;
	Health* health_;
	State* state_;
	AsteroidManager* astMngr_;
	Transform* playerT_;
};