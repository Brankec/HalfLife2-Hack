#include "Wallhack.h"
#include "../mainhack.h"

bool OnEntityList(int entityType);
void DrawESPBox(Entity* ent, vec2 screen, LPDIRECT3DDEVICE9* pDevice);
void DrawOutline(float x, float y, float width, float height, float lineWidth, D3DCOLOR color, LPDIRECT3DDEVICE9* pDevice);
void DrawLine(float xSrc, float ySrc, float xDst, float yDst, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice);
bool WorldToScreen(vec3 pos, vec2& screen, float matrix[4][4], int windowWidth, int windowHeight);

int windowWidth = 1176;
int windowHeight = 664;
int seconds = 0;
float entityHeight = 5;
float entityWindow = 5;
float entityAspectRatio = entityHeight / entityWindow;

void Hack::Wallhack::GetEntities(int fpsLimit, int loopNumber)
{
	//increment every second
	if (loopNumber == fpsLimit)
	{
		seconds++;
	}

	//Every 5 seconds run the code
	if (seconds >= 5)
	{
		Hack::Data::entities.clear();
		seconds = 0;
		for (auto ent : Hack::Data::cbEntityList->ents)
		{
			if (ent.entPtr && ent.entPtr->entityType && OnEntityList(ent.entPtr->entityType))
			{
				Hack::Data::entities.push_back(ent.entPtr);
				//Hack::Data::entities.push_back(ent.entPtr);
				//ent.entPtr->health = 0;
			}
		}
	}
}

void Hack::Wallhack::Draw(LPDIRECT3DDEVICE9* pDevice)
{
	for (int i = 0; i < Hack::Data::entities.size(); i++)
	{
		if (Hack::Data::entities[i]) //only displaying the first entity for testing purposes
		{
			vec3 center;
			center.x = Hack::Data::entities[i]->xPosition;//x is horizontal
			center.z = Hack::Data::entities[i]->yPosition;//z is vertical
			center.y = Hack::Data::entities[i]->zPosition;//y is horizontal

			vec2 screenCoords;

			if (WorldToScreen(center, screenCoords, Hack::Data::viewMatrix->matrix, windowWidth, windowHeight))
			{
				DrawESPBox(Hack::Data::entities[i], screenCoords, pDevice);
			}
		}
	}
}

void DrawESPBox(Entity* ent, vec2 screen, LPDIRECT3DDEVICE9* pDevice)
{
	vec3 playerPos;
	playerPos.x = *(float*)Hack::Data::xPlayerPosition;
	playerPos.z = *(float*)Hack::Data::zPlayerPosition;
	playerPos.y = *(float*)Hack::Data::yPlayerPosition;

	float dist = sqrt(pow((ent->xPosition - playerPos.x), 2) + pow((ent->yPosition - playerPos.y), 2) + pow((ent->zPosition - playerPos.z), 2));

	float scale = 20;//(windowHeight / dist) * (viewport[2] / windowWidth);
	float x = screen.x - scale;
	float y = screen.y - scale * entityAspectRatio;
	float width = scale * 2;
	float height = scale * entityAspectRatio * 2;

	DrawOutline(x, y, width, height, 2, D3DCOLOR_ARGB(255, 0, 0, 255), pDevice);
}

void ESP()
{
}

void DrawOutline(float x, float y, float width, float height, float lineWidth, D3DCOLOR color, LPDIRECT3DDEVICE9* pDevice)
{
	//left
	DrawLine(x, y, x, y + height, lineWidth, D3DCOLOR_ARGB(255, 0, 0, 255), *pDevice);
	//top
	DrawLine(x, y, x + width, y, lineWidth, D3DCOLOR_ARGB(255, 0, 0, 255), *pDevice);
	//right
	DrawLine(x + width, y, x + width, y + height, lineWidth, D3DCOLOR_ARGB(255, 0, 0, 255), *pDevice);
	//bottom
	DrawLine(x, y + height, x + width, y + height, lineWidth, D3DCOLOR_ARGB(255, 0, 0, 255), *pDevice);
}

void DrawLine(float xSrc, float ySrc, float xDst, float yDst, int thickness, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	if (!Hack::Data::dxLine)
		D3DXCreateLine(pDevice, &Hack::Data::dxLine);

	D3DXVECTOR2 Line[2];
	Line[0] = D3DXVECTOR2(xSrc, ySrc);
	Line[1] = D3DXVECTOR2(xDst, yDst);
	Hack::Data::dxLine->SetWidth(thickness);
	Hack::Data::dxLine->Draw(Line, 2, color);
}

bool WorldToScreen(vec3 pos, vec2& screen, float matrix[4][4], int windowWidth, int windowHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	vec4 clipCoords;
	clipCoords.x = pos.x * matrix[0][0] + pos.y * matrix[0][1] + pos.z * matrix[0][2] + matrix[0][3];
	clipCoords.y = pos.x * matrix[1][0] + pos.y * matrix[1][1] + pos.z * matrix[1][2] + matrix[1][3];
	clipCoords.z = pos.x * matrix[2][0] + pos.y * matrix[2][1] + pos.z * matrix[2][2] + matrix[2][3];
	clipCoords.w = pos.x * matrix[3][0] + pos.y * matrix[3][1] + pos.z * matrix[3][2] + matrix[3][3];

	if (clipCoords.w < 0.1f)
		return false;

	//perspective division, dividing by clip.W = Normalized Device Coordinates
	vec3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (windowWidth / 2 * NDC.x) + (NDC.x + windowWidth / 2);
	screen.y = -(windowHeight / 2 * NDC.y) + (NDC.y + windowHeight / 2);
	return true;
}

bool OnEntityList(int entityType)
{
	if (std::count(Hack::Data::entitiesToESP.begin(), Hack::Data::entitiesToESP.end(), entityType))
		return true;
	else
		return false;
}