#pragma once
#include <cstdint>
#include "Vectors.h"

class PlayerMod {

public:

	//construtors
	PlayerMod();

	//public methods
	void spectator(bool toggle);
	void speedHack(bool toggle);
	void highFov(bool toggle);
	void noFlash(bool toggle);
	void noClip(bool toggle);

private:

	// getters
	float getCurrentWeaponFov();
	float getCurrentPlayerFov();
	float getCurrentSpeed();

	// setters
	void setSpeed(float speed);
	void setCurrentWeaponFov(float fov);
	void setCurrentPlayerFov(float fov);

	//private class vars
	float defaultSpeed;
	float defaultWeaponFov;
	float defaultPlayerFov;
	

};