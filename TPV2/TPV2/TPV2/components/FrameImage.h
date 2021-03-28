// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "Transform.h"
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "../sdlutils/SDLUtils.h"

class FrameImage : public Component {
public:
	FrameImage(Texture* tex, int rows, int cols, int r, int c, const float frameRate = 50.0f) :
		tr_(nullptr), //
		tex_(tex), //
		timer(frameRate) 
	{
		//ancho de cada sprite, //alto de cada sprite
		sizeXF = tex_->width() / cols;
		sizeYF = tex_->height() / rows;

		//Rectangulo base
		src_ = { sizeXF * c, sizeYF * r, sizeXF, sizeYF };

		posX = c;
		posX = r;
		iniPos = Vector2D(posX, posY);
		wholeSize = Vector2D(cols, rows);
	}

	virtual ~FrameImage() {
	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		lastTime = sdlutils().currRealTime() - timer; //la resta es para que deje disparar al principio del juego
		assert(tr_ != nullptr);
	}

	void render() override
	{
		SDL_Rect dest = build_sdlrect(tr_->getPos(), tr_->getW(), tr_->getH());
		tex_->render(src_, dest, tr_->getRot());
	}

	void update() override{
		if (sdlutils().currRealTime() - lastTime > timer){
			//Actualizamos los frames de la textura a renderizar, pasados uno un rateFrame 
			lastTime = sdlutils().currRealTime();
			if (posX != wholeSize.getX() - 1) ++posX;
			else{
				if (posY != wholeSize.getY() - 1 ){
					++posY;
					posX = iniPos.getX();
				}
				else{
					posX = iniPos.getX();
					posY = iniPos.getY();
				}
			}
			src_ = { sizeXF * posX,sizeYF * posY, sizeXF, sizeYF };
		}
	}

private:
	Transform* tr_;
	Texture* tex_;
	Vector2D wholeSize, iniPos;
	SDL_Rect src_;

	float timer, lastTime;
	int sizeXF, sizeYF, posX, posY;
};
