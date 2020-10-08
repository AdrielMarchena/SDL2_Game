#include "Colisor.h"
#include <iostream>
namespace Colisions {

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
			//for (size_t j = 0; j < objToColide.size(); j++) {
			if (i == firstMember)
				continue;
			testColision(objToColide[0], objToColide[i]);
			//}
		}
	}
	/*
	Only notificate the first obj
	*/
	inline void Colisor::processFirstToAll_A()
	{
		for (size_t i = 0; i < objToColide.size(); i++) {
			//for (size_t j = 0; j < objToColide.size(); j++) {
			if (i == firstMember)
				continue;
			testColision(objToColide[0], objToColide[i]);
			//}
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

	void Colisor::setModeToColide(const unsigned int& mode)
	{
		this->mode = mode;
	}
	/*
		Not tested
	*/
	void Colisor::setFirstMember(InterfaceToColide* obj)
	{
		for (int i = 0; i < objToColide.size(); i++) {
			if (obj == objToColide[i])
			{
				firstMember = i;
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