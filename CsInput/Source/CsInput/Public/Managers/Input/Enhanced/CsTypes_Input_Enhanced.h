// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_StructOps.h"
// Log
#include "Utility/CsInputLog.h"

#include "CsTypes_Input_Enhanced.generated.h"

// FCsInputMappingContextInfo
#pragma region

class UInputMappingContext;

/**
*
*/
USTRUCT(BlueprintType)
struct CSINPUT_API FCsInputMappingContextInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Input|Enhanced")
	UInputMappingContext* MappingContext;

public:

	FCsInputMappingContextInfo() :
		MappingContext(nullptr)
	{
	}

	CS_STRUCT_OPS_IS_VALID_CHECKED(FCsInputMappingContextInfo)
	CS_STRUCT_OPS_IS_VALID(FCsInputMappingContextInfo)
	CS_STRUCT_OPS_IS_TOP_VALID_CHECKED(FCsInputMappingContextInfo)
	CS_STRUCT_OPS_IS_TOP_VALID(FCsInputMappingContextInfo)

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsInput::FLog::Warning) const;
	bool IsTopValidChecked(const FString& Context) const;
	bool IsTopValid(const FString& Context, void(*Log)(const FString&) = &NCsInput::FLog::Warning) const;
};

#pragma endregion FCsInputMappingContextInfo