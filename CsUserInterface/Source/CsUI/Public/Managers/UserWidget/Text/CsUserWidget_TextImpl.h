// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

public:

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MyText;

#define InfoType NCsUserWidget::NText::FInfo
	void SetInfo(const InfoType& Info);
#undef InfoType
};