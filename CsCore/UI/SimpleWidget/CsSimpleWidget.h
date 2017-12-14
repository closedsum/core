// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Types/CsTypes_Input.h"
#include "CsSimpleWidget.generated.h"

UCLASS()
class CSCORE_API UCsSimpleWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

	UPROPERTY(meta = (BindWidget))
	UCanvas* Canvas;
};