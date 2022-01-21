// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "Managers/Input/CsTypes_Key.h"

#include "CsSettings_Manager_Time.generated.h"

// FCsSettings_Manager_Time_CustomUpdate
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Time_CustomUpdate
{
	GENERATED_USTRUCT_BODY()

public:

	/** The input to use for CustomUpdate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSet<FKey> Keys;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (UIMin = "0.0", ClampMin = "0.0"))
	float DeltaTime; 

	/** Whether to allow sustained pressing of Key for Update.
		NOTE: Set to false if the intention is to "Step" 1 "Frame" at a time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bAllowSustained;

	FCsSettings_Manager_Time_CustomUpdate() :
		Keys(),
		DeltaTime(0.01667f),
		bAllowSustained(true)
	{
	}
};

#pragma endregion FCsSettings_Manager_Time

// FCsSettings_Manager_Time
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FCsSettings_Manager_Time
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUpdateGroup, FCsSet_Key> TogglePauseGroupByKeysMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FECsUpdateGroup, FCsSettings_Manager_Time_CustomUpdate> CustomUpdateMap;

	FCsSettings_Manager_Time() :
		TogglePauseGroupByKeysMap(),
		CustomUpdateMap()
	{
	}
};

#pragma endregion FCsSettings_Manager_Time