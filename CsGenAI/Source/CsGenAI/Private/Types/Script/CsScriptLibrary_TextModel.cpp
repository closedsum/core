// Copyright 2017-2025 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Script/CsScriptLibrary_TextModel.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_TextModel)

UCsScriptLibrary_TextModel::UCsScriptLibrary_TextModel(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using EnumMapType = EMCsTextModel;
using EnumType = ECsTextModel;

// Enum
#pragma region

FString UCsScriptLibrary_TextModel::ToDisplayName(const EnumType& Enum)
{
	return EMCsTextModel::Get().ToDisplayName(Enum);
}

#pragma endregion Enum