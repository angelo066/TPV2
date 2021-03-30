#pragma once
#include <cassert>

#include "..//components/DisableOnExit.h"
#include "../ecs/Component.h"
#include"../sdlutils/SDLUtils.h"
#include "../ecs/Manager.h"


class Health : public Component {
public:
	Health(Vector2D pos = Vector2D(0, 0), Vector2D size = Vector2D(50, 50), const int h = 3, Texture* tex_ = &sdlutils().images().at("heart")) :
		pos_(pos), size_(size), lives(h), initLives(lives), tex(tex_), mngr(nullptr) {
	}

	virtual ~Health() {
	}

	void init() override {
		iniPos_ = pos_;
		mngr = entity_->getMngr();
	}

	void update() override {
	}

	void render() override {
		for (int i = 0; i < lives; i++) {
			SDL_Rect dest = build_sdlrect(pos_, size_.getX(), size_.getX());
			tex->render(dest, 0.0f);
			pos_.setX(pos_.getX() + size_.getX());
		}
		pos_ = iniPos_;
	}

	/// <summary>
	/// Disminuye en cierta cantidad las vidas del jugador
	/// </summary>
	/// <param name="cant"> cantidad a reducir. Por defecto es una unidad</param>
	void loseLife(int cant = 1){
		if (lives > 0) lives-= cant;
	}

	/// <summary>
	/// Restaura las vidas iniciales al jugador
	/// </summary>
	void restoreLife(){
		lives = initLives;
	}

	/// <summary>
	/// Devuelve las vidas restantes del jugador
	/// </summary>
	/// <returns></returns>
	int getLives(){
		return lives;
	}

private:
	Vector2D pos_, iniPos_, size_;
	Texture* tex;
	Manager* mngr;
	int lives, initLives;
};