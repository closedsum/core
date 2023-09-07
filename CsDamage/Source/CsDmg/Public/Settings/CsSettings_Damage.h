// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Debug/CsTypes_Debug.h"

#include "CsSettings_Damage.generated.h"

// FCsSettings_Damage_Debug
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Damage_Debug
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	FCsDebugDrawSphere Sphere;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	bool bSphereAsCircle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	FCsDebugDrawCircle Circle;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	FCsDebugDrawPie Pie;

	FCsSettings_Damage_Debug() :
		Sphere(),
		bSphereAsCircle(false),
		Circle(),
		Pie()
	{
	}

	static const FCsSettings_Damage_Debug& Get();
};

#pragma endregion FCsSettings_Damage_Debug

// FCsSettings_Damage
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Damage
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg")
	FCsSettings_Damage_Debug Debug;

	FCsSettings_Damage() :
		Debug()
	{
	}

	static const FCsSettings_Damage& Get();
};

#pragma endregion FCsSettings_Damage