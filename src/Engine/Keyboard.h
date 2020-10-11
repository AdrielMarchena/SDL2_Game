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
		std::vector<bool> pressedKeys;
		std::vector<bool> clickedKeys;

	private:
		std::vector<std::function<void()>> clickedFunction;
	public:
		Keyboard();
		~Keyboard();

		enum ky {
			ARROW_RIGHT = 1,
			ARROW_LEFT,
			ARROW_UP,
			ARROW_DOWN,
			SPACEBAR,
			PLUS_KEY,
			MINUS_KEY
		};

		void handleInputs();
		bool isPress(const ky& k);
		void clicked(const ky& k, const std::function<void()>& func);
	private:
		inline int keyAssociated(int key);
	};
}