#include "mainhack.h"

void InitImGui(LPDIRECT3DDEVICE9* pDevice, HWND* window);
void Init();

void Hack::Draw(HWND* window, LPDIRECT3DDEVICE9* pDevice)
{
	Hack::Menu::Draw(window, pDevice);

	if (Hack::Data::bWallhack)
	{
		Hack::Wallhack::Draw(pDevice);
	}
}

void Hack::Run(int *fpsLimit, int loopNumber)
{
	if (!Data::bInitialized)
	{
		Init();

		Data::bInitialized = true;
	}

	//bad memory address
	//if (*Data::IsLoading != 0)
	//{
	//	Data::bInitialized = false;
	//}

	Hack::Wallhack::GetEntities(*fpsLimit, loopNumber);
	Hack::StatFreeze::Freeze();
	Hack::Flight::Fly();
}

void Init()
{
	Hack::Data::studioRender = (uintptr_t)GetModuleHandle(L"studiorender.dll");
	Hack::Data::server = (uintptr_t)GetModuleHandle(L"server.dll");
	Hack::Data::engine = (uintptr_t)GetModuleHandle(L"engine.dll");
	Hack::Data::localPlayer = (uintptr_t*)(Hack::Data::server + HL2::Offsets::Server::offsetLocalPlayer);
	Hack::Data::playerHealth = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::health);
	Hack::Data::playerArmor = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::armor);
	Hack::Data::playerAuxPower = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::auxPower);
	Hack::Data::xPlayerPosition = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::xPosition);
	Hack::Data::zPlayerPosition = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::zPosition);
	Hack::Data::yPlayerPosition = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::yPosition);
	Hack::Data::xPlayerVelocity = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::xVelocity);
	Hack::Data::zPlayerVelocity = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::zVelocity);
	Hack::Data::yPlayerVelocity = (uintptr_t*)(*Hack::Data::localPlayer + HL2::Offsets::Server::LocalPlayerData::yVelocity);
	Hack::Data::xCameraAxis = (uintptr_t*)(Hack::Data::engine + HL2::Offsets::Engine::xCameraAxis);
	Hack::Data::yCameraAxis = (uintptr_t*)(Hack::Data::engine + HL2::Offsets::Engine::yCameraAxis);
	Hack::Data::IsLoading = (uintptr_t*)(Hack::Data::engine + HL2::Offsets::Engine::gameLoadingStatus);
	Hack::Data::gravity = (uintptr_t*)(Hack::Data::server + HL2::Offsets::Server::gravity);
	Hack::Data::fovBase = (uintptr_t*)(Hack::Data::engine + HL2::Offsets::Engine::fovBase);
	Hack::Data::fov = (uintptr_t*)(*Hack::Data::fovBase + HL2::Offsets::Engine::fov);
	Hack::Data::timeScale = (uintptr_t*)(Hack::Data::engine + HL2::Offsets::Engine::timeScale);
	Hack::Data::cbEntityList = (CBaseEntityList*)(Hack::Data::server + 0x634164);
	Hack::Data::viewMatrix = (ViewMatrix*)(Hack::Data::engine + 0x58BAA8);

	EntityInfo entityInfo;
	Hack::Data::entitiesToESP.clear();

	entityInfo.entityType = *(uintptr_t*)*(uintptr_t*)(Hack::Data::server + 0x634914); //CNPC_CScanner 
	entityInfo.height = 18600;
	entityInfo.width = 18600;
	entityInfo.center = true;
	entityInfo.color = D3DCOLOR_ARGB(255, 0, 0, 255);
	Hack::Data::entitiesToESP.push_back(entityInfo); 

	entityInfo.entityType = *(uintptr_t*)*(uintptr_t*)(Hack::Data::server + 0x6361B4); //CNPC_Citizen 
	entityInfo.height = 37200;
	entityInfo.width = 18600;
	entityInfo.center = false;
	entityInfo.color = D3DCOLOR_ARGB(255, 255, 0, 255);
	Hack::Data::entitiesToESP.push_back(entityInfo); //CNPC_Citizen 

	//Hack::Data::entitiesToESP.push_back(0x7AA932B4); //CPNC_Vortigaunt 
	//faulty address
	//Hack::Data::entitiesToESP.push_back(*(uintptr_t*)*(uintptr_t*)(Hack::Data::server + 0x637054)); //CNC_MetroPolice
}

namespace Hack
{
	namespace Data
	{
		//Game
		uintptr_t client;
		uintptr_t engine;
		uintptr_t server;
		uintptr_t studioRender;
		uintptr_t* localPlayer;
		uintptr_t* IsLoading;
		uintptr_t* fovBase;
		uintptr_t* fov;
		uintptr_t* timeScale;
		uintptr_t* ingameCheats;

		//Wallhack
		std::vector<EntityData> entities;
		std::vector<EntityInfo> entitiesToESP;
		ViewMatrix* viewMatrix;
		ID3DXLine* dxLine;
		CBaseEntityList* cbEntityList;
		float WallhackDistance = 5000;

		//Stats
		uintptr_t* playerHealth;
		uintptr_t* playerArmor;
		uintptr_t* playerAuxPower;

		//Movement
		uintptr_t* xPlayerPosition;
		uintptr_t* zPlayerPosition;
		uintptr_t* yPlayerPosition;
		uintptr_t* xPlayerVelocity;
		uintptr_t* zPlayerVelocity;
		uintptr_t* yPlayerVelocity;
		uintptr_t* yCameraAxis;
		uintptr_t* xCameraAxis;
		uintptr_t* gravity;

		//Toggles
		bool bInitialized = false;
		bool bHealthFreeze = false;
		bool bArmorFreeze = false;
		bool bFlyMode = false;
		bool bGravity = false;
		bool bAuxPowerFreeze = false;
		bool bWallhack = false;

		//Values
		float flightSpeed = 5;
	}
}