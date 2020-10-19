#pragma once

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
		const float gravity = 1.6f;
		bool fScreen = false;
	};
}
