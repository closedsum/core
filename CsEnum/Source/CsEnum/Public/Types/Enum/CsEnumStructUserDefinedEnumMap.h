// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "UObject/Object.h"
#include "Types/Enum/CsUserDefinedEnum.h"

#include "CsEnumStructUserDefinedEnumMap.generated.h"

class UUserDefinedEnum;

UCLASS(Blueprintable)
class CSENUM_API UCsEnumStructUserDefinedEnumMap : public UObject
{
	GENERATED_UCLASS_BODY()

	virtual UUserDefinedEnum* GetUserDefinedEnum(const FECsUserDefinedEnum& EnumType);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enum")
	UUserDefinedEnum* InputAction;
};