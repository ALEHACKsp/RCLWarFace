#include "AimEngine.h"

#include "Mask.h"

using namespace std;

AimEngine::AimEngine(HackEngine* owned)
{
	m_Owned = owned;

	InitOffsets();
}

AimEngine::~AimEngine()
{

}

void AimEngine::InitOffsets()
{

}