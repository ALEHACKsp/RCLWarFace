#include "HackEngine.h"

#include "Mask.h"
#include "AimEngine.h"
#include "PlayerEngine.h"
#include "WeaponEngine.h"

using namespace std;

HackEngine::HackEngine()
{
	InitOffsets();

	m_AimEngine = new AimEngine(this);
	m_PlayerEngine = new PlayerEngine(this);
	m_WeaponEngine = new WeaponEngine(this);
}

HackEngine::~HackEngine()
{

}

Game::SSystemGlobalEnvironment* HackEngine::GetSSGEnvironment()
{
	return (Game::SSystemGlobalEnvironment*)m_SSGEnvironment.GetValue();
}

Game::IRenderer* HackEngine::GetIRenderer(Game::SSystemGlobalEnvironment* env)
{
	if(!env || !m_IRenderer)
		return NULL;
	return *(Game::IRenderer**)((char*)env + m_IRenderer.GetOffset());
}

DWORD_PTR* HackEngine::GetID3DDevice(Game::IRenderer* render)
{
	if(!render || !m_ID3DDevice)
		return NULL;
	return *(DWORD_PTR**)((char*)render + m_ID3DDevice.GetOffset());
}

Game::IPhysicalWorld* HackEngine::GetIPhysicalWorld(Game::SSystemGlobalEnvironment* env)
{
	if(!env || !m_IPhysicalWorld)
		return NULL;
	return *(Game::IPhysicalWorld**)((char*)env + m_IPhysicalWorld.GetOffset());
}

Game::IEntitySystem* HackEngine::GetIEntitySystem(Game::SSystemGlobalEnvironment* env)
{
	if(!env || !m_IEntitySystem)
		return NULL;
	return *(Game::IEntitySystem**)((char*)env + m_IEntitySystem.GetOffset());
}

Game::IEntityIt* HackEngine::GetEntityIterator(Game::IEntitySystem* entity_system)
{
	typedef Game::IEntityIt*(__thiscall* GetEntityIterator_t)(Game::IEntitySystem*);
	GetEntityIterator_t f_GetEntityIterator = (GetEntityIterator_t)m_GetEntityIterator.GetAddress();
	if(!entity_system || !f_GetEntityIterator)
		return NULL;
	return f_GetEntityIterator(entity_system);
}

Game::IGameFramework* HackEngine::GetIGameFramework()
{
	return (Game::IGameFramework*)m_IGameFramework.GetAddress();
}

Game::IGameRulesSystem* HackEngine::GetIGameRulesSystem(Game::IGameFramework* framework)
{
	if(!framework)
		return NULL;
	return framework->GetIGameRulesSystem();
}

Game::IActorSystem* HackEngine::GetIActorSystem(Game::IGameFramework* framework)
{
	if(!framework)
		return NULL;
	return framework->GetIActorSystem();
}

void HackEngine::Draw()
{

}

void HackEngine::InitOffsets()
{
	m_SSGEnvironment = GamePointer(g_SSGEnvironment_Byte, g_SSGEnvironment_Len, g_SSGEnvironment_Mask, g_SSGEnvironment_Offset);
	m_IGameFramework = GamePointer(g_IGameFramework_Byte, g_IGameFramework_Len, g_IGameFramework_Mask, g_IGameFramework_Offset);
	m_IRenderer = GameOffset(g_IRenderer_Byte, g_IRenderer_Len, g_IRenderer_Mask, g_IRenderer_Offset);
	m_ID3DDevice = GameOffset(g_ID3DDevice_Byte, g_ID3DDevice_Len, g_ID3DDevice_Mask, g_ID3DDevice_Offset);
	m_IPhysicalWorld = GameOffset(g_IPhysicalWorld_Byte, g_IPhysicalWorld_Len, g_IPhysicalWorld_Mask, g_IPhysicalWorld_Offset);
	m_IEntitySystem = GameOffset(g_IEntitySystem_Byte, g_IEntitySystem_Len, g_IEntitySystem_Mask, g_IEntitySystem_Offset);
	m_GetEntityIterator = GameFunction(g_GetEntityIterator_Byte, g_GetEntityIterator_Len, g_GetEntityIterator_Mask);
	m_RayWorldIntersection = GameFunction(g_RayWorldIntersection_Byte, g_RayWorldIntersection_Len, g_RayWorldIntersection_Mask);

#if TEST_BUILD || defined(_DEBUG)
	cout << "m_SSGEnvironment = " << (LPVOID)m_SSGEnvironment.GetAddress() << " " << (LPVOID)m_SSGEnvironment.GetValue() << endl;
	cout << "m_IGameFramework = " << (LPVOID)m_IGameFramework.GetAddress() << " " << (LPVOID)m_IGameFramework.GetValue() << endl;
	cout << "m_IRenderer = " << (LPVOID)m_IRenderer.GetAddress() << " " << (LPVOID)m_IRenderer.GetOffset() << endl;
	cout << "m_ID3DDevice = " << (LPVOID)m_ID3DDevice.GetAddress() << " " << (LPVOID)m_ID3DDevice.GetOffset() << endl;
	cout << "m_IPhysicalWorld = " << (LPVOID)m_IPhysicalWorld.GetAddress() << " " << (LPVOID)m_IPhysicalWorld.GetOffset() << endl;
	cout << "m_IEntitySystem = " << (LPVOID)m_IEntitySystem.GetAddress() << " " << (LPVOID)m_IEntitySystem.GetOffset() << endl;
	cout << "m_GetEntityIterator = " << (LPVOID)m_GetEntityIterator.GetAddress() << endl;
	cout << "m_RayWorldIntersection = " << (LPVOID)m_RayWorldIntersection.GetAddress() << endl;
#endif
	
}