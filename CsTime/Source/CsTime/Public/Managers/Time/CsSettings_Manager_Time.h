// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsTypes_Update.h"
#include "InputCoreTypes.h"

#include "CsSettings_Manager_Time.generated.h"

// FCsSettings_Manager_Time_CustomUpdate
#pragma region

USTRUCT(BlueprintType)
struct CSTIME_API FCsSettings_Manager_Time_CustomUpdate
{
	GENERATED_USTRUCT_BODY()

public:

	/** The input to use for CustomUpdate. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTime|Time")
	TSet<FKey> Keys;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTime|Time", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float DeltaTime; 

	/** Whether to allow sustained pressing of Key for Update.
		NOTE: Set to false if the intention is to "Step" 1 "Frame" at a time. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTime|Time")
	bool bAllowSustained;

	FCsSettings_Manager_Time_CustomUpdate() :
		Keys(),
		DeltaTime(0.01667f),
		bAllowSustained(true)
	{
	}
};

#pragma endregion FCsSettings_Manager_Time_CustomUpdate

// FCsSettings_Manager_Time_Set_Key
#pragma region

USTRUCT(BlueprintType)
struct CSTIME_API FCsSettings_Manager_Time_Set_Key
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTime|Time")
	TSet<FKey> Set;

	FCsSettings_Manager_Time_Set_Key() :
		Set()
	{
	}
};

#pragma endregion FCsSettings_Manager_Time

// FCsSettings_Manager_Time
#pragma region

class UCsManager_Time;

USTRUCT(BlueprintType)
struct CSTIME_API FCsSettings_Manager_Time
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, NoClear, Category = "CsTime|Managers|Time")
	TSoftClassPtr<UCsManager_Time> Class;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTime|Time")
	TMap<FECsUpdateGroup, FCsSettings_Manager_Time_Set_Key> TogglePauseGroupByKeysMap;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsTime|Time")
	TMap<FECsUpdateGroup, FCsSettings_Manager_Time_CustomUpdate> CustomUpdateMap;

	FCsSettings_Manager_Time();

	static const FCsSettings_Manager_Time& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Time