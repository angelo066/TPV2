#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include"../sdlutils/SDLUtils.h"

class Generations : public Component {
public:
	Generations(const int generations = 3): generations_(generations){
	}

	virtual ~Generations() {
	}


	void init() override {

	}

	void update() override {

	}

	inline int getLeftGenerations() { return generations_; }

	void substractGenerations() { --generations_; }

private:
	int generations_;
};