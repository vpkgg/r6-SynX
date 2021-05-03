#pragma once
#include "Glow.h"
#include "PlayerMod.h"
#include "GunMod.h"
#include "Esp.h"

#include <thread>
#include <atomic>

class RainbowSix {

public:

	RainbowSix();
	void start();

private:

	void input();
	void rainbowGlow();
	std::thread inputThread;
	std::thread rainbowGlowThread;

	bool glowToggle;
	bool cavToggle;
	bool outlineToggle;
	bool noRecoilToggle;
	bool speedHacksToggle;
	bool impactBulletsToggle;
	bool noFlashToggle;
	bool highFovToggle;
	bool noClipToggle;

	PlayerMod playerMod;
	GunMod gunMod;
	Glow glow;
	Esp esp;

};