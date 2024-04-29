// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"

UCsEnumStructUserDefinedEnumMap::UCsEnumStructUserDefinedEnumMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UUserDefinedEnum* UCsEnumStructUserDefinedEnumMap::GetUserDefinedEnum(const FECsUserDefinedEnum& EnumType)
{
	// FECsInputAction
	if (EnumType == NCsUserDefinedEnum::FECsInputAction)
		return InputAction;
	return nullptr;
}