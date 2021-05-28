// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Data/CsData_ProjectileWeapon.h"

struct FCsInterfaceMap;

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
CS_FWD_DECLARE_STRUCT_NAMESPACE_4(NCsWeapon, NProjectile, NParams, NLaunch, ILaunch)

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			/**
			*/

			/**
			* Represents a "slice" of data, PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData).
			*
			* If members are set via points to an "owning" data, then
			* "Emulates" PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData) by mimicking
			* the interfaces and having pointers to the appropriate members.
			*
			* The idea behind this struct is to "build" the data via composition of separate objects that each implementation
			* a specific interface. The whole data will be constructed elsewhere in native (usually a manager).
			*/
			struct CSWP_API FImplSlice : public IData
			{
			public:

				static const FName Name;

			private:

				// ICsGetInterfaceMap

				/** Pointer to the "root" object for all "Emu Slices". That object acts as the hub for the separate objects (via composition)
					that describe the data. */
				FCsInterfaceMap* InterfaceMap;

				// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)

				bool bDoFireOnRelease;
				bool* bDoFireOnRelease_Emu;

				bool bFullAuto;
				bool* bFullAuto_Emu;

				bool bInfiniteAmmo;
				bool* bInfiniteAmmo_Emu;

				int32 MaxAmmo;
				int32* MaxAmmo_Emu;

				int32 ProjectilesPerShot;
				int32* ProjectilesPerShot_Emu;

				float TimeBetweenShots;
				float* TimeBetweenShots_Emu;

				float TimeBetweenAutoShots;
				float* TimeBetweenAutoShots_Emu;

				float TimeBetweenProjectilesPerShot;
				float* TimeBetweenProjectilesPerShot_Emu;

				typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;

			public:

				FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
					bDoFireOnRelease(false),
					bDoFireOnRelease_Emu(nullptr),
					bFullAuto(false),
					bFullAuto_Emu(nullptr),
					bInfiniteAmmo(false),
					bInfiniteAmmo_Emu(nullptr),
					MaxAmmo(0),
					MaxAmmo_Emu(nullptr),
					ProjectilesPerShot(0),
					ProjectilesPerShot_Emu(nullptr),
					TimeBetweenShots(0.0f),
					TimeBetweenShots_Emu(nullptr),
					TimeBetweenAutoShots(0.0f),
					TimeBetweenAutoShots_Emu(nullptr),
					TimeBetweenProjectilesPerShot(0.0f),
					TimeBetweenProjectilesPerShot_Emu(nullptr)
				{
				}

				~FImplSlice()
				{
				}

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			public:

				FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map) { InterfaceMap = Map; }

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const { return InterfaceMap; }

			#pragma endregion ICsGetInterfaceMap

			// PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)
			#pragma region
			public:

				FORCEINLINE void SetDoFireOnRelease(const bool& Value) \
				{
					bDoFireOnRelease = Value;
					bDoFireOnRelease_Emu = &bDoFireOnRelease;
				}
				FORCEINLINE void SetDoFireOnRelease(bool* Value) { check(Value); bDoFireOnRelease_Emu = Value; }
				FORCEINLINE const bool& DoFireOnRelease() const { return *bDoFireOnRelease_Emu; }

				FORCEINLINE void SetFullAuto(const bool& Value) \
				{
					bFullAuto = Value;
					bFullAuto_Emu = &bFullAuto;
				}
				FORCEINLINE void SetFullAuto(bool* Value) { check(Value); bFullAuto_Emu = Value; }
				FORCEINLINE const bool& IsFullAuto() const { return *bFullAuto_Emu; }

				FORCEINLINE void SetInfiniteAmmo(const bool& Value) \
				{
					bInfiniteAmmo = Value;
					bInfiniteAmmo_Emu = &bInfiniteAmmo;
				}
				FORCEINLINE void SetInfiniteAmmo(bool* Value) { check(Value); bInfiniteAmmo_Emu = Value; }
				FORCEINLINE const bool& HasInfiniteAmmo() const { return *bInfiniteAmmo_Emu; }

				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(MaxAmmo, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(ProjectilesPerShot, int32)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenShots, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenAutoShots, float)
				CS_DEFINE_SET_GET_MEMBER_WITH_EMU(TimeBetweenProjectilesPerShot, float)

				FORCEINLINE const LaunchParamsType* GetLaunchParams() const
				{
					return nullptr;
				}

			#pragma endregion PrjWeaponDataType (NCsWeapon::NProjectile::NData::IData)

			public:

				static void Deconstruct(void* Ptr)
				{
					delete static_cast<NCsWeapon::NProjectile::NData::FImplSlice*>(Ptr);
				}
			};
		}
	}
}