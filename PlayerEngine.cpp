#include "PlayerEngine.h"

#include "Mask.h"

using namespace std;

PlayerEngine::PlayerEngine(HackEngine* owned)
{
	m_Owned = owned;

	InitOffsets();
}

PlayerEngine::~PlayerEngine()
{

}

void PlayerEngine::InitOffsets()
{

}