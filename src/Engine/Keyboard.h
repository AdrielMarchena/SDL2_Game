#pragma once
#include "SDL_events.h"
#include "vector"
#include <functional>
#include <iostream>

namespace Engine
{
	class Keyboard {
	public:
		SDL_Event events;
		

	private:
		std::vector<std::function<void()>> clickedFunction;
		std::vector<bool> pressedKeys;
		std::vector<bool> clickedKeys;
	public:
		Keyboard();
		~Keyboard();

		enum ky {
			INVALID,
			ARROW_RIGHT,
			ARROW_LEFT,
			ARROW_UP,
			ARROW_DOWN,
			SPACEBAR,
			PLUS_KEY,
			MINUS_KEY,
			ESC_KEY,
			F11_KEY
		};

		void handleInputs();
		bool isPress(const ky& k);
		void clicked(const ky& k, const std::function<void()>& func);
	private:
		inline int keyAssociated(int key);
	};
}