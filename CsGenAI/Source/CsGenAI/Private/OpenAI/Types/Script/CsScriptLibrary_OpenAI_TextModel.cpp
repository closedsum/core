// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "OpenAI/Types/Script/CsScriptLibrary_OpenAI_TextModel.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_OpenAI_TextModel)

UCsScriptLibrary_OpenAI_TextModel::UCsScriptLibrary_OpenAI_TextModel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using EnumMapType = EMCsOpenAI_TextModel;
using EnumType = ECsOpenAI_TextModel;

// Enum
#pragma region

FString UCsScriptLibrary_OpenAI_TextModel::ToDisplayName(const EnumType& Enum)
{
	return EMCsOpenAI_TextModel::Get().ToDisplayName(Enum);
}

#pragma endregion Enum