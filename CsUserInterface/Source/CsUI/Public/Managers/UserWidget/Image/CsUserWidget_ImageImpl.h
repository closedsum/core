// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"
// Types
#include "Managers/UserWidget/Image/CsUserWidget_ImageInfo.h"

#include "CsUserWidget_ImageImpl.generated.h"

class UImage;

UCLASS()
class CSUI_API UCsUserWidget_ImageImpl : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:

	UPROPERTY(meta = (BindWidget))
	UImage* MyImage;

#define InfoType NCsUserWidget::NImage::FInfo
	void SetInfo(const InfoType& Info);
#undef InfoType
};