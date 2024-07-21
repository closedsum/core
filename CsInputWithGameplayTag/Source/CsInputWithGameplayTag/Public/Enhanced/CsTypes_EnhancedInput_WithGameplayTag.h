// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Input/CsTypes_Input_WithGameplayTag.h"
// Log
#include "Utility/CsInputWithGameplayTagLog.h"

#include "CsTypes_EnhancedInput_WithGameplayTag.generated.h"

// FCsEnhancedInput_WithGameplayTag_ActionInfo
#pragma region

class UInputAction;

USTRUCT(BlueprintType)
struct CSINPUTWITHGAMEPLAYTAG_API FCsEnhancedInput_WithGameplayTag_ActionInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Enhanced")
	UInputAction* Action;

	/** The Tag that will be broadcasted for any corresponding [Action, Event]. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Enhanced")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Enhanced")
	TSet<ECsInputActionEvent> Events;

	FCsEnhancedInput_WithGameplayTag_ActionInfo() :
		Action(nullptr),
		Tag(),
		Events()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsInput::NWithGameplayTag::FLog::Warning) const;
};

#pragma endregion FCsEnhancedInput_WithGameplayTag_ActionInfo

// FCsEnhancedInput_WithGameplayTag_MappingInfo
#pragma region

class UInputMappingContext;

USTRUCT(BlueprintType)
struct CSINPUTWITHGAMEPLAYTAG_API FCsEnhancedInput_WithGameplayTag_MappingInfo
{
	GENERATED_USTRUCT_BODY()

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Enhanced")
	UInputMappingContext* MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Enhanced")
	FGameplayTag Tag;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsInput|Enhanced")
	TArray<FCsEnhancedInput_WithGameplayTag_ActionInfo> ActionInfos;

	FCsEnhancedInput_WithGameplayTag_MappingInfo() :
		MappingContext(nullptr),
		Tag(),
		ActionInfos()
	{
	}

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsInput::NWithGameplayTag::FLog::Warning) const;
};

#pragma endregion FCsEnhancedInput_WithGameplayTag_MappingInfo