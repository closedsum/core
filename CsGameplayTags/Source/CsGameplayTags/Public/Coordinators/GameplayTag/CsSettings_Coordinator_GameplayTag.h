// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CsSettings_Coordinator_GameplayTag.generated.h"

// FCsSettings_Coordinator_GameplayTag
#pragma region

class UCsCoordinator_GameplayTag;
class UClass;

USTRUCT(BlueprintType)
struct CSGAMEPLAYTAGS_API FCsSettings_Coordinator_GameplayTag
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsGameplayTags|Coordinators|GameplayTag")
	TSoftClassPtr<UCsCoordinator_GameplayTag> Class;

	FCsSettings_Coordinator_GameplayTag();

	static const FCsSettings_Coordinator_GameplayTag& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Coordinator_GameplayTag