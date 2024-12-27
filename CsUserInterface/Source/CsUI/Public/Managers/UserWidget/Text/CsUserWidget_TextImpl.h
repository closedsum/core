// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Blueprint/UserWidget.h"
// Types
#include "Managers/UserWidget/Text/CsUserWidget_TextInfo.h"

#include "CsUserWidget_TextImpl.generated.h"

class UTextBlock;

UCLASS()
class CSUI_API UCsUserWidget_TextImpl : public UUserWidget
{
	GENERATED_UCLASS_BODY()

private:

	using InfoType = NCsUserWidget::NText::FInfo;

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;


	void SetInfo(const InfoType& Info);
};