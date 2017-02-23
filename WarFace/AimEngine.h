#ifndef __AIM_ENGINE__
#define __AIM_ENGINE__

#include "Base.h"
#include "HackEngine.h"

class AimEngine
{
public:
	AimEngine(HackEngine* owned);
	~AimEngine();

private:
	void InitOffsets();

	HackEngine*					m_Owned;
};

#endif
