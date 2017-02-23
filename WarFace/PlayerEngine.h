#ifndef __PLAYER_ENGINE__
#define __PLAYER_ENGINE__

#include "Base.h"
#include "HackEngine.h"

class PlayerEngine
{
public:
	PlayerEngine(HackEngine* owned);
	~PlayerEngine();

private:
	void InitOffsets();

	HackEngine*					m_Owned;
};

#endif