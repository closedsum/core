// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Settings/CsTypes_ProjectileSettings.h"

#include "CsPrjDataRootSet.generated.h"

class UDataTable;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UDataTable> ProjectileClasses;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FCsProjectileSettings_DataTable_Projectiles> Projectiles;

	FCsPrjDataRootSet() :
		ProjectileClasses(),
		Projectiles()
	{
	}
};