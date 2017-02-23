#include "Base.h"
#include "Exceptions.h"
#include "GameClasses.h"
#include "MemoryTools.h"
#include "HackEngine.h"

#include <d3dx9.h>
#include <iostream>

using namespace std;

HackEngine* g_HackEngine = NULL;

Game::SSystemGlobalEnvironment* gEnv = NULL;
HINSTANCE hinstDLL = NULL;

Game::IWeaponData* lastWeaponData = NULL;
char lastRecoilData[56] = { 0 };

typedef HRESULT(WINAPI* EndScene_t)(LPDIRECT3DDEVICE9 pDevice);
EndScene_t f_EndScene;

DWORD currentFrame = 0;
DWORD lastFrame = 0;

D3DXVECTOR3 screenCenter;

bool WorldToScreen(const D3DXVECTOR3 &input, D3DXVECTOR3 &output)
{
	Game::IRenderer* Renderer = gEnv->pIRenderer;

	VecToScreen toVectot;
	toVectot.toX = input.x;
	toVectot.toY = input.y;
	toVectot.toZ = input.z;
	toVectot.outX = &output.x;
	toVectot.outY = &output.y;
	toVectot.outZ = &output.z;

	Renderer->ProjectToScreen(&toVectot);
	if(output.z < 0.0f || output.z > 1.0f)
	{
		return 0;
	}
	output.x = output.x * (Renderer->GetWidth() / 100.0f);
	output.y = output.y * (Renderer->GetHeight() / 100.0f);

	return (true);
}

D3DXVECTOR3 GetPosition(Game::IEntity* Entity)
{
	Matrix34 positionMatrix = Entity->GetWorldTM();
	return positionMatrix.GetPosition();
}

Matrix34 GetBoneOrigin(Game::IEntity* pEntity, Game::ISkeletonPose* pSkeletonPose, int boneID)
{
	Matrix34 world = pEntity->GetWorldTM();
	Matrix34 skeletonAbs = Matrix34(pSkeletonPose->GetAbsJointByID(boneID));
	return world * skeletonAbs;
}

bool isVisible(D3DXVECTOR3 start, D3DXVECTOR3 end)
{
	D3DXVECTOR3 vec = end - start;
	ray_hit RayHit;
	if(!gEnv->pIPhysicalWorld->RayWorldIntersection(start, vec, 0x101, (COLLISION_RAY_PIERCABILITY & RWI_RAY_PIERCABILITY_MASK), &RayHit, 1, 0, 0, 0, 0, "RayWorldIntersection(Game)", 0, 4))
	{
		//printf("%f %f\n", RayHit.dist, GetDistance(start, end));
		//if(RayHit.dist > (GetDistance(start, end) - 0.5f))
		return true;
	}
	return false;
}

D3DXVECTOR3 GetBoneByName(Game::IEntity* pEntity, Game::ISkeletonPose* pSkeletonPose, const char* name)
{
	int boneID = pSkeletonPose->GetJointIDByName(name);
	if(boneID > 0)
	{
		return GetBoneOrigin(pEntity, pSkeletonPose, boneID).GetPosition();;
	}
	return D3DXVECTOR3(0, 0, 0);
}

Matrix34 GetBoneOriginByName(Game::IEntity* pEntity, Game::ISkeletonPose* pSkeletonPose, const char* name)
{
	int boneID = pSkeletonPose->GetJointIDByName(name);
	if(boneID > 0)
	{
		return GetBoneOrigin(pEntity, pSkeletonPose, boneID);
	}
	return Matrix34();
}

void DrawBone(Game::IEntity* pEntity, Game::ISkeletonPose* pSkeletonPose, const char* start, const char* end, unsigned int color, float h)
{
	D3DXVECTOR3 start3D = GetBoneByName(pEntity, pSkeletonPose, start);
	D3DXVECTOR3 end3D = GetBoneByName(pEntity, pSkeletonPose, end);
	D3DXVECTOR3 start2D, end2D;
	if(start3D != D3DXVECTOR3(0, 0, 0) && end3D != D3DXVECTOR3(0, 0, 0) && WorldToScreen(start3D, start2D) && WorldToScreen(end3D, end2D))
	{
		/*char buffer[32] = { 0 };
		sprintf(buffer, "[%d]", i);
		DrawString(buffer, head2D.x, head2D.y, D3DCOLOR_ARGB(255, 255, 0, 0));
		*/
		//DrawPrimitive(start2D.x, start2D.y, end2D.x, end2D.y, h, line, color);
	}
}

