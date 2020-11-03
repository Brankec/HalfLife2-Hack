#pragma once
#include <d3dx9.h>
#include <math.h>
#include "imgui/imgui.h"
#include "imgui/imgui_impl_win32.h"
#include "imgui/imgui_impl_dx9.h"
#include <vector>
#include "Features/Wallhack.h"
#include "Features/Flight.h"
#include "Features/StatFreeze.h"
#include "Features/Menu.h"

struct vec4
{
	float x, z, y, w;
};
struct vec3
{
	float x, z, y;
};
struct vec2
{
	float x, y;
};

namespace HL2
{
	namespace Offsets
	{
		namespace Client
		{
			const uintptr_t dwAttack = 0x4602D0;

			namespace ClientData
			{
			}
		}

		namespace Engine
		{
			const uintptr_t xCameraAxis = 0x456DF8;
			const uintptr_t yCameraAxis = 0x456DF4;
			const uintptr_t gameLoadingStatus = 0x40BFFC;
			const uintptr_t timeScale = 0x611F84;

			const uintptr_t fovBase = 0x446E7C;
			const uintptr_t fov = 0x1048;
		}

		namespace Server
		{
			//const mem_t dwEntityList = 0x4B0FB4;
			const uintptr_t offsetLocalPlayer = 0x00634174;
			const uintptr_t gravity = 0x64DB8C;

			namespace LocalPlayerData
			{
				const uintptr_t health = 0xE0;
				const uintptr_t armor = 0xD30;
				const uintptr_t auxPower = 0x10CC;
				const uintptr_t xVelocity = 0x214;
				const uintptr_t zVelocity = 0x218;
				const uintptr_t yVelocity = 0x21C;
				const uintptr_t xPosition = 0x27C;
				const uintptr_t zPosition = 0x280;
				const uintptr_t yPosition = 0x284;
			}
		}
	}
}

namespace Hack
{
	//Called inside the hkEndSceen method
	void Draw(HWND* window, LPDIRECT3DDEVICE9* pDevice);

	//Called inside MainThread method
	void Run(int* fpsLimit, int loopNumber);

	namespace Data
	{
		//Game
		extern uintptr_t client;
		extern uintptr_t engine;
		extern uintptr_t server;
		extern uintptr_t studioRender;
		extern uintptr_t* localPlayer;
		extern uintptr_t* IsLoading;
		extern uintptr_t* fovBase;
		extern uintptr_t* fov;
		extern uintptr_t* timeScale;
		extern uintptr_t* ingameCheats;

		//Wallhack
		extern std::vector<Entity*> entities;//list of entities pulled from entityList based on entitiestToESP vector
		extern std::vector<uintptr_t> entitiesToESP;//list of entities to pull from entityList
		extern ViewMatrix* viewMatrix;
		extern ID3DXLine* dxLine;
		extern CBaseEntityList* cbEntityList;
		extern float WallhackDistance;

		//Stats
		extern uintptr_t* playerHealth;
		extern uintptr_t* playerArmor;
		extern uintptr_t* playerAuxPower;

		//Movement
		extern uintptr_t* xPlayerPosition;
		extern uintptr_t* zPlayerPosition;
		extern uintptr_t* yPlayerPosition;
		extern uintptr_t* xPlayerVelocity;
		extern uintptr_t* zPlayerVelocity;
		extern uintptr_t* yPlayerVelocity;
		extern uintptr_t* yCameraAxis;
		extern uintptr_t* xCameraAxis;
		extern uintptr_t* gravity;

		//Toggles
		extern bool bInitialized;
		extern bool bHealthFreeze;
		extern bool bArmorFreeze;
		extern bool bFlyMode;
		extern bool bGravity;
		extern bool bAuxPowerFreeze;
		extern bool bWallhack;

		//Values
		extern float flightSpeed;
	}
}