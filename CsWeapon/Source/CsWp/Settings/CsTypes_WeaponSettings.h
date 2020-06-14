// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "CsTypes_WeaponSettings.generated.h"
#pragma once

// FCsWeaponSettings_WeaponsRowName
#pragma region

USTRUCT(BlueprintType)
struct CSWP_API FCsWeaponSettings_WeaponsRowName
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Name;

	FCsWeaponSettings_WeaponsRowName() :
		Name(NAME_None)
	{
	}
};

#pragma endregion FCsWeaponSettings_WeaponsRowName