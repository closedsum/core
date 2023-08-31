// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Settings/CsWeaponSettings.h"
#include "CsWp.h"

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