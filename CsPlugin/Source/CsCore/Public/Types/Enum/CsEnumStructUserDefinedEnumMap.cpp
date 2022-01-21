// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"
#include "CsCore.h"

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