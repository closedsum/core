// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "OpenAI/Types/CsTypes_OpenAI.h"

#include "CsScriptLibrary_OpenAI_SpeechToTextModel.generated.h"

UCLASS()
class CSGENAI_API UCsScriptLibrary_OpenAI_SpeechToTextModel : public UObject
{
	GENERATED_UCLASS_BODY()

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGen|Library|OpenAI|Speech To Text|Model", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToDisplayName(const ECsOpenAI_SpeechToTextModel& Enum);

#pragma endregion Enum
};