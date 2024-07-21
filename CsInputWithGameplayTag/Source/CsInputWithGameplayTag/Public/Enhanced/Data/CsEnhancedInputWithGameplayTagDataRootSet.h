// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Log
#include "Utility/CsInputWithGameplayTagLog.h"

#include "CsEnhancedInputWithGameplayTagDataRootSet.generated.h"

class UCsData_EnhancedInput_WithGameplayTag;

USTRUCT(BlueprintType)
struct CSINPUTWITHGAMEPLAYTAG_API FCsEnhancedInputWithGameplayTagDataRootSet
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Enhanced|WithGameplayTag|DataRootSet", meta = (AllowedClasses = "/Script/CsInputWithGameplayTag.CsData_EnhancedInput_WithGameplayTag"))
	TSubclassOf<UCsData_EnhancedInput_WithGameplayTag> Data;

	FCsEnhancedInputWithGameplayTagDataRootSet() :
		Data(nullptr)
	{
	}

	bool IsValidChecked(const FString& Context) const;

	UCsData_EnhancedInput_WithGameplayTag* GetDataChecked(const FString& Context) const;
};