// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "../CoreUObject/Public/UObject/Object.h"
#include "Types/CsTypes_Input.h"
#include "CsInput_Base.generated.h"

UCLASS()
class CSCORE_API UCsInput_Base : public UObject
{
	GENERATED_UCLASS_BODY()

	TCsInputAction Action;

	CS_DECLARE_INPUT_ACTION

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	FCsInputInfo Info;

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	int32 ActionMap;

	CS_DECLARE_INPUT_ACTION_MAP

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	class ACsManager_Input* Manager_Input;

#if WITH_EDITOR
	void OnPrePIEEnded(const bool IsSimulating);
#endif // #if WITH_EDITOR
};