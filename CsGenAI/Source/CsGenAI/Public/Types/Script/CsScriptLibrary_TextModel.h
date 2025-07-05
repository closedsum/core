// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_GenAI.h"

#include "CsScriptLibrary_TextModel.generated.h"

UCLASS()
class CSGENAI_API UCsScriptLibrary_TextModel : public UObject
{
	GENERATED_UCLASS_BODY()

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGenAI|Library|Text|Model", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToDisplayName(const ECsTextModel& Enum);

#pragma endregion Enum
};