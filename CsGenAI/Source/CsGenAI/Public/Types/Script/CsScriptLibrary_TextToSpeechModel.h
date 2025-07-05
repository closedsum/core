// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_GenAI.h"

#include "CsScriptLibrary_TextToSpeechModel.generated.h"

UCLASS()
class CSGENAI_API UCsScriptLibrary_TextToSpeechModel : public UObject
{
	GENERATED_UCLASS_BODY()

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGen|Library|Text To Speech|Model", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToDisplayName(const ECsTextToSpeechModel& Enum);

#pragma endregion Enum
};