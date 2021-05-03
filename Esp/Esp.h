#pragma once
#include <cstdint>
#include "Vectors.h"

class Esp {

public:

	Esp();
	void outlineEsp(bool toggle);
	void cavEsp();

private:

	uintptr_t localPlayer;
	uintptr_t outlineComp;

	void setOutlineColor(bool team, Vector4 color);
	void setOutline(bool update, bool visible);

	Vector4 teamOutlineColor = Vector4(0.0, 0.0, 1.0, 1.0);
	Vector4 enemyOutlineColor = Vector4(1.0, 0.0, 0.0, 1.0);

};