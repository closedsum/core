// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsCoroutineLog.h"

#include "CsSettings_CoroutineScheduler.generated.h"

// FCsSettings_CoroutineScheduler_Custom
#pragma region


USTRUCT(BlueprintType)
struct CSCOROUTINE_API FCsSettings_CoroutineScheduler_Custom
{
	GENERATED_USTRUCT_BODY()

public:

	/** The number of Custom Schedules (groups of 2048 Routines) that are created. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCoroutine", meta = (UIMin = "1", ClampMin = "1", UIMax = "4", ClampMax = "4"))
	int32 MaxGroups;

	/** The maximum number of Owners for updating their own set of Routines. 
		NOTE: Currently, MaxOwners * MaxRoutinesPerOwner <= 2048. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCoroutine", meta = (UIMin = "1", ClampMin = "1", UIMax = "2048", ClampMax = "2048"))
	int32 MaxOwners;

	/** The maximum number of Routines reserved for an Owner. 
		NOTE: Currently, MaxOwners * MaxRoutinesPerOwner <= 2048. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCoroutine", meta = (UIMin = "1", ClampMin = "1", UIMax = "2048", ClampMax = "2048"))
	int32 MaxRoutinesPerOwner;

	FCsSettings_CoroutineScheduler_Custom() :
		MaxGroups(1),
		MaxOwners(128),
		MaxRoutinesPerOwner(16)
	{
	}

	static const FCsSettings_CoroutineScheduler_Custom& Get();

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_CoroutineScheduler_Custom

// FCsSettings_CoroutineScheduler
#pragma region


USTRUCT(BlueprintType)
struct CSCOROUTINE_API FCsSettings_CoroutineScheduler
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCoroutine")
	FCsSettings_CoroutineScheduler_Custom Custom;

	FCsSettings_CoroutineScheduler() :
		Custom()
	{
	}

	static const FCsSettings_CoroutineScheduler& Get();

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_CoroutineScheduler