bool boneScanFromHead = true;//сканить с головы
const char* boneScanNamesFromHead[] = { "Bip01 Neck", "Bip01 Spine3", "Bip01 Head", "Bip01 Spine2" };
const char* boneScanNamesFromBody[] = { "Bip01 Spine2", "Bip01 Spine3",  "Bip01 Neck", "Bip01 Head" };

void DrawPlayerSleleton(Game::IEntity* pEntity, Game::ISkeletonPose* pSkeletonPose, unsigned int color, float h)
{
	DrawBone(pEntity, pSkeletonPose, "eye_left_bone", "eye_right_bone", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Head", "eye_left_bone", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Head", "eye_right_bone", color, h);



	DrawBone(pEntity, pSkeletonPose, "Bip01 Head", "Bip01 Spine3", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L Hand", "Bip01 L Forearm", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R Hand", "Bip01 R Forearm", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L UpperArm", "Bip01 L Forearm", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R UpperArm", "Bip01 R Forearm", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L UpperArm", "Bip01 R Clavicle", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R UpperArm", "Bip01 R Clavicle", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Spine3", "Bip01 L Clavicle", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Spine3", "Bip01 R Clavicle", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Spine2", "Bip01 Spine3", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Spine2", "Bip01 Spine1", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 Spine", "Bip01 Spine1", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R Thigh", "Bip01 Spine", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L Thigh", "Bip01 Spine", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L Calf", "Bip01 L Thigh", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R Calf", "Bip01 R Thigh", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R Foot", "Bip01 R Toe0", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L Foot", "Bip01 L Toe0", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 L Foot", "Bip01 L Calf", color, h);
	DrawBone(pEntity, pSkeletonPose, "Bip01 R Foot", "Bip01 R Calf", color, h);
}

void DrawPlayerESP(Game::IEntity* pEntity, Game::IActor* pIActor, D3DXVECTOR3 topBone3D, D3DXVECTOR3 footBone3D, unsigned int color)
{
	D3DXVECTOR3 topBone2D, footBone2D;
	if(WorldToScreen(topBone3D, topBone2D) && WorldToScreen(footBone3D, footBone2D))
	{
		float height = footBone2D.y - topBone2D.y;//высота
		float width = height / 2.2f;//ширина
		//if(shared->settings.enableESP)
		//	DrawPrimitive(footBone2D.x - (width / 2), topBone2D.y, width, height, 1, box, color);

		//if(shared->settings.enableShowHP)
		{
			int armmor = pIActor->GetArmor() / pIActor->GetMaxArmor() * 100;
			int hp = pIActor->GetHealth() / pIActor->GetMaxHealth() * 100;
			//DrawPrimitive(footBone2D.x - (width / 2), footBone2D.y + 2, width, 8, (float)hp, fillbox, c_hp);
			//DrawPrimitive(footBone2D.x - (width / 2), footBone2D.y + 12, width, 8, (float)armmor, fillbox, c_armmor);
		}

	}
}

void DrawBox3D(Game::IEntity* pEntity, unsigned int color, float h)
{
	D3DXVECTOR3 Min, Max, vVec1, vVec2, vVec3, vVec4, vVec5, vVec6, vVec7, vVec8;
	AABB bBox;
	pEntity->GetWorldBounds(bBox);
	Max = bBox.max;
	Min = bBox.min;
	vVec3 = Min;
	vVec3.x = Max.x;
	vVec4 = Min;
	vVec4.y = Max.y;
	vVec5 = Min;
	vVec5.z = Max.z;
	vVec6 = Max;
	vVec6.x = Min.x;
	vVec7 = Max;
	vVec7.y = Min.y;
	vVec8 = Max;
	vVec8.z = Min.z;

	if(!WorldToScreen(Min, vVec1))
		return;
	if(!WorldToScreen(Max, vVec2))
		return;
	if(!WorldToScreen(vVec3, vVec3))
		return;
	if(!WorldToScreen(vVec4, vVec4))
		return;
	if(!WorldToScreen(vVec5, vVec5))
		return;
	if(!WorldToScreen(vVec6, vVec6))
		return;
	if(!WorldToScreen(vVec7, vVec7))
		return;
	if(!WorldToScreen(vVec8, vVec8))
		return;

	/*DrawPrimitive(vVec1.x, vVec1.y, vVec5.x, vVec5.y, h, line, color);
	DrawPrimitive(vVec2.x, vVec2.y, vVec8.x, vVec8.y, h, line, color);
	DrawPrimitive(vVec3.x, vVec3.y, vVec7.x, vVec7.y, h, line, color);
	DrawPrimitive(vVec4.x, vVec4.y, vVec6.x, vVec6.y, h, line, color);
	DrawPrimitive(vVec1.x, vVec1.y, vVec3.x, vVec3.y, h, line, color);
	DrawPrimitive(vVec1.x, vVec1.y, vVec4.x, vVec4.y, h, line, color);
	DrawPrimitive(vVec8.x, vVec8.y, vVec3.x, vVec3.y, h, line, color);
	DrawPrimitive(vVec8.x, vVec8.y, vVec4.x, vVec4.y, h, line, color);
	DrawPrimitive(vVec2.x, vVec2.y, vVec6.x, vVec6.y, h, line, color);
	DrawPrimitive(vVec2.x, vVec2.y, vVec7.x, vVec7.y, h, line, color);
	DrawPrimitive(vVec5.x, vVec5.y, vVec6.x, vVec6.y, h, line, color);
	DrawPrimitive(vVec5.x, vVec5.y, vVec7.x, vVec7.y, h, line, color);*/
}

