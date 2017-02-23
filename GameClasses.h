// Generated using ReClass 2016

#pragma once

#include "Base.h"
#include "Math.h"

#define SSystemGlobalEnvironmentPtr 0x1863B78

#define IGameFrameworkPtr 0x187A404

namespace Game
{

	class SSystemGlobalEnvironment;
	class IEntitySystem;
	class IEntityIt;
	class IPhysicalWorld;
	class IRenderer;
	class vTable;
	class IGameFramework;
	class IActorSystem;
	class IGameRulesSystem;
	class ICharacterInstance;
	class IEntity;
	class ISkeletonPose;
	class IPhysicalEntity;
	class IActor;
	class N00000614;
	class IGameObject;
	class IItem;
	class IWeapon;
	class IFireMode;
	class IWeaponPTR;
	class IWeaponData;

	class SSystemGlobalEnvironment
	{
	public:
		char pad_0x0000[0x88]; //0x0000
		IRenderer* pIRenderer; //0x0088 from below cl_DisableHUDText  
		char pad_0x008C[0xC]; //0x008C
		IPhysicalWorld* pIPhysicalWorld; //0x0098 
		char pad_0x009C[0x14]; //0x009C
		IEntitySystem* pIEntitySystem; //0x00B0 
		char pad_0x00B4[0x4C]; //0x00B4


	}; //Size=0x0100

	class IEntitySystem
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual IEntityIt* GetEntityIterator(); //56 6A 04 6A 10 8B F1

