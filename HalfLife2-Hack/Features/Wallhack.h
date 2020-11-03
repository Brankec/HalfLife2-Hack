#pragma once
#include <d3dx9.h>
#include <math.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_win32.h"
#include "../imgui/imgui_impl_dx9.h"
#include <vector>

//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class ViewMatrix
{
public:
	float matrix[4][4]; //0x0000
	char pad_0040[1384]; //0x0040
}; //Size: 0x05A8
static_assert(sizeof(ViewMatrix) == 0x5A8);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

//entity list pointer array
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
class clientInfo
{
public:
	class Entity* entPtr; //0x0000
	char pad_0004[12]; //0x0004
}; //Size: 0x0010
static_assert(sizeof(clientInfo) == 0x10);

class CBaseEntityList
{
public:
	class clientInfo ents[2048]; //0x0000
}; //Size: 0x8000
static_assert(sizeof(CBaseEntityList) == 0x8000);

class Entity
{
public:
	int entityType; //0x0000
	char pad_0004[36]; //0x0004
	float xPosition; //0x0028
	float zPosition; //0x002C
	float yPosition; //0x0030
	char pad_0034[172]; //0x0034
	int health; //0x00E0
	char pad_00E4[104]; //0x00E4
}; //Size: 0x014C
static_assert(sizeof(Entity) == 0x14C);
//+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

class EntityInfo
{
public:
	float height;
	float width;
};


namespace Hack
{
	namespace Wallhack
	{
		void GetEntities(int fpsLimit, int loopNumber);
		void Draw(LPDIRECT3DDEVICE9* pDevice);
	}
}
