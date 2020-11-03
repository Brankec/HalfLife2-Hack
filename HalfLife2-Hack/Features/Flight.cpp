#include "Flight.h"

float DegreeToRadian(float degrees);

void Hack::Flight::Fly()
{
	if (Hack::Data::bGravity && !Hack::Data::bFlyMode)
	{
		*(float*)Hack::Data::gravity = 600.f;
		Hack::Data::bGravity = false;
	}

	if (*Hack::Data::localPlayer && Hack::Data::bFlyMode)
	{
		Hack::Data::bGravity = true;
		vec3 d;
		d.x = *(float*)Hack::Data::xPlayerPosition;
		d.z = *(float*)Hack::Data::zPlayerPosition;
		d.y = *(float*)Hack::Data::yPlayerPosition;

		if (GetAsyncKeyState(0x57))
		{
			d.x += cos(DegreeToRadian(*(float*)Hack::Data::xCameraAxis)) * Hack::Data::flightSpeed;
			d.z += sin(DegreeToRadian(*(float*)Hack::Data::xCameraAxis)) * Hack::Data::flightSpeed;
		}
		else if (GetAsyncKeyState(0x53))
		{
			d.x -= cos(DegreeToRadian(*(float*)Hack::Data::xCameraAxis)) * Hack::Data::flightSpeed;
			d.z -= sin(DegreeToRadian(*(float*)Hack::Data::xCameraAxis)) * Hack::Data::flightSpeed;
		}

		//vertical flight
		if (GetAsyncKeyState(VK_SPACE))
		{
			d.y += Hack::Data::flightSpeed;
		}
		if (GetAsyncKeyState(VK_SHIFT))
		{
			d.y -= Hack::Data::flightSpeed;
		}

		*(float*)Hack::Data::xPlayerPosition = d.x;
		*(float*)Hack::Data::zPlayerPosition = d.z;
		*(float*)Hack::Data::yPlayerPosition = d.y;

		if (*Hack::Data::localPlayer)
		{
			//resets gravity and movement velocity when in fly mode to avoid gliding and jittering
			*Hack::Data::xPlayerVelocity = 0;
			*Hack::Data::zPlayerVelocity = 0;
			*Hack::Data::yPlayerVelocity = 0;
			*(float*)Hack::Data::gravity = 1.f;
		}
	}
}

float DegreeToRadian(float degrees)
{
	return degrees * (3.1415927f / 180);
}
