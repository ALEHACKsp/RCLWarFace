#ifndef __HACK_ENGINE__
#define __HACK_ENGINE__

#include "Base.h"
#include "GameClasses.h"
#include "GameOffset.h"
#include "GamePointer.h"
#include "GameFunction.h"

class AimEngine;
class PlayerEngine;
class WeaponEngine;

class HackEngine
{
public:
	HackEngine();
	~HackEngine();

	Game::SSystemGlobalEnvironment* GetSSGEnvironment();
	Game::IRenderer* GetIRenderer(Game::SSystemGlobalEnvironment* env);
	DWORD_PTR* GetID3DDevice(Game::IRenderer* render);
	Game::IPhysicalWorld* GetIPhysicalWorld(Game::SSystemGlobalEnvironment* env);
	Game::IEntitySystem* GetIEntitySystem(Game::SSystemGlobalEnvironment* env);
	Game::IEntityIt* GetEntityIterator(Game::IEntitySystem* entity_system);

	Game::IGameFramework* GetIGameFramework();
	Game::IGameRulesSystem* GetIGameRulesSystem(Game::IGameFramework* framework);
	Game::IActorSystem* GetIActorSystem(Game::IGameFramework* framework);

	void Draw();

private:
	void InitOffsets();

	AimEngine*					m_AimEngine;
	PlayerEngine*				m_PlayerEngine;
	WeaponEngine*				m_WeaponEngine;

	GamePointer					m_SSGEnvironment;
	GamePointer					m_IGameFramework;
	GameOffset					m_IRenderer;
	GameOffset					m_ID3DDevice;
	GameOffset					m_IPhysicalWorld;
	GameOffset					m_IEntitySystem;
	GameFunction				m_GetEntityIterator;
	GameFunction				m_RayWorldIntersection;
};

#endif