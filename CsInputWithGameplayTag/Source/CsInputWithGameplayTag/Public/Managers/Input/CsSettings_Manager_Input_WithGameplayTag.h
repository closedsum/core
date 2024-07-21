// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

#include "CsSettings_Manager_Input_WithGameplayTag.generated.h"

// FCsSettings_Manager_Input_WithGameplayTag
#pragma region

USTRUCT(BlueprintType)
struct CSINPUTWITHGAMEPLAYTAG_API FCsSettings_Manager_Input_WithGameplayTag
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|WithGameplayTag|Managers|Input", NoClear, meta = (MustImplement = "/Script/CsInputWithGameplayTag.CsManager_Input_WithGameplayTag"))
	TSoftClassPtr<UObject> Class;

	FCsSettings_Manager_Input_WithGameplayTag();

	static const FCsSettings_Manager_Input_WithGameplayTag& Get();

	bool IsValidChecked(const FString& Context) const;

	UClass* LoadClassChecked(const FString& Context) const;
};

#pragma endregion FCsSettings_Manager_Input_WithGameplayTag