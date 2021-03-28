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
	//Devolvemos las generaciones que quedan
	inline int getLeftGenerations() { return generations_; }
	//Restamos una a generación
	void substractGenerations() { --generations_; }

private:
	int generations_;
};