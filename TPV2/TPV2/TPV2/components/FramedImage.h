// This file is part of the course TPV2@UCM - Samir Genaim
#pragma once

#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"
#include "..//ecs/Entity.h" //Por que aquí me pide añadirlo y en image no

#include "Transform.h"

class FramedImage : public Component {
public:
	FramedImage(Texture* tex, int fil, int col) :
		tr_(nullptr), //
		tex_(tex) //

	{
		fils = fil;
		cols = col;
		posx = posy = 0;
		xFrame = tex_->width() / cols;
		yFrame = tex_->height() / fils;
	}
	virtual ~FramedImage() {

	}

	//Override sobreescribre
	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);
		//src = build_sdlrect(tr_->getPos(), tex_->width() / cols, tex_->height() / fils);
		src = { xFrame * posx, yFrame * posy, xFrame , yFrame };
	}

	void render() override {
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(src, dest, tr_->getRot());
	}


	void update() {

		if (tiempo < timer)tiempo++;
		else {
			tiempo = 0;
			posx++;

			if (posx > cols - 1) {
				posx = 0;
				posy++;

				if (posy > fils - 1) {
					posy = 0;
					posx = 0;
				}
			}
			src = { xFrame * posx, yFrame * posy, xFrame , yFrame };
		}

	}

private:
	Transform* tr_;
	Texture* tex_;

	int fils, cols;
	int posx, posy; //Posicion en la text
	int xFrame, yFrame;

	SDL_Rect src;


	const int timer = 5;
	int tiempo = 0;
};