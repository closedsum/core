// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "OpenAI/Types/Script/CsScriptLibrary_OpenAI_TextToSpeechModel.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_OpenAI_TextToSpeechModel)

UCsScriptLibrary_OpenAI_TextToSpeechModel::UCsScriptLibrary_OpenAI_TextToSpeechModel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using EnumMapType = EMCsOpenAI_TextToSpeechModel;
using EnumType = ECsOpenAI_TextToSpeechModel;

// Enum
#pragma region

FString UCsScriptLibrary_OpenAI_TextToSpeechModel::ToDisplayName(const EnumType& Enum)
{
	return EMCsOpenAI_TextToSpeechModel::Get().ToDisplayName(Enum);
}

#pragma endregion Enum