// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"

#include "CsUserWidget_Fade.generated.h"

class UImage;

UCLASS(Blueprintable)
class CSUI_API UCsUserWidget_Fade : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UImage* Fade_Image;
};