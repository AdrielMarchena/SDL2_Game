#include "Keyboard.h"

namespace Engine
{
	Keyboard::Keyboard() {
		//Init the arrays with false values
		//Zero is for non supported keys
		const unsigned short qtdKeys = 8;
		pressedKeys.reserve(qtdKeys); pressedKeys.assign(qtdKeys, false);
		clickedKeys.reserve(qtdKeys); clickedKeys.assign(qtdKeys, false);
		clickedFunction.reserve(qtdKeys); clickedFunction.assign(qtdKeys, []()
		{
		});
	}
	Keyboard::~Keyboard() {}

	void Keyboard::handleInputs() {
		int key = events.key.keysym.sym;
		switch (events.type) {

			case SDL_KEYDOWN:
				pressedKeys[keyAssociated(key)] = true;

				if (clickedFunction[keyAssociated(key)] && !clickedKeys[keyAssociated(key)]) {
					clickedKeys[keyAssociated(key)] = true;
					clickedFunction[keyAssociated(key)]();
				}
			break;

			case SDL_KEYUP:
				pressedKeys[keyAssociated(key)] = false;
				clickedKeys[keyAssociated(key)] = false;
			break;
		}
	}

	bool Keyboard::isPress(const ky& k)
	{
		return clickedKeys[k];
	}

	void Keyboard::clicked(const ky& k, const std::function<void()>& func)
	{
		clickedFunction[k] = func;
	}

	inline int Keyboard::keyAssociated(int key)
	{
		switch (key) {
		case SDLK_RIGHT:
			return (int)ARROW_RIGHT;
			break;
		case SDLK_LEFT:
			return (int)ARROW_LEFT;
			break;
		case SDLK_UP:
			return (int)ARROW_UP;
			break;
		case SDLK_DOWN:
			return (int)ARROW_DOWN;
			break;
		case SDLK_SPACE:
			return (int)SPACEBAR;
			break;
		case SDLK_KP_PLUS:
			return (int)PLUS_KEY;
			break;
		case SDLK_KP_MINUS:
			return (int)MINUS_KEY;
			break;
		default:
			return 0;
			break;

		}
	}
}