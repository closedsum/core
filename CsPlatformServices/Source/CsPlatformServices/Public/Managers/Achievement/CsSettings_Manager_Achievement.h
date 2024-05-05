// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Manager_Achievement.generated.h"

// FCsSettings_Manager_Achievement
#pragma region

class UCsManager_Achievement;
class UClass;

USTRUCT(BlueprintType)
struct CSPLATFORMSERVICES_API FCsSettings_Manager_Achievement
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsPlatformServices|Managers|Achievement")
	TSoftClassPtr<UCsManager_Achievement> Class;

	FCsSettings_Manager_Achievement();

	static const FCsSettings_Manager_Achievement& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Achievement