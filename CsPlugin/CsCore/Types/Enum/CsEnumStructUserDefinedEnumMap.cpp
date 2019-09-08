// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnumStructUserDefinedEnumMap.h"
#include "CsCore.h"

UCsEnumStructUserDefinedEnumMap::UCsEnumStructUserDefinedEnumMap(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

UUserDefinedEnum* UCsEnumStructUserDefinedEnumMap::GetUserDefinedEnum(const FECsUserDefinedEnum& EnumType)
{
	// FECsInputAction
	if (NCsUserDefinedEnum::FECsInputAction)
		return InputAction;
	return nullptr;
}