#include "Glow.h"
#include "Offsets.h"
#include <random>

// Glow data defs

/*
Make a new glow color
*/
GlowColor::GlowColor(float r, float g, float b, float a, float distance) {

	offsets::init();
	gColor.red = r;
	gColor.green = g;
	gColor.blue = b;

	gColorData.alpha = a;
	gColorData.distance = distance;


}


// Glow defs

Glow::Glow(float r, float g, float b, float a, float distance) {

	offsets::init();
	glowBase = Read<uintptr_t>(offsets::glowManager + 0xB8);
	glowColor = GlowColor(r, g, b, a, distance);

}

Glow::Glow() {

	offsets::init();
	glowBase = Read<uintptr_t>(offsets::glowManager + 0xB8);

}

/*
Returns the current color of glow
*/
GlowColor::Color GlowColor::getCurrentGlowColor() {

	return gColor;

}

/*
Updates glow color with glowColor and glowColorData structs
*/
void Glow::updateColor() {

	Write<GlowColor::Color>(glowBase + 0x110, glowColor.gColor);
	Write<GlowColor::ColorData>(glowBase + 0x130, glowColor.gColorData);

}

/*
Updates glow color with passed GlowColor
*/
void Glow::updateColor(GlowColor gColor) {

	glowColor = gColor;
	Write<GlowColor::Color>(glowBase + 0x110, glowColor.gColor);
	Write<GlowColor::ColorData>(glowBase + 0x130, glowColor.gColorData);

}

/*
Updates glow color with passed GlowColor
*/
void Glow::updateColor(float r, float g, float b, float a, float distance) {

	glowColor = GlowColor(r, g, b, a, distance);

	Write<GlowColor::Color>(glowBase + 0x110, glowColor.gColor);
	Write<GlowColor::ColorData>(glowBase + 0x130, glowColor.gColorData);

}


/*
Set the color of glow
*/
void Glow::setColor(GlowColor gColor) {

	glowColor = gColor;
	updateColor();

}


void Glow::setColor(float r, float g, float b, float a, float distance) {

	glowColor = GlowColor(r, g, b, a, distance);

}

/*
Applies a random glow/color
*/
void Glow::randomGlow() {

	std::random_device seeder;
	std::ranlux48 gen(seeder());
	std::uniform_int_distribution<int>  uniform_0_255(0, 255);

	glowColor = GlowColor(uniform_0_255(gen), uniform_0_255(gen), uniform_0_255(gen), 999, 0);
	updateColor();

}