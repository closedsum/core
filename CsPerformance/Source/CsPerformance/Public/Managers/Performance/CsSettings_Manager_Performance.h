// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsSettings_Manager_Performance.generated.h"

// FCsSettings_Manager_Performance
#pragma region

class UCsManager_Performance;
class UClass;

USTRUCT(BlueprintType)
struct CSPERFORMANCE_API FCsSettings_Manager_Performance
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPerformance|Managers|Performance")
	TSoftClassPtr<UCsManager_Performance> Class;

	FCsSettings_Manager_Performance();

	static const FCsSettings_Manager_Performance& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Performance