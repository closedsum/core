// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsSettings_Performance_UI.generated.h"

// FCsSettings_Performance_UI
#pragma region

class UClass;
class UUserWidget;

USTRUCT(BlueprintType)
struct CSPERFORMANCE_API FCsSettings_Performance_UI
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPerformance|UI", meta = (MustImplement = "/Script/CsPerformance.CsPerformanceUI"))
	TSoftClassPtr<UUserWidget> Class;

	FCsSettings_Performance_UI() :
		Class(nullptr)
	{
	}

	static const FCsSettings_Performance_UI& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Performance_UI