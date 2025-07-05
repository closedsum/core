// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
// Types
#include "Types/CsTypes_GenAI.h"

#include "CsScriptLibrary_GenAIService.generated.h"

UCLASS()
class CSGENAI_API UCsScriptLibrary_GenAIService : public UObject
{
	GENERATED_UCLASS_BODY()

// Enum
#pragma region
public:

	UFUNCTION(BlueprintPure, Category = "CsGen|Library|Service", meta = (AutoCreateRefTerm = "Enum"))
	static FString ToString(const ECsGenAIService& Enum);

#pragma endregion Enum
};