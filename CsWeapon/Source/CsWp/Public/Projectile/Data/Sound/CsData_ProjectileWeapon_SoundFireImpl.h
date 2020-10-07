// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Data/Sound/CsData_ProjectileWeapon_SoundFire.h"
#include "Managers/Sound/CsTypes_Sound.h"

struct FCsInterfaceMap;

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NSound
			{
				namespace NFire
				{
					struct CSWP_API FImpl : public ICsData_ProjectileWeapon_SoundFire
					{
					public:

						static const FName Name;

					private:

						FCsInterfaceMap* InterfaceMap;

						FCsSound* Sound;

					public:

						FImpl() :
							InterfaceMap(nullptr),
							Sound(nullptr)
						{
						}
						~FImpl(){}

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

						FORCEINLINE void SetFireSound(FCsSound* Value)
						{
							Sound = Value;
						}

					// ICsData_ProjectileWeapon_SoundFire
					#pragma region
					public:

						FORCEINLINE const FCsSound& GetFireSound() const
						{
							return *Sound;
						}

					#pragma endregion ICsData_ProjectileWeapon_SoundFire
					};
				}
			}
		}
	}
}