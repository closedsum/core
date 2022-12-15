// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Damage.h"
#include "Value/Types/CsTypes_DamageValue.h"
	// Debug
#include "Debug/CsTypes_Debug.h"

#include "CsSettings_Manager_Damage.generated.h"

// FCsSettings_Manager_Damage_Event
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Manager_Damage_Event
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage")
	FCsDebugDrawPie DrawPie;

	FCsSettings_Manager_Damage_Event() :
		PoolSize(256),
		DrawPie()
	{
	}

	static const FCsSettings_Manager_Damage_Event& Get();
};

#pragma endregion FCsSettings_Manager_Damage_Event

// FCsSettings_Manager_Damage_Value
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Manager_Damage_Value
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Damage_Value() :
		PoolSize(256)
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage_Value

// FCsSettings_Manager_Damage_Range
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Manager_Damage_Range
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Damage_Range() :
		PoolSize(256)
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage_Range

// FCsSettings_Manager_Damage_Modifier
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Manager_Damage_Modifier
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage", meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Damage_Modifier() :
		PoolSize(256)
	{
	}

	static const FCsSettings_Manager_Damage_Modifier& Get();
};

#pragma endregion FCsSettings_Manager_Damage_Modifier

// FCsSettings_Manager_Damage
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Manager_Damage
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage")
	FCsSettings_Manager_Damage_Event Event;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage")
	FCsSettings_Manager_Damage_Value Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage")
	FCsSettings_Manager_Damage_Range Range;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsDmg|Settings|Manager|Damage")
	FCsSettings_Manager_Damage_Modifier Modifier;

	FCsSettings_Manager_Damage() :
		Event(),
		Value(),
		Range(),
		Modifier()
	{
	}

	static const FCsSettings_Manager_Damage& Get();
};

#pragma endregion FCsSettings_Manager_Damage

// FCsSettings_Manager_Damage_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSDMG_API FCsSettings_Manager_Damage_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Damage_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage_UnitTest