void GetCamera(Game::IActor* localPlayer, D3DXVECTOR3 &cam)
{
	cam = D3DXVECTOR3(0, 0, 0);
	if(localPlayer && localPlayer->LinkedEntity)
	{
		Game::ICharacterInstance *pCharacterInstance = localPlayer->LinkedEntity->GetCharacter(0);
		if(!pCharacterInstance)
			return;

		Game::ISkeletonPose* pSkeletonPose = pCharacterInstance->GetISkeletonPose();
		if(!pSkeletonPose)
			return;
		cam = GetBoneByName(localPlayer->LinkedEntity, pSkeletonPose, "cameraBone");
	}
}

void AimAt(Matrix34 aimBoneOrigin, Game::IActor* localPlayer, D3DXVECTOR3 cameraPos)
{
	D3DXVECTOR3 delta = aimBoneOrigin.GetPosition() - cameraPos;
	delta.z -= 0.03f;

	VectorNormalize(&delta, &delta);

	Matrix33 aimBoneOrigin2(aimBoneOrigin);
	aimBoneOrigin2.SetRotationVDir(delta);

	Quat TargetRotation = Quat(aimBoneOrigin2);

	int aimSpeed = 15;

	D3DXVECTOR3 aimBone2D;
	if(WorldToScreen(aimBoneOrigin.GetPosition(), aimBone2D))
	{
		float distance = GetDistance2D(aimBone2D, screenCenter);
		if(distance > 250)
			aimSpeed -= 3;
		else if(distance > 50)
			aimSpeed -= 2;
		else if(distance > 20)
			aimSpeed -= 1;
	}
	else
		aimSpeed -= 4;

	float frameTime = (float)(currentFrame - lastFrame) / 1000;
	TargetRotation = Quat::CreateSlerp(localPlayer->GetViewRotation(), TargetRotation, min(frameTime * aimSpeed, 1.0f));

	localPlayer->SetViewRotation(TargetRotation);
}

EntityId lastTargetId = NULL;
void AimBot(Game::IActor* currentTarget, Game::IActor* closestTarget, Game::IActor* localPlayer, D3DXVECTOR3 &cameraPos)
{
	if((currentTarget || closestTarget) && GetAsyncKeyState(VK_LSHIFT))
	{
		if(!currentTarget && closestTarget)
		{
			currentTarget = closestTarget;
		}

		lastTargetId = currentTarget->LinkedEntity->GetRawId();

		if(currentTarget->LinkedEntity->IsHidden() || currentTarget->IsDead())
		{
			lastTargetId = NULL;
			return;
		}

		Game::ICharacterInstance *pCharacterInstance = currentTarget->LinkedEntity->GetCharacter(0);
		if(!pCharacterInstance)
		{
			lastTargetId = NULL;
			return;
		}


		Game::ISkeletonPose* pSkeletonPose = pCharacterInstance->GetISkeletonPose();
		if(!pSkeletonPose)
		{
			lastTargetId = NULL;
			return;
		}
		bool visible = false;
		Matrix34 aimBoneOrigin;
		for(int i = 0; i < 4; i++)
		{
			if(boneScanFromHead)
				aimBoneOrigin = GetBoneOriginByName(currentTarget->LinkedEntity, pSkeletonPose, boneScanNamesFromHead[i]);
			else
				aimBoneOrigin = GetBoneOriginByName(currentTarget->LinkedEntity, pSkeletonPose, boneScanNamesFromBody[i]);
			if(isVisible(cameraPos, aimBoneOrigin.GetPosition()))
			{
				visible = true;
				break;
			}
		}

		if(visible)
		{
			AimAt(aimBoneOrigin, localPlayer, cameraPos);
		}
		else
		{
			lastTargetId = NULL;
			return;
		}
	}
	else
		lastTargetId = NULL;
}

