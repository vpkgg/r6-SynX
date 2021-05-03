#include "GunMod.h"
#include "MemoryFunctions.h"
#include "Offsets.h"

/*
Default constructor
*/
GunMod::GunMod() {

	offsets::init();

	// set base offsets for this object
	localPlayer = ReadChain(offsets::statusManager, std::vector<uintptr_t>{
		0x370,
		0x0,
		0x28
	});

	// store default values
	defaultDamage = getDamage();
	defaultRecoil = getRecoil();
	defaultSpread = getSpread();

}

/*
Gets recoil

@return float recoil
*/
float GunMod::getRecoil() {

	uintptr_t LpCurrentDisplayWeapon = ReadChain(localPlayer, std::vector<uintptr_t>{
		0x98,
		0xC8,
		0x208,
		0xA0
	});

	return Read<float>(LpCurrentDisplayWeapon);

}


/*
Gets spread

@return float spread
*/
float GunMod::getSpread() {

	uintptr_t LpCurrentDisplayWeapon = ReadChain(localPlayer, std::vector<uintptr_t>{
		0x98,
		0xC8,
		0x208,
		0x50,
		0x0
	});

	return Read<float>(LpCurrentDisplayWeapon);

}

/*
Gets the amount of bullets your gun shoots

@return unsigned int amount of bullets current gun shoots
*/
unsigned int GunMod::getDamage() {

	uintptr_t bulletCount = ReadChain(offsets::gameManager, std::vector<uintptr_t>{
		0x1F8,
		0xD8,
		0x48,
		0x130,
		0x120,
		0x0
	});

	//unsigned int because we can only shoot < 0 bullets
	return Read<unsigned int>(bulletCount + 0x40);

}

/*
Sets damage

@return void
*/
void GunMod::setDamage(int dmg) {


	uintptr_t bulletCount = ReadChain(offsets::gameManager, std::vector<uintptr_t>{
		0x1F8,
		0xD8,
		0x48,
		0x130,
		0x120,
		0x0
	});

	//unsigned int because we can only shoot > 0 bullets
	Write<unsigned int>(bulletCount + 0x40, dmg);

}

/*
Sets spread

@return void
*/
void GunMod::setSpread(float spread) {

	uintptr_t LpCurrentDisplayWeapon = ReadChain(localPlayer, std::vector<uintptr_t>{
		0x98,
		0xC8,
		0x208
	});

	Write<float>(LpCurrentDisplayWeapon + 0x50, spread);

}

/*
Sets recoil

@return void
*/
void GunMod::setRecoil(float recoil) {

	uintptr_t LpCurrentDisplayWeapon = ReadChain(localPlayer, std::vector<uintptr_t>{
		0x98,
		0xC8,
		0x208
	});

	Write<float>(LpCurrentDisplayWeapon + 0xA0, recoil);

}

/*
resets recoil back to what it was (for the gun you enabled no recoil for)

@return void
*/
void GunMod::resetRecoil() {

	setRecoil(defaultRecoil);

}


/*
resets spread back to what is was (for the gun you enabled no spread for)

@return void
*/
void GunMod::resetSpread() {


	setSpread(defaultSpread);

}

/*
Toggle impact bullets on/off
*/
void GunMod::impactBullet(bool toggle) {


	if (toggle == true) {

		setDamage(125); //you can make this bigger but it will crash the game.
		setRecoil(0); // we dont need recoil
		setSpread(2); // make this bigger so its like a shotgun

	}
	else {

		void resetSpread();
		void resetRecoil();
		void resetDamage();

	}
	

}

/*
No Recoil

@return void
*/
void GunMod::noSpread(bool toggle) {

	if (toggle == true) {

		setSpread(0);

	}
	else {

		resetSpread();

	}

}

/*
No Spread

@return void
*/
void GunMod::noRecoil(bool toggle) {

	if (toggle == true) {

		setRecoil(0);

	}
	else {

		resetRecoil();

	}

}