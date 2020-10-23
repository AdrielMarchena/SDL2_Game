#pragma once
#include "Math.h"
namespace Engine
{
	struct WindowSize
	{
		WindowSize(float W, float H)
			:W(W), H(H)
		{}
		WindowSize()
			:W(600.0f), H(600.0f)
		{}
		float W, H;
	};

	struct GlobalConf
	{
		WindowSize windowSize;
		Math::Vec2f gravity;
		bool fScreen = false;

		GlobalConf()
			:gravity({0.0f, 9.8f})
		{}
	};
}
