// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"
#include "CsTypes_DamageExpression.generated.h"
#pragma once

// FCsScriptDamagePoint
#pragma region

struct FCsDamagePointEmu;

USTRUCT(BlueprintType)
struct CSCORE_API FCsScriptDamagePoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FECsDamageType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Damage;

	FCsScriptDamagePoint() :
		Type(),
		Damage(0.0f)
	{
	}

	void SetExpression(FCsDamagePointEmu* Expression);
};

#pragma endregion FCsScriptDamagePoint