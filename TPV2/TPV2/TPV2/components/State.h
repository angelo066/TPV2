#pragma once
#include <SDL.h>
#include <cassert>

#include "../ecs/Component.h"
#include "../sdlutils/InputHandler.h"
#include "../ecs/Entity.h"
#include "..//sdlutils/SDLUtils.h"

enum States {NEWGAME, PAUSED, RUNNING, GAMEOVER};

class State : public Component {
public:
	State() :
		s(NEWGAME), win(false) {
	}

	virtual ~State() {
	}


	void init() override {
	}

	
	void render() override {
		// message when game is not running
		
		//Si no está corriendo escribimos mensaje
		if (s != RUNNING) {

			// game over message
			if (s == GAMEOVER) {
				//Mensaje si pierde
				if (!win) {
					auto& t = sdlutils().msgs().at("gameover");
					t.render((sdlutils().width() - t.width()) / 2,
						(sdlutils().height() - t.height()) / 2 - 100);
				}//Mensaje si gana
				else {
					auto& t = sdlutils().msgs().at("win");
					t.render((sdlutils().width() - t.width()) / 2,
						(sdlutils().height() - t.height()) / 2 - 100);
				}
			}

			// new game message
			if (s == NEWGAME) {
				auto& t = sdlutils().msgs().at("start");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2 );
			}
			else {
				auto& t = sdlutils().msgs().at("continue");
				t.render((sdlutils().width() - t.width()) / 2,
					sdlutils().height() / 2);
			}
		}

	}
	//Devuelve el estado del juego
	States getStates()
	{
		return s;
	}
	//Cambia el estado del juego
	void setStates(States stat)
	{
		s = stat;
	}
	//Determina si el jugador ha ganado
	void setWin() { win = true; }

	//Devuelve si el jugador ha ganado
	bool getWin() { return win; }

private:
	States s;

	bool win;
}
;