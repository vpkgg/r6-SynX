#pragma once
#include "MemoryFunctions.h"
// new update offsets

#define OFFSET_GAME_MANAGER 0x505E3B8
#define OFFSET_GLOW_MANAGER 0x5cb69f0
#define OFFSET_STATUS_MANAGER 0x505E398
#define OFFSET_NETWORK_MANAGER 0x504DC20
#define OFFSET_GAME_Renderer 0x505E230
#define OFFSET_PLAYER_MANAGER 0x504B488
#define OFFSET_ROUNDMANAGER 0x504DC80
#define OFFSET_FOV_CHANGER 0x505E370 


#define OFFSET_SPOOF_SPECTATE 0x504dc10    // 0x4ff0eb8 
#define OFFSET_SPOOF_SPECTATE_ENABLE 0x5D

#define OFFSET_GAME_MANAGER_ENTITY_COUNT 0x1D0
#define OFFSET_GAME_MANAGER_ENTITY_LIST 0x1C8
#define OFFSET_STATUS_MANAGER_LOCALENTITY 0x28
#define OFFSET_STATUS_MANAGER_CONTAINER 0x370

#define OFFSET_ENTITY_PAWN 0x20
#define OFFSET_MAINCOMPONENT_ESPCHAIN 0x78
#define OFFSET_ESPCHAIN_WRITE1 0x532
#define OFFSET_ESPCHAIN_WRITE2 0x534

#define OFFSET_ESPCHAIN_CHECK 0x531

// new offsets here.

#define OFFSET_ENTITY_REPLICATION 0xC8
#define OFFSET_ENTITY_REPLICATION_TEAM 0x190


// camera stuff.

#define OFFSET_CAMERA_MANAGER 0X504EC18
#define OFFSET_CAMERA_ENGINELINK 0x120
#define OFFSET_CAMERA_ENGINE 0x1C8
#define OFFSET_CAMERA_ENGINE_CAMERA 0x08

#define OFFSET_CAMERA_VIEWFOVY 0x124
#define OFFSET_CAMERA_VIEWFOVX 0x110
#define OFFSET_CAMERA_VIEWFORWARD 0xF0
#define OFFSET_CAMERA_VIEWUP 0xE0
#define OFFSET_CAMERA_VIEWRIGHT 0xD0
#define OFFSET_CAMERA_VIEWTRANSLATION 0x100


// outdated maybe
//#define OFFSET_ENTITY_HEAD 0x180 
//#define OFFSET_ENTITY_FEET 0x1D0


// updated offsets.

#define OFFSET_ENTITY_SKELETON 0x20
#define OFFSET_SKELETON_POSITION 0x700
#define OFFSET_SKELETON_HEADPOSITION 0x6A0
#define OFFSET_ENTITYPAWN_FEET 0x700

#define OFFSET_ENTITY_COMPONENT	0xD8
#define OFFSET_ENTITY_COMPONENT_LIST 0x8
#define ENTITY_MARKER_VT_OFFSET 0x37AA6F0
#define ENTITY_MARKER_ENABLED_OFFSET  0x530


namespace offsets {

    static uintptr_t baseAddress = NULL;
    static uintptr_t statusManager;
	static uintptr_t glowManager;
	static uintptr_t gameManager;
	static uintptr_t fovManager;
	static uintptr_t cameraManager;
	static uintptr_t spectatorManager;

	static void init() {

		if (baseAddress == NULL) {

			PID = GetProcessID("RainbowSix.exe");
			offsets::baseAddress = GetModuleBaseAddr("RainbowSix.exe");
			offsets::statusManager = Read<uintptr_t>(offsets::baseAddress + OFFSET_STATUS_MANAGER);
			offsets::glowManager = Read<uintptr_t>(offsets::baseAddress + OFFSET_GLOW_MANAGER);
			offsets::gameManager = Read<uintptr_t>(offsets::baseAddress + OFFSET_GAME_MANAGER);
			offsets::fovManager = Read<uintptr_t>(offsets::baseAddress + OFFSET_FOV_CHANGER);
			offsets::cameraManager = Read<uintptr_t>(offsets::baseAddress + OFFSET_CAMERA_MANAGER);
			offsets::spectatorManager = Read<uintptr_t>(offsets::baseAddress + OFFSET_SPOOF_SPECTATE);

		}

	}

}