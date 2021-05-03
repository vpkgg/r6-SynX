#pragma once
#include <cstdint>
#include <vector>
#include "MemoryFunctions.h"
#include <thread>
#include "Vectors.h"

class GlowColor {

public:

	GlowColor() {} //default constructor
	GlowColor(float r, float g, float b, float a, float distance);

	// we make two structs because the alpha and distance are 24 bytes away (sorry)
	struct Color {

		float red;
		float green;
		float blue;

	};
	struct ColorData {

		float alpha; //alpha
		float distance;

	};

	Color gColor;
	ColorData gColorData;

private:

	Color getCurrentGlowColor();

};

class Glow {

public:

	Glow();
	Glow(float r, float g, float b, float a, float distance);
	void randomGlow();
	void setColor(GlowColor gColor);
	void setColor(float r, float g, float b, float a, float distance);
	

private:

	
	bool toggle;
	uintptr_t glowBase; // RainbowSix.exe + OFFSET_GLOW_MANAGER ] + 0xB8
	GlowColor glowColor;
	void updateColor();
	void updateColor(GlowColor gColor);
	void updateColor(float r, float g, float b, float a, float distance);
	Vector4 randomColor();

};