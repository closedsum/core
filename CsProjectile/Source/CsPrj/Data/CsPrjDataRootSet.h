// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	FCsProjectileSettings_DataTable_Projectiles Projectiles;

	FCsPrjDataRootSet() :
		Projectiles()
	{
	}
};