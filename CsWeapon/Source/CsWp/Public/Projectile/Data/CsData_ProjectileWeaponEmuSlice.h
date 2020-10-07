// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Data/CsData_ProjectileWeapon.h"

struct FCsInterfaceMap;

// NCsWeapon::NProjectile::NParams::NLaunch::ILaunch
namespace NCsWeapon {
	namespace NProjectile {
		namespace NParams {
			namespace NLaunch {
				struct ILaunch;
			}
		}
	}
}

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{

			/**
			*/
			struct CSWP_API FEmuSlice : public IData
			{
			public:

				static const FName Name;

			private:

				FCsInterfaceMap* InterfaceMap;

				bool* bDoFireOnRelease;

				bool* bFullAuto;

				bool* bInfiniteAmmo;

				int32* MaxAmmo;

				int32* ProjectilesPerShot;

				float* TimeBetweenShots;

				float* TimeBetweenAutoShots;

				float* TimeBetweenProjectilesPerShot;

				typedef NCsWeapon::NProjectile::NParams::NLaunch::ILaunch LaunchParamsType;

			public:

				FEmuSlice() :
					InterfaceMap(nullptr),
					bDoFireOnRelease(nullptr),
					bFullAuto(nullptr),
					bInfiniteAmmo(nullptr),
					MaxAmmo(nullptr),
					ProjectilesPerShot(nullptr),
					TimeBetweenShots(nullptr),
					TimeBetweenAutoShots(nullptr),
					TimeBetweenProjectilesPerShot(nullptr)
				{
				}

				~FEmuSlice()
				{
				}

				FORCEINLINE UObject* _getUObject() const { return nullptr; }

			public:

				FORCEINLINE void SetInterfaceMap(FCsInterfaceMap* Map)
				{
					InterfaceMap = Map;
				}

			// ICsGetInterfaceMap
			#pragma region
			public:

				FORCEINLINE FCsInterfaceMap* GetInterfaceMap() const
				{
					return InterfaceMap;
				}

			#pragma endregion ICsGetInterfaceMap

			public:

				FORCEINLINE void SetDoFireOnRelease(bool* Value)
				{
					bDoFireOnRelease = Value;
				}

				FORCEINLINE void SetFullAuto(bool* Value)
				{
					bFullAuto = Value;
				}

				FORCEINLINE void SetInfiniteAmmo(bool* Value)
				{
					bInfiniteAmmo = Value;
				}

				FORCEINLINE void SetMaxAmmo(int32* Value)
				{
					MaxAmmo = Value;
				}

				FORCEINLINE void SetProjectilesPerShot(int32* Value)
				{
					ProjectilesPerShot = Value;
				}

				FORCEINLINE void SetTimeBetweenShots(float* Value)
				{
					TimeBetweenShots = Value;
				}

				FORCEINLINE void SetTimeBetweenAutoShots(float* Value)
				{
					TimeBetweenAutoShots = Value;
				}

				FORCEINLINE void SetTimeBetweenProjectilesPerShot(float* Value)
				{
					TimeBetweenProjectilesPerShot = Value;
				}

			// ICsData_ProjectileWeapon
			#pragma region
			public:

				FORCEINLINE const bool& DoFireOnRelease() const
				{
					return *bDoFireOnRelease;
				}

				FORCEINLINE const bool& IsFullAuto() const
				{
					return *bFullAuto;
				}

				FORCEINLINE const bool& HasInfiniteAmmo() const
				{
					return *bInfiniteAmmo;
				}

				FORCEINLINE const int32& GetMaxAmmo() const
				{
					return *MaxAmmo;
				}

				FORCEINLINE const int32& GetProjectilesPerShot() const
				{
					return *ProjectilesPerShot;
				}

				FORCEINLINE const float& GetTimeBetweenShots() const
				{
					return *TimeBetweenShots;
				}

				FORCEINLINE const float& GetTimeBetweenAutoShots() const
				{
					return *TimeBetweenAutoShots;
				}

				FORCEINLINE const float& GetTimeBetweenProjectilesPerShot() const
				{
					return *TimeBetweenProjectilesPerShot;
				}

				FORCEINLINE const LaunchParamsType* GetLaunchParams() const
				{
					return nullptr;
				}

			#pragma endregion ICsData_ProjectileWeapon
			};
		}
	}
}