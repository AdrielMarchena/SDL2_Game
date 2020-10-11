#pragma once

#include "SDL.h"
#include <vector>
#include <functional>

namespace Engine
{
#define COLISOR_ALL_TO_ALL_MODE 1
#define COLISOR_FIRST_TO_ALL_MODE 2
#define COLISOR_FIRST_TO_ALL_MODE_A 3


		enum class TypeColision {
			GROUND,
			WALL,
			WALLGROUND,
			PLAYER,
			DEFAULT
		};

		class InterfaceToColide {
		public:
			TypeColision type = TypeColision::DEFAULT;
			virtual SDL_Rect& boxInfo() = 0;
			virtual void colided(InterfaceToColide* cause) = 0;
		};

		class Colisor
		{
		public:
			int firstMember = 0;
			std::vector<InterfaceToColide*> objToColide;


			Colisor();
			~Colisor();


			void processColisions();
			void pushNewItem(InterfaceToColide* obj);
			void setMethodToColide(std::function<bool(const SDL_Rect&, const SDL_Rect&)>);
			void setModeToColide(const unsigned int& mode);
			void setFirstMember(InterfaceToColide* obj);
		private:
			unsigned int mode = 0;

			inline bool testColision(InterfaceToColide* subject, InterfaceToColide* other);
			inline bool testColisionA(InterfaceToColide* subject, InterfaceToColide* other);
			std::function<bool(const SDL_Rect&, const SDL_Rect&)> methodToColide;
			inline void processFirtToAll();
			inline void processAllToAll();
			inline void processFirstToAll_A();

		};
}