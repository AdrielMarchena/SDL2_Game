#include "Colisor.h"
#include <iostream>
namespace Engine {

	Colisor::Colisor() {}
	Colisor::~Colisor() {}

	void Colisor::processColisions()
	{
		switch (mode) {
		case COLISOR_FIRST_TO_ALL_MODE:
			processFirtToAll();
			break;
		case COLISOR_ALL_TO_ALL_MODE:
			processAllToAll();
			break;
		case COLISOR_FIRST_TO_ALL_MODE_A:
			processFirstToAll_A();
			break;
		default:
			std::cerr << "This colisor mode do not exist: " << mode << std::endl;
			break;
		}
	}

	inline void Colisor::processAllToAll() {
		for (size_t i = 0; i < objToColide.size(); i++) {
			for (size_t j = 0; j < objToColide.size(); j++) {
				if (i == j)
					continue;
				testColision(objToColide[0], objToColide[i]);
			}
		}
	}

	inline void Colisor::processFirtToAll() {
		for (size_t i = 0; i < objToColide.size(); i++) {
			if (i == firstMember)
				continue;
			testColision(objToColide[0], objToColide[i]);
		}
	}
	/*
	Only notificate the first obj
	*/
	inline void Colisor::processFirstToAll_A()
	{
		for (size_t i = 0; i < objToColide.size(); i++) {
			if (i == firstMember)
				continue;
			testColision(objToColide[0], objToColide[i]);
		}
	}

	void Colisor::pushNewItem(InterfaceToColide* obj)
	{
		objToColide.push_back(obj);
	}

	void Colisor::setMethodToColide( std::function<bool(const SDL_Rect&, const SDL_Rect&)> function )
	{
		methodToColide = function;
	}

	void Colisor::setModeToColide(unsigned int mode)
	{
		this->mode = mode;
	}

	SideColided Colisor::calcRecColision(SDL_Rect* a, SDL_Rect* b)
	{
		float dx = ((a->x + a->w) / 2) - ((b->x + b->w) / 2);
		float dy = ((a->y + a->h) / 2) - ((b->y + b->h) / 2);
		float wid = (a->w + b->w) / 2;
		float hei = (a->h + b->h) / 2;
		float crossW = wid * dy;
		float crossH = hei * dx;

		if (abs(dx) <= wid && abs(dy) <= hei)
			if (crossW > crossH) {
				if (crossW > (-crossH))
				{
					//Bottom
					return SideColided::BOTTOM;
				}
				else
				{
					//Left
					return SideColided::LEFT;
				}
			}
			else
			{
				if (crossW > -(crossH))
				{
					//Right
					return SideColided::RIGHT;
				}
				else
				{
					//Top
					return SideColided::TOP;
				}
			}
	}

	inline bool Colisor::testColision(InterfaceToColide* subject, InterfaceToColide* other) {
		SDL_Rect& subBox = subject->boxInfo(), otherBox = other->boxInfo();

		if (methodToColide(subBox, otherBox)) {
			subject->colided(other);
			other->colided(subject);
			return true;
		}
		return false;
	}

	inline bool Colisor::testColisionA(InterfaceToColide* subject, InterfaceToColide* other)
	{
		SDL_Rect& subBox = subject->boxInfo();

		if (methodToColide(subBox, other->boxInfo())) {
			subject->colided(other);
			return true;
		}
		return false;
	}
}