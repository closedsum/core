// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Script/CsScriptLibrary_GenAIService.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_GenAIService)

UCsScriptLibrary_GenAIService::UCsScriptLibrary_GenAIService(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using EnumMapType = EMCsGenAIService;
using EnumType = ECsGenAIService;

// Enum
#pragma region

FString UCsScriptLibrary_GenAIService::ToString(const EnumType& Enum)
{
	return EMCsGenAIService::Get().ToString(Enum);
}

#pragma endregion Enum