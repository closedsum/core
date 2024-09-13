// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsWeaponSettings.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsWeaponSettings)

#pragma region

namespace NCsWeaponSettings
{
	namespace NCached
	{
		namespace Str
		{
			CSWP_API const FString Weapon = TEXT("UCsWeaponSettings.ECsWeapon");
			CSWP_API const FString WeaponClass = TEXT("UCsWeaponSettings.ECsWeaponClass");
			CSWP_API const FString WeaponState = TEXT("UCsWeaponSettings.ECsWeaponState");
		}
	}
}

#pragma endregion Cached


UCsWeaponSettings::UCsWeaponSettings(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}