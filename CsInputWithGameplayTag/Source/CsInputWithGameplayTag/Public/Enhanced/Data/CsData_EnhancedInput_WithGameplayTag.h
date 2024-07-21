// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Enhanced/CsTypes_EnhancedInput_WithGameplayTag.h"

#include "CsData_EnhancedInput_WithGameplayTag.generated.h"

// Inner
#pragma region

USTRUCT(BlueprintType)
struct CSINPUTWITHGAMEPLAYTAG_API FCsData_EnhancedInput_WithGameplayTag_Inner
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input|Enhanced")
	TArray<FCsEnhancedInput_WithGameplayTag_MappingInfo> MappingInfos;
	
	FCsData_EnhancedInput_WithGameplayTag_Inner() :
		MappingInfos()
	{
	}
};

#pragma endregion Inner

UCLASS(BlueprintType, Blueprintable)
class CSINPUTWITHGAMEPLAYTAG_API UCsData_EnhancedInput_WithGameplayTag : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInputWithGameplayTag|Input|Enhanced")
	FCsData_EnhancedInput_WithGameplayTag_Inner Inner;
};