HRESULT WINAPI HookEndScene(LPDIRECT3DDEVICE9 pDevice)
{
	if(pDevice && GetAsyncKeyState(VK_F10) != NULL)
	{
		Game::IGameFramework* pGameFramework = *(Game::IGameFramework**)IGameFrameworkPtr;
		
		if(pGameFramework && gEnv->pIEntitySystem)
		{
			Game::IGameRulesSystem* pIGameRulesSystem = pGameFramework->GetIGameRulesSystem();
			Game::IEntityIt* pIEntityIterator = gEnv->pIEntitySystem->GetEntityIterator();
			Game::IActorSystem* pIactorSystem = pGameFramework->GetIActorSystem();
			if(pIEntityIterator && pIactorSystem && pIGameRulesSystem)
			{
				Game::IActor* localPlayer;
				D3DXVECTOR3 cameraPos;
				int localPlayerTeam = 0;
				bool localPlayerAlive = false;

				if(pIactorSystem->GetActorCount() > 0)
				{
					Game::IActor* localPlayer;
					if(pGameFramework->GetClientActor(&localPlayer) && localPlayer && localPlayer->LinkedEntity
					   && !localPlayer->LinkedEntity->IsHidden() && !localPlayer->IsDead())
					{
						GetCamera(localPlayer, cameraPos);

						if(Game::IGameRulesSystem* pIGameRulesSystem = pGameFramework->GetIGameRulesSystem())
							localPlayerTeam = pIGameRulesSystem->GetTeam(localPlayer->LinkedEntity->GetRawId());

						if(Game::IItem* item = localPlayer->GetCurrentItem(0))
						{
							if(Game::IWeapon* weapon = item->GetIWeapon())
							{
								if(weapon->IWeaponPtr && weapon->IWeaponPtr->weaponData)
								{
									if(lastWeaponData != weapon->IWeaponPtr->weaponData)
									{
										memcpy(lastRecoilData, weapon->IWeaponPtr->weaponData->recoilData, 56);
										lastWeaponData = weapon->IWeaponPtr->weaponData;
									}

									memcpy(weapon->IWeaponPtr->weaponData->recoilData, lastRecoilData, 56);

									weapon->IWeaponPtr->weaponData->spreadData1 = 0.0001f;
									weapon->IWeaponPtr->weaponData->spreadData2 = 0.0001f;
								}
							}
						}
					}
				}

				float closestDist = -1;
				Game::IActor* closestTarget = NULL;
				Game::IActor* currentTarget = NULL;

				do
				{
					if(Game::IEntity* pEntity = pIEntityIterator->This())
					{
						if(pEntity->IsHidden())
							continue;

						const char* entityName = pEntity->GetName();

						if(Game::IActor* pIActor = pIactorSystem->GetActor(pEntity->GetRawId()))
						{
							if(lastTargetId != NULL && pEntity->GetRawId() == lastTargetId)
								currentTarget = pIActor;

							if(pIActor->IsDead() || (localPlayer && localPlayer->EntityID == pIActor->EntityID))
								continue;

							if(pIGameRulesSystem)
								if(localPlayerTeam == pIGameRulesSystem->GetTeam(pEntity->GetRawId()) && localPlayerTeam != 0)
									continue;

							Game::ICharacterInstance *pCharacterInstance = pEntity->GetCharacter(0);
							if(!pCharacterInstance)
								continue;
							Game::ISkeletonPose* pSkeletonPose = pCharacterInstance->GetISkeletonPose();
							if(!pSkeletonPose)
								continue;

							bool visible = false;

							if(strstr(entityName, "Turret"))
							{
								//DrawBox3D(pEntity, c_target, 2);
							}
							else
							{
								for(int i = 0; i < 4; i++)
								{
									D3DXVECTOR3 visibleBone3D;
									visibleBone3D = GetBoneByName(pEntity, pSkeletonPose, boneScanNamesFromHead[i]);

									if(isVisible(cameraPos, visibleBone3D))
									{
										visible = true;
										//получаем ближайшую цель
										D3DXVECTOR3 visibleBone2D;
										if(WorldToScreen(visibleBone3D, visibleBone2D))
										{
											//получаем ближайшую цель
											float currentDist = 1000;
											currentDist = GetDistance2D(visibleBone2D, screenCenter);
											if(currentDist < closestDist || closestDist == -1)
											{
												closestTarget = pIActor;
												closestDist = currentDist;
											}
											break;
										}
									}
								}

								Matrix34 positionTM = pEntity->GetWorldTM();
								D3DXVECTOR3 position3D = positionTM.GetPosition();

								D3DXVECTOR3 topBone3D = GetBoneByName(pEntity, pSkeletonPose, "Bip01 Head") + D3DXVECTOR3(0, 0, 0.35f);
								D3DXVECTOR3 footBone3D = position3D - D3DXVECTOR3(0, 0, 0.15f);

								float distance = GetDistance3D(footBone3D, cameraPos);

								if(visible)
								{
									//DrawPlayerESP(pEntity, pIActor, topBone3D, footBone3D, c_targetvisible);
									//DrawPlayerSleleton(pEntity, pSkeletonPose, c_targetvisible, 2);
								}
								else
								{
									//DrawBox3D(pEntity, D3DCOLOR_ARGB(255, 255, 0, 0), 1);
									//DrawPlayerESP(pEntity, pIActor, topBone3D, footBone3D, c_target);
									//DrawPlayerSleleton(pEntity, pSkeletonPose, c_target, 2);
								}
							}
						}
						else
						{
							if(strstr(entityName, "ammo"))//грена
							{
								Matrix34 positionTM = pEntity->GetWorldTM();
								D3DXVECTOR3 position3D = positionTM.GetPosition();
								D3DXVECTOR3 position2D;
								if(WorldToScreen(position3D, position2D))
								{
									//DrawBox3D(pEntity, c_grenade, 2);
								}
							}
							else if(strstr(entityName, "@"))//оружка
							{
								Matrix34 positionTM = pEntity->GetWorldTM();
								D3DXVECTOR3 position3D = positionTM.GetPosition();
								D3DXVECTOR3 position2D;
								if(WorldToScreen(position3D, position2D))
								{
									//DrawBox3D(pEntity, c_weapon, 1);
								}
							}
							else if(strstr(entityName, "BombGeometry") || strstr(entityName, "ctf_case"))//бомба и кейс
							{
								Matrix34 positionTM = pEntity->GetWorldTM();
								D3DXVECTOR3 position3D = positionTM.GetPosition();
								D3DXVECTOR3 position2D;
								if(WorldToScreen(position3D, position2D))
								{
									//DrawBox3D(pEntity, c_bomb, 2);
								}
							}
						}
					}
				}
				while(pIEntityIterator->Next());
			}
			if(pIEntityIterator)
				pIEntityIterator->Release();
		}
	}
	return f_EndScene(pDevice);
}

