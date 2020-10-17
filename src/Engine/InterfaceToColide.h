#pragma once

namespace Engine
{
	enum class SideColided
	{
		INVALID = -1,
		BOTTOM,
		LEFT,
		RIGHT,
		TOP
	};

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
}