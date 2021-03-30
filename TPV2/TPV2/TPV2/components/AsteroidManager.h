// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once
#include "../ecs/Component.h"
#include "../ecs/Entity.h"
#include "Transform.h"
#include "../sdlutils/SDLUtils.h"

#include "..//components/FrameImage.h"
#include "..//components/Generations.h"
#include "..//components/ShowAtOpposieSide.h"
#include "..//components/Follow.h"
#include "../ecs/Manager.h"
#include "..//components/State.h"

class AsteroidManager : public Component {
public:
	AsteroidManager(const int numAsteroids_ = 10, const int t_ = 5000, const float w = 20.0f, const float h = 20.0f) :
		tr_(nullptr), time(t_), numAsteroids(numAsteroids_), widthAst_(w), heightAst_(h), lastTime(), generations_(), mngr_(nullptr), state(nullptr){
	}

	virtual ~AsteroidManager(){
	}

	void init() override {
		lastTime = sdlutils().currRealTime();
		mngr_ = entity_->getMngr();
		state = entity_->getComponent<State>();
	}

	void update() override{
		if (sdlutils().currRealTime() - lastTime>= time && state->getStates() == RUNNING && generations_ > 0){
			lastTime = sdlutils().currRealTime();
			createAsteroids();
		}
		else if(state->getStates() == RUNNING && generations_ <= 0) {
			state->setWin();
			state->setStates(GAMEOVER);
		}
		
	}

	/// <summary>
	/// Devuelve el número de generaciones de asteroides actuales
	/// </summary>
	/// <returns>int</returns>
	inline int getGenerations() { return generations_; }

	/// <summary>
	/// Divide el asteroide al haber colisionado con una bala
	/// </summary>
	/// <param name="asteroid">Asteroide que ha colisionado</param>
	void onCollision(Entity* asteroid){
		//Desactivas asteroide
		asteroid->setActive(false);
		generations_--;
		//Componente generatios, se le resta y se comprueba si tiene
		Generations* n = asteroid->getComponent<Generations>();
		n->substractGenerations();

		if (n->getLeftGenerations() > 0) {
			for (int i = 0; i < 2; i++)
				divideAsteroid(asteroid->hasComponent<Follow>(), n->getLeftGenerations(), asteroid);
		}
	}

	/// <summary>
	/// Crea un asteroide alrededor de los bordes de la pantalla
	/// </summary>
	/// <param name="nGenerations">Número de generaciones disponibles iniciales</param>
	void createAsteroids(int nGenerations = sdlutils().rand().nextInt(1, 4)){
		generations_++;
		bool isA = (sdlutils().rand().nextInt(0, 10) < 3 ? true : false);
		auto* asteroid = mngr_->addEntity();
		//Random para saber en qu� eje hacer el random de la posicion en los bordes
		int posibility = sdlutils().rand().nextInt(0, 2);
		//Centro de la pantalla
		Vector2D center = Vector2D((float)sdlutils().width() / 2.0f, (float)sdlutils().height() / 2.0f);
		//Posicion central de la pantalla aleatoria
		Vector2D finalPos = Vector2D(center.getX() + sdlutils().rand().nextInt(-100, 100), center.getY() + sdlutils().rand().nextInt(-100, 100));
		Vector2D pos;
		int posRandom;
		//Random en eje X
		if (posibility == 0) {
			posibility = sdlutils().rand().nextInt(0, 2);
			posRandom = sdlutils().rand().nextInt(0, sdlutils().width() + 1);
			pos.setX((float)posRandom);
			if (posibility == 0) pos.setX(0);
			else pos.setX((float)sdlutils().height());
		}
		else { //Random en eje X
			posibility = sdlutils().rand().nextInt(0, 2);
			posRandom = sdlutils().rand().nextInt(0, sdlutils().height() + 1);
			pos.setY((float)posRandom);
			if (posibility == 0) pos.setX(0);
			else pos.setX((float)sdlutils().width());
		}
		//Hacemos que vaya a la position aleatoria del centro
		Vector2D v = Vector2D(finalPos - pos).normalize() * (sdlutils().rand().nextInt(1, 10) / 10.0f);
		asteroid->addComponent<Transform>(pos, v, widthAst_ + 5.0f * nGenerations, heightAst_ + 5 * nGenerations, 0.0f);
		//Diferenciamos entre tipo A o B
		if(isA) asteroid->addComponent<FrameImage>(&sdlutils().images().at("asteroidA"), 5, 6, 0, 0, 50.0f);
		else{
			asteroid->addComponent<FrameImage>(&sdlutils().images().at("asteroidB"), 5, 6, 0, 0, 50.0f);
			//Si es de tipo B, hacemos que siga al jugador
			asteroid->addComponent<Follow>();
		}

		asteroid->addComponent<ShowAtOpposieSide>(Vector2D((float)sdlutils().width(), (float)sdlutils().height()));
		asteroid->addComponent<Generations>(nGenerations);
		//Asignamos su grupo
		asteroid->setGroup<Asteroid_grp>(true);
	}
	/// <summary>
	/// Divide un asteroide si es posible, en dos más pequeños
	/// </summary>
	/// <param name="golden">es de tipo B</param>
	/// <param name="numGenerations">generaciones restantes del padre</param>
	/// <param name="ast">asteroide padre</param>
	void divideAsteroid(bool golden,const int & numGenerations, Entity* ast){
		generations_++;
		Transform* t = ast->getComponent<Transform>();
		Vector2D p = t->getPos();
		Vector2D v = t->getVel();
		float width = t->getW();

		int r = sdlutils().rand().nextInt(0, 360);
		Vector2D astPos = p + v.rotate(r) * 2 * width;
		Vector2D astVel = v.rotate(r) * 1.1f;

		auto* asteroid = mngr_->addEntity();
		asteroid->addComponent<Transform>(astPos, astVel, widthAst_ + 5.0f * numGenerations, heightAst_ + 5 * numGenerations, 0.0f);

		if (!golden) asteroid->addComponent<FrameImage>(&sdlutils().images().at("asteroidA"), 5, 6, 0, 0, 50.0f);
		else asteroid->addComponent<FrameImage>(&sdlutils().images().at("asteroidB"), 5, 6, 0, 0, 50.0f);

		asteroid->addComponent<ShowAtOpposieSide>(Vector2D((float)sdlutils().width(), (float)sdlutils().height()));
		asteroid->addComponent<Generations>(numGenerations);
		//Si es de tipo B, hacemos que siga al jugador
		if (golden) asteroid->addComponent<Follow>();
		//Asignamos su grupo
		asteroid->setGroup<Asteroid_grp>(true);
	}
	/// <summary>
	/// Empieza el juego generando numAsteroids asteroides
	/// </summary>
	void startGame(){
		for (int i = 0; i < numAsteroids; i++) createAsteroids();
	}

private:
	Transform* tr_;
	Manager* mngr_;
	int generations_, time, lastTime, numAsteroids;
	float widthAst_, heightAst_;
	State* state;
};
