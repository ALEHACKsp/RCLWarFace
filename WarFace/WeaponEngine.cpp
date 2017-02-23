#include "WeaponEngine.h"

#include "Mask.h"

using namespace std;

WeaponEngine::WeaponEngine(HackEngine* owned)
{
	m_Owned = owned;

	InitOffsets();
}

WeaponEngine::~WeaponEngine()
{

}

void WeaponEngine::InitOffsets()
{
	m_IWeaponPtr = GameOffset(g_IWeaponPtr_Byte, g_IWeaponPtr_Len, g_IWeaponPtr_Mask, g_IWeaponPtr_Offset, GameOffset::OFFSET_BYTE);
	m_IWeaponData = GameOffset(g_IWeaponData_Byte, g_IWeaponData_Len, g_IWeaponData_Mask, g_IWeaponData_Offset, GameOffset::OFFSET_BYTE);

#if TEST_BUILD || defined(_DEBUG)
	cout << "m_IWeaponPtr = " << (LPVOID)m_IWeaponPtr.GetAddress() << " " << (LPVOID)m_IWeaponPtr.GetOffset() << endl;
	cout << "m_IWeaponData = " << (LPVOID)m_IWeaponData.GetAddress() << " " << (LPVOID)m_IWeaponData.GetOffset() << endl;
#endif
}