// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include <memory>
#include "../ecs/Entity.h"

// when you are not using the methods of a class, just
// say that it exists, that saves time when parsing files
class Manager;

class Game {
public:
	Game();
	virtual ~Game();
	void init();
	void start();

	Entity* createManagerNPlayer();
private:
	std::unique_ptr<Manager> mngr_;
};

