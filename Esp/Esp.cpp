#include "Esp.h"
#include "MemoryFunctions.h"
#include "Offsets.h"

/*
Default constructor
*/
Esp::Esp() {

	offsets::init();
	outlineComp = ReadChain(offsets::gameManager, std::vector<uintptr_t>{
		0x320,
		0x968
	});
	localPlayer = ReadChain(offsets::statusManager, std::vector<uintptr_t>{
		0x370, 
		0x0,
		0x28
	});

}


/*
cav esp

@return void
*/
void Esp::cavEsp() {

	uintptr_t entity_list = Read<uintptr_t>(offsets::gameManager + OFFSET_GAME_MANAGER_ENTITY_LIST);
	int entity_count = Read<DWORD>(offsets::gameManager + OFFSET_GAME_MANAGER_ENTITY_COUNT);

	for (int i = 0; i < entity_count; i++)
	{
		uintptr_t entity_object = Read<uintptr_t>(entity_list + i * 0x8);

		for (int a = 0; a < 6; a++) {

			uintptr_t addr4 = ReadChain(entity_object, std::vector<uintptr_t>{
				OFFSET_ENTITY_PAWN,
				0x18,
				0xD8,
				((uintptr_t)OFFSET_MAINCOMPONENT_ESPCHAIN + (a * 0x8))
			});

			int check = Read<int>(addr4 + OFFSET_ESPCHAIN_CHECK);

			// this check is required for my method of cav esp.
			if (check != 1)
				continue;


			if (Read<int>(addr4 + OFFSET_ESPCHAIN_WRITE1) != 1)
				Write<BYTE>(addr4 + OFFSET_ESPCHAIN_WRITE1, 1);


			if (Read<int>(addr4 + OFFSET_ESPCHAIN_WRITE2) != 1)
				Write<BYTE>(addr4 + OFFSET_ESPCHAIN_WRITE2, 1);


		}
	}

}

/*
outline esp

@return void
*/
void Esp::outlineEsp(bool toggle) {

	if (toggle) {

		setOutlineColor(false, teamOutlineColor);
		setOutlineColor(true, enemyOutlineColor);
		setOutline(true, false);
		Write<BYTE>(outlineComp + 0x348, toggle);
	}
	else {

		Write<BYTE>(outlineComp + 0x348, toggle);

	}

}

/*
Set outline color

@return false
*/
void Esp::setOutlineColor(bool team, Vector4 color) {

	Write<Vector4>(outlineComp + (team ? 0x50 : 0x60), color);

}

/*
Updates outline visiblity

@return void
*/
void Esp::setOutline(bool update, bool visible)
{

	uintptr_t objectArray = Read<uintptr_t>(outlineComp + 0x328);
	uint32_t objectArraySize = Read<uint32_t>(outlineComp + 0x330);
	for (size_t offset = 0x0; offset < objectArraySize * 0x90; offset += 0x90)
	{
		Write<BYTE>(objectArray + offset + 0x0, visible);
		Write<BYTE>(objectArray + offset + 0x2, update);
	}
}