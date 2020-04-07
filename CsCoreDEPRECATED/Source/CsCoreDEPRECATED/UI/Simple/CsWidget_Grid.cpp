// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_Grid.h"
#include "CsCoreDEPRECATED.h"

UCsWidget_Grid::UCsWidget_Grid(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::SelfHitTestInvisible;
}

void UCsWidget_Grid::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);
}

void UCsWidget_Grid::Show()
{
	Super::Show();

	MyGridPanel->SetIsEnabled(true);
	MyGridPanel->SetVisibility(DefaultVisibility);
}

void UCsWidget_Grid::Hide()
{
	MyGridPanel->SetVisibility(ESlateVisibility::Visible);
	MyGridPanel->SetIsEnabled(false);

	Super::Hide();
}

UPanelSlot* UCsWidget_Grid::GetChildSlot()
{
	return MyGridPanel->Slot;
}