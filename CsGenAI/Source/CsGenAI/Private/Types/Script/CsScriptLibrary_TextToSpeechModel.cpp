// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Script/CsScriptLibrary_TextToSpeechModel.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_TextToSpeechModel)

UCsScriptLibrary_TextToSpeechModel::UCsScriptLibrary_TextToSpeechModel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using EnumMapType = EMCsTextToSpeechModel;
using EnumType = ECsTextToSpeechModel;

// Enum
#pragma region

FString UCsScriptLibrary_TextToSpeechModel::ToDisplayName(const EnumType& Enum)
{
	return EMCsTextToSpeechModel::Get().ToDisplayName(Enum);
}

#pragma endregion Enum