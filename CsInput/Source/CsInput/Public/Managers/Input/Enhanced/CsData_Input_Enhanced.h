// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Managers/Input/Enhanced/CsTypes_Input_Enhanced.h"

#include "CsData_Input_Enhanced.generated.h"

// Inner
#pragma region

class UInputMappingContext;

USTRUCT(BlueprintType)
struct CSINPUT_API FCsData_Input_Enhanced_Inner
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input|Enhanced")
	TArray<FCsInputMappingContextInfo> ContextInfos;
	
	FCsData_Input_Enhanced_Inner() :
		ContextInfos()
	{
	}
};

#pragma endregion Inner

UCLASS(BlueprintType, Blueprintable)
class CSINPUT_API UCsData_Input_Enhanced : public UObject
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsInput|Input|Enhanced")
	FCsData_Input_Enhanced_Inner Inner;
};