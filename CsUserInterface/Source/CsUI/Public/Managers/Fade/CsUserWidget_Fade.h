// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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