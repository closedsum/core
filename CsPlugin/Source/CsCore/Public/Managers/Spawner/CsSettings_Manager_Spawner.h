// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsLog.h"

#include "CsSettings_Manager_Spawner.generated.h"

// FCsSettings_Manager_Character_Modifier
#pragma region

/**
* Describes any settings related to Spawner Modifiers.
*  Modifier is an object that implements the interface: NCsModifier::IModifier
*  Spawner Modifier is an objects that implements the interface: NCsSpawner::NModifier::IModifier
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Spawner_Modifier
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore", meta = (ClampMin = "256", UIMin = "256"))
	int32 PoolSize;

	FCsSettings_Manager_Spawner_Modifier() :
		PoolSize(256)
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Character_Modifier

// FCsSettings_Manager_Spawner
#pragma region

class UObject;
class UClass;

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Spawner
{
	GENERATED_USTRUCT_BODY()

public:

	/**  Describes any settings related to Character Modifiers */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore")
		FCsSettings_Manager_Spawner_Modifier Modifier;

	FCsSettings_Manager_Spawner() :
		Modifier()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsSettings_Manager_Spawner