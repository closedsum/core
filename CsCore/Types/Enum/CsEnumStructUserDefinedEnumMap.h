// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Primitive.h"
#include "CsEnumStructUserDefinedEnumMap.generated.h"

class UUserDefinedEnum;

UCLASS(Blueprintable)
class CSCORE_API UCsEnumStructUserDefinedEnumMap : public UObject
{
	GENERATED_UCLASS_BODY()

	virtual UUserDefinedEnum* GetUserDefinedEnum(const FECsUserDefinedEnum& EnumType);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Enum")
	UUserDefinedEnum* InputAction;
};