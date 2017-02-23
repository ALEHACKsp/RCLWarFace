#ifndef __WEAPON_ENGINE__
#define __WEAPON_ENGINE__

#include "Base.h"
#include "HackEngine.h"

class WeaponEngine
{
public:
	WeaponEngine(HackEngine* owned);
	~WeaponEngine();

private:
	void InitOffsets();

	HackEngine*					m_Owned;

	GameOffset					m_IWeaponPtr;
	GameOffset					m_IWeaponData;
};

#endif