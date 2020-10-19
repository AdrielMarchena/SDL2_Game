#pragma once
#include <iostream>

namespace Engine
{
	namespace Math
	{
		struct Vec2f
		{
			Vec2f(float x, float y)
				:x(x), y(y)
			{}
			Vec2f()
				:x(0.0f),y(0.0f)
			{}

			void print()
			{ 
				std::cout << x << ", " << y << std::endl;
			}

			float x, y;
		};
	}
}