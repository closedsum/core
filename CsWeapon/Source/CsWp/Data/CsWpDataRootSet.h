// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Settings/CsTypes_WeaponSettings.h"

#include "CsWpDataRootSet.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct CSWP_API FCsWpDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> WeaponClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCsWeaponSettings_DataTable_Weapons> Weapons;

	FCsWpDataRootSet() :
		WeaponClasses(),
		Weapons()
	{
	}
};