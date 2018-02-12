// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsWidget_Crafting.generated.h"

UCLASS()
class CSCORE_API UCsWidget_Crafting : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void Init() override;

	UPROPERTY(meta = (BindWidget))
	UVerticalBox* MyVerticalBox;

	TCsFVector2D Position;
	TCsFVector2D Size;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Header_Text;

	UPROPERTY(meta = (BindWidget))
	UGridPanel* Options_Grid;

	UPROPERTY(meta = (BindWidget))
	UComboBoxString* Options_ComboBox;

	UPROPERTY(meta = (BindWidget))
	UBorder* Count_Border;

	UPROPERTY(meta = (BindWidget))
	USpinBox* Count_Spin;

	FCsWidget_SpinIntBox CurrentCount;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* MyProgressBar;

	FCsWidget_Bar ProgressBar;

	UPROPERTY(meta = (BindWidget))
	class UCsWidget_Crafting_Grid* MyGrid;
};