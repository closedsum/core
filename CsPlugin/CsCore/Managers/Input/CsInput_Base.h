// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

#include "../CoreUObject/Public/UObject/Object.h"
#include "Managers/Input/CsTypes_Input.h"
#include "CsInput_Base.generated.h"

class UCsManager_Input;

UCLASS()
class CSCORE_API UCsInput_Base : public UObject
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	FECsInputAction Action;

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	FCsInputInfo Info;

	UPROPERTY(BlueprintReadWrite, Category = "Input")
	int32 ActionMap;

	UPROPERTY(BlueprintReadOnly, Category = "Input")
	UCsManager_Input* Manager_Input;

#if WITH_EDITOR
	virtual void OnPrePIEEnded(const bool bIsSimulating);
#endif // #if WITH_EDITOR
};