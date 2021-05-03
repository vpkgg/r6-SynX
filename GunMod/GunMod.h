#pragma once
#include <cstdint>

class GunMod {

public:
	
	GunMod();
	void impactBullet(bool enable);
	void noRecoil(bool toggle);
	void noSpread(bool toggle);
	void resetSpread();
	void resetRecoil();
	void resetDamage();

private:

	void setDamage(int damage);
	void setRecoil(float recoil);
	void setSpread(float spread);

	float getSpread();
	float getRecoil();
	unsigned int getDamage();

	float defaultSpread;
	float defaultRecoil; 
	int defaultDamage; //damage is how many bullets we shoot, we cant shoot 1/2 a bullet

	uintptr_t localPlayer; // RainbowSix.exe + 0x505E398 (status manager) ] + 0x370 ] +0x0 ] + 0x28
};