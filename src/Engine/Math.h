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

			//Override +
			Vec2f operator+(const Vec2f& b)
			{
				Vec2f a;
				a.x = this->x + b.x;
				a.y = this->y + b.y;
				return a;
			}
			//Override -
			Vec2f operator-(const Vec2f& b)
			{
				Vec2f a;
				a.x = this->x - b.x;
				a.y = this->y - b.y;
				return a;
			}
			//Override *
			Vec2f operator*(const Vec2f& b)
			{
				Vec2f a;
				a.x = this->x * b.x;
				a.y = this->y * b.y;
				return a;
			}
			//Override /
			Vec2f operator/(const Vec2f& b)
			{
				Vec2f a;
				a.x = this->x / b.x;
				a.y = this->y / b.y;
				return a;
			}
			//Override +=
			Vec2f& operator+=(const Vec2f& b)
			{
				this->x += b.x;
				this->y += b.y;
				return *this;
			}
			//Override -=
			Vec2f& operator-=(const Vec2f& b)
			{
				this->x -= b.x;
				this->y -= b.y;
				return *this;
			}
			//Override *=
			Vec2f& operator*=(const Vec2f& b)
			{
				this->x *= b.x;
				this->y *= b.y;
				return *this;
			}
			//Override /=
			Vec2f& operator/=(const Vec2f& b)
			{
				this->x /= b.x;
				this->y /= b.y;
				return *this;
			}
			//Override == Identical
			bool operator==(const Vec2f& b)
			{
				if (this->x == b.x && this->y == b.y)
					return true;
				return false;
			}
			//Override != Identical
			bool operator!=(const Vec2f& b)
			{
				if (this->x != b.x || this->y != b.y)
					return true;
				return false;
			}
		};
	}
}