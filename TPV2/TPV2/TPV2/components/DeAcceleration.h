#pragma once
// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

#include "Transform.h"

class DeAcceleration : public Component {
public:
	DeAcceleration(Texture* tex) :
		tr_(nullptr), //
		tex_(tex) //
	{
	}
	virtual ~DeAcceleration() {
	}

	void init() override {
		
	}

	void render() override {
		
	}

private:
	
};