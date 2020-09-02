// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"
#include "CsTypes_Data_Damage.generated.h"
#pragma once

// FCsScriptData_DamagePoint
#pragma region

struct FCsData_DamagePointEmu;

USTRUCT(BlueprintType)
struct CSCORE_API FCsScriptData_DamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsDamageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	FCsScriptData_DamagePoint() :
		Type(),
		Damage(0.0f)
	{
	}

	void SetData(FCsData_DamagePointEmu* Data);
};

#pragma endregion FCsScriptDamagePoint