void Console()
{
	if(AllocConsole())
	{
		freopen("CONOUT$", "w", stdout);
		HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOutput, BACKGROUND_BLUE | FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY);
		SetConsoleTitleA("RCL-Cheats.ru");
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL_, DWORD fdwReason, LPVOID lpReserved)
{
	if(fdwReason == DLL_PROCESS_ATTACH)
	{
		Console();
		hinstDLL = hinstDLL_;

		//SetHookKiUserExceptionDispatcher();

		g_HackEngine = new HackEngine();

		Game::vTable* device;
		gEnv = *(Game::SSystemGlobalEnvironment**)SSystemGlobalEnvironmentPtr;
		cout << "SSystemGlobalEnvironment " << (LPVOID)gEnv << endl;
		cout << "IGameFramework " << (LPVOID)*(DWORD*)IGameFrameworkPtr << endl;
		if(gEnv && gEnv->pIRenderer && (device = gEnv->pIRenderer->GetID3DDevice()))
		{
			f_EndScene = (EndScene_t)(*(DWORD*)device->GetFunctionPtr(42));
			*(DWORD*)device->GetFunctionPtr(42) = (DWORD)HookEndScene;
		}

		/*Game::SSystemGlobalEnvironment* env = g_HackEngine->GetSSGEnvironment();
		cout << "SSystemGlobalEnvironment " << (LPVOID)env << endl;
		Game::IRenderer* render = g_HackEngine->GetIRenderer(env);
		cout << "IRenderer " << (LPVOID)render << endl;
		if(DWORD_PTR* device = g_HackEngine->GetID3DDevice(render))
		{
			f_EndScene = (EndScene_t)device[42];
			device[42] = (DWORD)HookEndScene;
		}*/
	}
	return TRUE;
}