#include "StatFreeze.h"

void Hack::StatFreeze::Freeze()
{
	if (*Hack::Data::localPlayer)
	{
		if (Hack::Data::bHealthFreeze)
		{
			*Hack::Data::playerHealth = 1337;
		}

		if (Hack::Data::bArmorFreeze)
		{
			*Hack::Data::playerArmor = 1337;
		}

		if (Hack::Data::bAuxPowerFreeze)
		{
			*(float*)Hack::Data::playerAuxPower = 100;
		}
	}
}
