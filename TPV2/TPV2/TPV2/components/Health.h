#pragma once
#include <cassert>

#include "..//components/DisableOnExit.h"
#include "../ecs/Component.h"
#include "../ecs/Manager.h"


class Health : public Component {
public:
	Health(Texture* tex) :
		tr_(nullptr), lives(3), t(tex), pos(Vector2D()){
	}

	virtual ~Health() {

	}

	void init() override {
		tr_ = entity_->getComponent<Transform>();
		assert(tr_ != nullptr);

	}

	void render() override {

		for (int i = 0; i < lives; i++) {
			SDL_Rect dest = build_sdlrect(pos, tr_->getW(), tr_->getH());

			t->render(dest, 0);
			pos.setX(pos.getX() + tr_->getW()); //Primero con (0,0) renderizas y luego lo cambias yo que se te me cuidas :)
		}

		pos = Vector2D();
	}

	void lifeLost(int cuantity) { lives = lives - cuantity; }
	void restoreLife() { lives = 3; }
	int getLifes() { return lives; }

private:
	Transform* tr_;
	int lives;

	Texture* t;
	
	Vector2D pos;
}
;