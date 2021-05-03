#include "PlayerMod.h"
#include "MemoryFunctions.h"
#include "Offsets.h"
#include <vector>
#include <cstdint>

/*
Default construtor, get all of the default values for the following hacks.
*/
PlayerMod::PlayerMod() {

	offsets::init();

	//get the default values
	defaultSpeed = getCurrentSpeed();
	defaultWeaponFov = getCurrentWeaponFov();
	defaultPlayerFov = getCurrentPlayerFov();

}


/*
spectator mode

@return void
*/
void PlayerMod::spectator(bool toggle) {

	if (toggle)
		Write<char>(offsets::spectatorManager + OFFSET_SPOOF_SPECTATE_ENABLE, 1);
	else 
		Write<char>(offsets::spectatorManager + OFFSET_SPOOF_SPECTATE_ENABLE, 0);

}

/*
Speed hack

@return void
*/
void PlayerMod::speedHack(bool toggle) {

	if (toggle)
		setSpeed(PlayerMod::defaultSpeed + 0.5);
	else
		setSpeed(PlayerMod::defaultSpeed);

}

/*
Set speed of player

@return void
*/
void PlayerMod::setSpeed(float speed) {

	uintptr_t playerSpeed = ReadChain(offsets::statusManager, std::vector<uintptr_t>{ 
		0x370, 
		0x0
	});
	Write<float>(playerSpeed + 0x48, speed);

}

/*
Makes player model fov and weapon fov 0.5 higher

@return void
*/
void PlayerMod::highFov(bool toggle) {

	if (toggle) {

		setCurrentPlayerFov(defaultPlayerFov + 1); 
		setCurrentWeaponFov(defaultWeaponFov + 1);

	}
	else {

		setCurrentPlayerFov(defaultPlayerFov);
		setCurrentWeaponFov(defaultWeaponFov);

	}
		
}

/*
Removes flash/stun effect

@return void
*/
void PlayerMod::noFlash(bool toggle) {

	uintptr_t lpFxStun = ReadChain(offsets::statusManager, std::vector<uintptr_t> {
		0x370, 
		0x0,
		0x28,
		0x30, 
		0x30, 
		((uintptr_t) (5 * sizeof(PVOID)))
	});

	if(toggle)
		Write<uint8_t>(lpFxStun + 0x40, 0);
	else
		Write<uint8_t>(lpFxStun + 0x40, 1);

}


/*
Get current speed of player

@return float, speed of player
*/
float PlayerMod::getCurrentSpeed() {

	uintptr_t playerSpeed = ReadChain(offsets::statusManager, std::vector<uintptr_t>{
		0x370, 
		0x0
	});

	return Read<float>(playerSpeed + 0x48);

}

/*
Gets current player fov

@return float fov
*/
float PlayerMod::getCurrentPlayerFov() {

	uintptr_t playerFov = ReadChain(Read<uintptr_t>(offsets::baseAddress + OFFSET_FOV_CHANGER), std::vector<uintptr_t>{
		0x28, 
		0x0
	});
	
	float fov = Read<float>(playerFov + 0x38);
	std::cout << fov << std::endl;
	return fov;


}


/*
gets current weapon fov

@return float current weapon fov
*/
float PlayerMod::getCurrentWeaponFov() {

	uintptr_t weaponFov = ReadChain(Read<uintptr_t>(offsets::baseAddress + OFFSET_FOV_CHANGER), std::vector<uintptr_t>{
		0x28,
		0x0
	});

	float fov = Read<float>(weaponFov + 0x3C);
	std::cout << fov << std::endl;
	return fov;

}

/*
Sets weapon fov

@return void
*/
void PlayerMod::setCurrentPlayerFov(float fov) {

	uintptr_t playerFov = ReadChain(Read<uintptr_t>(offsets::baseAddress + OFFSET_FOV_CHANGER), std::vector<uintptr_t>{
		0x28,
		0x0
	});

	Write<float>(playerFov + 0x38, fov);

}

/*
Sets player model fov

@return void
*/
void PlayerMod::setCurrentWeaponFov(float fov) {

	uintptr_t weaponFov = ReadChain(Read<uintptr_t>(offsets::baseAddress + OFFSET_FOV_CHANGER), std::vector<uintptr_t>{
		0x28,
		0x0
	});

	Write<float>(weaponFov + 0x3C, fov);

}


void PlayerMod::noClip(bool toggle) {

	uintptr_t noclip = ReadChain(Read<uintptr_t>(offsets::baseAddress + OFFSET_NETWORK_MANAGER), std::vector<uintptr_t>{
		0xF0,
		0x8
	});

	Write<int>(noclip, toggle);

}