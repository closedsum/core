// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"
#include "CsTypes_Data_ProjectileDamage.generated.h"
#pragma once

// FCsPrjDamageExpression
#pragma region

struct FCsDamageExpressionPoint;

USTRUCT(BlueprintType)
struct CSPRJ_API FCsPrjDamageExpressionPoint
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Damage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsDamageType Type;

public:

	FCsPrjDamageExpressionPoint() : 
		Damage(0.0f),
		Type()
	{
	}

	void SetExpression(FCsDamageExpressionPoint* Expression);
};

#pragma endregion FCsPrjDamageExpression