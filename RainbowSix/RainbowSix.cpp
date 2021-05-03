#include "RainbowSix.h"
#include "Offsets.h"
#include <thread>
#include <windows.h>


RainbowSix::RainbowSix() {

	//deleting this will cause you pain. This is required for setting global offsets and pid
	offsets::init();

}


/*
Threaded function that handles input

@return void
*/
void RainbowSix::input() {

	std::cout << "[+] F1: glow" << std::endl;
	std::cout << "[+] F2: cav esp" << std::endl;
	std::cout << "[+] F3: outline esp" << std::endl;
	std::cout << "[+] F4: no recoil/spread" << std::endl;
	std::cout << "[+] F5: speed hacks" << std::endl;
	std::cout << "[+] F6: impact bullets" << std::endl;
	std::cout << "[+] F7: no flash" << std::endl;
	std::cout << "[+] F8: high fov" << std::endl;

	while (true) {
		
		// if you press f1 (glow)
		if(GetAsyncKeyState(0x70) != 0) {

			if (glowToggle == true) {

				std::cout << "[GLOW] Disabled" << std::endl;
				glowToggle = false;

			}
			else {

				glowToggle = true;
				std::cout << "[GLOW] Enabled" << std::endl;

			}

		}

		//if you press f2 (cav esp)
		if (GetAsyncKeyState(0x71) != 0) {

			std::cout << "[ESP] Enabled" << std::endl;
			esp.cavEsp();

		}

		//if you press f3 (outline esp)
		if (GetAsyncKeyState(0x72) != 0) {

			if (outlineToggle) {

				std::cout << "[OUTLINE] Disabled" << std::endl;
				outlineToggle = false;
				esp.outlineEsp(outlineToggle);

			}
			else {

				std::cout << "[OUTLINE] Enabled" << std::endl;
				outlineToggle = true;
				esp.outlineEsp(outlineToggle);

			}

			

		}
		
		//if you press f4 (no recoil/spread)
		if (GetAsyncKeyState(0x73) != 0) {

			if (noRecoilToggle) {

				std::cout << "[RECOIL/SPREAD] Disabled" << std::endl;
				noRecoilToggle = false;
				gunMod.noRecoil(noRecoilToggle);
				gunMod.noSpread(noRecoilToggle);

			}
			else {

				std::cout << "[RECOIL/SPREAD] Enabled" << std::endl;
				noRecoilToggle = true;
				gunMod.noRecoil(noRecoilToggle);
				gunMod.noSpread(noRecoilToggle);

			}

		}

		//if you press f5 (speed hacks)
		if (GetAsyncKeyState(0x74) != 0) {

			if (speedHacksToggle) {

				speedHacksToggle = false;
				playerMod.speedHack(speedHacksToggle);
				std::cout << "[SPEED] Disabled" << std::endl;

			}
				
			else {

				speedHacksToggle = true;
				playerMod.speedHack(speedHacksToggle);
				std::cout << "[SPEED] Enabled" << std::endl;

			}

		}

		//if you press f6 (impact bullets)
		if (GetAsyncKeyState(0x75) != 0) {

			if (impactBulletsToggle) {

				impactBulletsToggle = false;
				gunMod.impactBullet(impactBulletsToggle);
				std::cout << "[IMPACT_BULLETS] Disabled" << std::endl;

			}
			else {

				impactBulletsToggle = true;
				gunMod.impactBullet(impactBulletsToggle);
				std::cout << "[IMPACT_BULLETS] Enabled" << std::endl;

			}

		}

		//if you press f7 (no flash)
		if (GetAsyncKeyState(0x76) != 0) {

			if (noFlashToggle) {

				noFlashToggle = false;
				playerMod.noFlash(noFlashToggle);
				std::cout << "[NOFLASH] Disabled" << std::endl;

			}
			else {

				noFlashToggle = true;
				playerMod.noFlash(noFlashToggle);
				std::cout << "[NOFLASH] Enabled" << std::endl;

			}

		}

		//if you press f8 (high fov)
		if (GetAsyncKeyState(0x77) != 0) {

			if (highFovToggle) {

				highFovToggle = false;
				playerMod.highFov(highFovToggle);
				std::cout << "[HIGHFOV] Disabled" << std::endl;

			}
			else {

				highFovToggle = true;
				playerMod.highFov(highFovToggle);
				std::cout << "[HIGHFOV] Enabled" << std::endl;

			}

		}

		//if we press f9 (no clip)
		if (GetAsyncKeyState(0x78)) {

			if (noClipToggle) {

				noClipToggle = false;
				playerMod.noClip(noClipToggle);
				std::cout << "[NOCLIP] Disabled noclip" << std::endl;

			}
			else {

				noClipToggle = true;
				playerMod.noClip(noClipToggle);
				std::cout << "[NOCLIP] Enabled noclip" << std::endl;


			}

		}

		Sleep(250);

	}

}

/*
Starts threads associated with hacks

@return void
*/
void RainbowSix::start() {

	inputThread = std::thread(&RainbowSix::input, this);
	rainbowGlowThread = std::thread(&RainbowSix::rainbowGlow, (this));
	inputThread.detach();
	rainbowGlowThread.detach();

}

/*
Threaded function for rainbow glow

@return void
*/
void RainbowSix::rainbowGlow() {

	while (true) {

		if (glowToggle == true) {

			glow.randomGlow();
			
		}

		Sleep(100);

	}

}