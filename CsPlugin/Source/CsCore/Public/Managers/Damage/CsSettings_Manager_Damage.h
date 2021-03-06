// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/CsTypes_Damage.h"
#include "Managers/Damage/Value/CsTypes_DamageValue.h"

#include "CsSettings_Manager_Damage.generated.h"
#pragma once

// FCsSettings_Manager_Damage_Event
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Damage_Event
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Damage_Event() :
		PoolSize(256)
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage_Event

// FCsSettings_Manager_Damage_Value
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Damage_Value
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "64", UIMin = "64"))
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
struct CSCORE_API FCsSettings_Manager_Damage_Range
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "64", UIMin = "64"))
	int32 PoolSize;

	FCsSettings_Manager_Damage_Range() :
		PoolSize(256)
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage_Range

// FCsSettings_Manager_Damage
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Damage
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSettings_Manager_Damage_Event Event;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSettings_Manager_Damage_Value Value;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSettings_Manager_Damage_Range Range;

	FCsSettings_Manager_Damage() :
		Event(),
		Value(),
		Range()
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage

// FCsSettings_Manager_Damage_UnitTest
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Damage_UnitTest
{
	GENERATED_USTRUCT_BODY()

public:

	FCsSettings_Manager_Damage_UnitTest()
	{
	}
};

#pragma endregion FCsSettings_Manager_Damage_UnitTest