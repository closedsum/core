// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Script/CsScriptLibrary_SpeechToTextModel.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_SpeechToTextModel)

UCsScriptLibrary_SpeechToTextModel::UCsScriptLibrary_SpeechToTextModel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using EnumMapType = EMCsSpeechToTextModel;
using EnumType = ECsSpeechToTextModel;

// Enum
#pragma region

FString UCsScriptLibrary_SpeechToTextModel::ToDisplayName(const EnumType& Enum)
{
	return EMCsSpeechToTextModel::Get().ToDisplayName(Enum);
}

#pragma endregion Enum