		char pad_0x0004[0x1000]; //0x0004

	}; //Size=0x1004

	class IEntityIt
	{
	public:
		virtual void AddRef(); //
		virtual void Function(); //
		virtual void Release(); //
		virtual void MoveFirst(); //
		virtual IEntity* This(); //
		virtual IEntity* Next(); //
		virtual bool IsEnd(); //

	}; //Size=0x0004

	class IPhysicalWorld
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual void Function61(); //
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual void Function65(); //
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //
		virtual void Function75(); //
		virtual void Function76(); //
		virtual void Function77(); //
		virtual void Function78(); //
		virtual void Function79(); //
		virtual void Function80(); //
		virtual void Function81(); //
		virtual void Function82(); //
		virtual void Function83(); //
		virtual void Function84(); //
		virtual void Function85(); //
		virtual void Function86(); //
		virtual void Function87(); //
		virtual void Function88(); //
		virtual void Function89(); //
		virtual void Function90(); //
		virtual void Function91(); //we find on line RayWorldIntersection(3dEngine) 
		virtual int RayWorldIntersection(const D3DXVECTOR3& Start, const D3DXVECTOR3& End, int objTypes, unsigned int traceFlags, ray_hit *hits, int nMaxHits, IPhysicalEntity **pSkipEnts, int nSkipEnts, void *pForeignData, int iForeignData, const char *pNameTag, ray_hit_cached *phitLast, int iCaller); //

	}; //Size=0x0004

	class IRenderer
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual void Function61(); //
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual void Function65(); //
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //
		virtual void Function75(); //
		virtual void Function76(); //
		virtual void Function77(); //
		virtual void Function78(); //
		virtual void Function79(); //
		virtual void Function80(); //
		virtual void Function81(); //
		virtual void Function82(); //
		virtual void Function83(); //
		virtual int GetWidth(); //function can be found in 8B C8 8B C6 99 2B C2 D1 F8  
		virtual int GetHeight(); //
		virtual void Function86(); //
		virtual void Function87(); //
		virtual void Function88(); //
		virtual void Function89(); //
		virtual bool ProjectToScreen(VecToScreen* pVecToScreen); //

		char pad_0x0004[0x4]; //0x0004

		vTable* GetID3DDevice()

		{

			//D3DXCreateTexture game imports

			//j_D3DXCreateTexture(*(_DWORD *)(IRenderer + 0x854C), a3, a4, a8, 0, v12, 2,  v35) 0) )

			return (vTable*)((DWORD)this + 0x8550);

		}
	}; //Size=0x0008

	class vTable
	{
	public:
		DWORD vtable; //0x0000 
		char pad_0x0004[0x3C]; //0x0004

		DWORD GetFunctionPtr(int iIndex)
		{
			DWORD dwTable = *(PDWORD)vtable;
			if(dwTable == NULL)
				return NULL;
			return dwTable + (0x4 * iIndex);
		}
	}; //Size=0x0040

	class IGameFramework
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual IActorSystem* GetIActorSystem(); //8B 81 B0 04 00 00 C3
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual bool GetClientActor(IActor** pActor); //8B 41 24 85 C0 74 05 8B 40 08 jump
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual IGameRulesSystem* GetIGameRulesSystem(); //there is not convinced of the correctness

		char pad_0x0004[0xBC]; //0x0004

	}; //Size=0x00C0

	class IActorSystem
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual int GetActorCount(); //
		virtual void Function14(); //
		virtual IActor *GetActor(EntityId ActorId); // 51 56 8D 71 ?? 8D 44 ?? ?? 50 8D 4C ?? ?? 51 8B CE second 

	}; //Size=0x0004

	class IGameRulesSystem
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual void Function61(); //
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual void Function65(); //
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //
		virtual void Function75(); //
		virtual void Function76(); //
		virtual void Function77(); //
		virtual void Function78(); //
		virtual void Function79(); //
		virtual void Function80(); //
		virtual void Function81(); //
		virtual void Function82(); //
		virtual void Function83(); //
		virtual void Function84(); //
		virtual void Function85(); //
		virtual void Function86(); //
		virtual void Function87(); //
		virtual void Function88(); //
		virtual void Function89(); //
		virtual void Function90(); //
		virtual void Function91(); //
		virtual void Function92(); //
		virtual void Function93(); //
		virtual void Function94(); //
		virtual void Function95(); //
		virtual void Function96(); //
		virtual void Function97(); //
		virtual void Function98(); //
		virtual void Function99(); //
		virtual void Function100(); //
		virtual void Function101(); //
		virtual void Function102(); //
		virtual void Function103(); //
		virtual void Function104(); //
		virtual void Function105(); //
		virtual void Function106(); //
		virtual void Function107(); //
		virtual void Function108(); //
		virtual int GetTeam(EntityId entityId); //http://prntscr.com/a2jujs GetTeam

		char pad_0x0004[0x3C]; //0x0004

	}; //Size=0x0040

	class ICharacterInstance
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual void Function61(); //
		virtual void Function62(); //
		virtual ISkeletonPose* GetISkeletonPose(); //GetBoneLocal http://prntscr.com/a96l3i

		char pad_0x0004[0x3C]; //0x0004

	}; //Size=0x0040

	class IEntity
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual const char* GetName(); //GetName http://prntscr.com/a956hy
		virtual void Function22(); //
		virtual void Function23(); //
		virtual EntityId GetRawId(); //GetRawId http://prntscr.com/a94yog
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual ICharacterInstance* GetCharacter(int Slot = 0); //GetCharacter http://prntscr.com/a94t2u possibly deleted Slot
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual int SetLocalPos(const D3DXVECTOR3 &vPos, int flag = 10); // SetLocalPos http://prntscr.com/a955v2 possibly deleted flag
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual bool IsHidden(); //8B 41 ?? C1 E8 04 83 E0 01 C3
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //
		virtual void Function75(); //
		virtual void Function76(); //
		virtual void Function77(); //
		virtual void Function78(); //
		virtual void Function79(); //
		virtual void Function80(); //
		virtual const Matrix34& GetWorldTM(); //GetProjectedWorldBBox http://prntscr.com/a94un9
		virtual void Function82(); //
		virtual void Function83(); //
		virtual void Function84(); //
		virtual void GetWorldBounds(AABB &BoundBox); //GetWorldBoundsCenter http://prntscr.com/a94vn5
		virtual void Function86(); //
		virtual void Function87(); //
		virtual void Function88(); //
		virtual void Function89(); //
		virtual void Function90(); //
		virtual void Function91(); //
		virtual void Function92(); //
		virtual void Function93(); //
		virtual void Function94(); //
		virtual void Function95(); //
		virtual void Function96(); //
		virtual void Function97(); //
		virtual void Function98(); //
		virtual void Function99(); //
		virtual void Function100(); //
		virtual void Function101(); //
		virtual void Function102(); //
		virtual void Function103(); //
		virtual void Function104(); //
		virtual int GetFlags(); //on_activate.unlock_achievement http://prntscr.com/eb3li2
		virtual void Function106(); //
		virtual void Function107(); //
		virtual void Function108(); //
		virtual void Function109(); //
		virtual void Function110(); //
		virtual void Function111(); //
		virtual void Function112(); //
		virtual void Function113(); //
		virtual void Function114(); //
		virtual void Function115(); //
		virtual void Function116(); //
		virtual void Function117(); //
		virtual void Function118(); //
		virtual void Function119(); //
		virtual void Function120(); //
		virtual void Function121(); //
		virtual void Function122(); //
		virtual void Function123(); //
		virtual void Function124(); //
		virtual void Function125(); //
		virtual void Function126(); //
		virtual void Function127(); //
		virtual void Function128(); //
		virtual void Function129(); //
		virtual void Function130(); //
		virtual void Function131(); //
		virtual void Function132(); //
		virtual void Function133(); //
		virtual void Function134(); //
		virtual void Function135(); //
		virtual void Function136(); //
		virtual void Function137(); //
		virtual void Function138(); //
		virtual void Function139(); //
		virtual void Function140(); //
		virtual void Function141(); //
		virtual void Function142(); //
		virtual void Function143(); //
		virtual void Function144(); //
		virtual void Function145(); //
		virtual void Function146(); //
		virtual void Function147(); //
		virtual void Function148(); //
		virtual void Function149(); //
		virtual void Function150(); //
		virtual void Function151(); //
		virtual void Function152(); //
		virtual void Function153(); //
		virtual void Function154(); //
		virtual void Function155(); //

	}; //Size=0x0004

	class ISkeletonPose
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual __int16 GetJointIDByName(const char* szJointName); //GetBoneDir http://prntscr.com/a96qxj
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual const QuatT& GetAbsJointByID(__int32 nJointID); //GetBonePos http://prntscr.com/a96nyz
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual char* GetJointNameByID(__int32 nJointID); //GetBoneNameFromTable http://prntscr.com/a96mb2

		char pad_0x0004[0x3C]; //0x0004

	}; //Size=0x0040

	class IPhysicalEntity
	{
	public:
		char pad_0x0000[0x40]; //0x0000

	}; //Size=0x0040

	class IActor
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual bool IsDead(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual int GetHealth(); //http://prntscr.com/a96a60
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual int GetMaxHealth(); //
		virtual int GetArmor(); //
		virtual int GetMaxArmor(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void SetViewRotation(const Quat &rotation); //
		virtual Quat GetViewRotation(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual IItem* GetCurrentItem(int arg); //

		char pad_0x0004[0x4]; //0x0004
		IEntity* LinkedEntity; //0x0008 
		IGameObject* GameObject; //0x000C 
		EntityId EntityID; //0x0010 
		char pad_0x0014[0x2C]; //0x0014

	}; //Size=0x0040

	class N00000614
	{
	public:
		char pad_0x0000[0x4]; //0x0000

	}; //Size=0x0004

	class IGameObject
	{
	public:
		char pad_0x0000[0x4]; //0x0000

	}; //Size=0x0004

	class IItem
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual void Function29(); //
		virtual void Function30(); //
		virtual void Function31(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //
		virtual void Function42(); //
		virtual void Function43(); //
		virtual void Function44(); //
		virtual void Function45(); //
		virtual void Function46(); //
		virtual void Function47(); //
		virtual void Function48(); //
		virtual void Function49(); //
		virtual void Function50(); //
		virtual void Function51(); //
		virtual void Function52(); //
		virtual void Function53(); //
		virtual void Function54(); //
		virtual void Function55(); //
		virtual void Function56(); //
		virtual void Function57(); //
		virtual void Function58(); //
		virtual void Function59(); //
		virtual void Function60(); //
		virtual void Function61(); //
		virtual void Function62(); //
		virtual void Function63(); //
		virtual void Function64(); //
		virtual void Function65(); //
		virtual void Function66(); //
		virtual void Function67(); //
		virtual void Function68(); //
		virtual void Function69(); //
		virtual void Function70(); //
		virtual void Function71(); //
		virtual void Function72(); //
		virtual void Function73(); //
		virtual void Function74(); //
		virtual void Function75(); //
		virtual void Function76(); //
		virtual void Function77(); //
		virtual void Function78(); //
		virtual IWeapon* GetIWeapon(); //
		virtual void Function80(); //
		virtual void Function81(); //
		virtual void Function82(); //
		virtual void Function83(); //
		virtual void Function84(); //
		virtual void Function85(); //
		virtual void Function86(); //
		virtual void Function87(); //
		virtual void Function88(); //
		virtual void Function89(); //

		char pad_0x0004[0x3C]; //0x0004

	}; //Size=0x0040

	class IWeapon
	{
	public:
		virtual void Function0(); //
		virtual void Function1(); //
		virtual void Function2(); //
		virtual void Function3(); //
		virtual void Function4(); //
		virtual void Function5(); //
		virtual void Function6(); //
		virtual void Function7(); //
		virtual void Function8(); //
		virtual void Function9(); //
		virtual void Function10(); //
		virtual void Function11(); //
		virtual void Function12(); //
		virtual void Function13(); //
		virtual void Function14(); //
		virtual void Function15(); //
		virtual void Function16(); //
		virtual void Function17(); //
		virtual void Function18(); //
		virtual void Function19(); //
		virtual void Function20(); //
		virtual void Function21(); //
		virtual void Function22(); //
		virtual void Function23(); //
		virtual void Function24(); //
		virtual void Function25(); //
		virtual void Function26(); //
		virtual void Function27(); //
		virtual void Function28(); //
		virtual IFireMode* GetFireMode(int FireModeId); //
		virtual void Function30(); //
		virtual int GetRequestedFireMode(); //
		virtual void Function32(); //
		virtual void Function33(); //
		virtual void Function34(); //
		virtual void Function35(); //
		virtual void Function36(); //
		virtual void Function37(); //
		virtual void Function38(); //
		virtual void Function39(); //
		virtual void Function40(); //
		virtual void Function41(); //

		char pad_0x0004[0x4]; //0x0004
		IWeaponPTR* IWeaponPtr; //0x0008 
		char pad_0x000C[0x34]; //0x000C

	}; //Size=0x0040

	class IFireMode
	{
	public:
		char pad_0x0000[0x40]; //0x0000

	}; //Size=0x0040

	class IWeaponPTR
	{
	public:
		char pad_0x0000[0x2C]; //0x0000
		IWeaponData* weaponData; //0x002C 

	}; //Size=0x0030

	class IWeaponData
	{
	public:
		float spreadData1; //0x0000 
		float spreadData2; //0x0004 
		char pad_0x0008[0x1C]; //0x0008
		char recoilData[56]; //0xC84888 

	}; //Size=0x005C

}
