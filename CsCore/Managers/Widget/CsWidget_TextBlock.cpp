// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsWidget_TextBlock.h"
#include "CsCore.h"

namespace ECsWidgetTextBlockCachedString
{
	namespace Str
	{
		const FString Text = TEXT("Text");
	}
}

UCsWidget_TextBlock::UCsWidget_TextBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_TextBlock::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	Text.Set(MyText);
	const FString MemberName = ECsWidgetTextBlockCachedString::Str::Text;
	Text.Init(MemberName, MemberName, GetName() + ECsCachedString::Str::Dot + MemberName);

	HasNativeContructed = true;
}

void UCsWidget_TextBlock::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Text.OnNativeTick(InDeltaTime);

	// Position
	if (Position.HasChanged())
	{
		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
		ParentSlot->SetPosition(Position.Get());
	}
	// Size
	if (!Size.HasChanged())
	{
		//SetDesiredSizeInViewport(Size.Get());

		// Set Size of TextBlock
		UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(MyText->Slot);
		ChildSlot->SetSize(Size.Get());
		// Set Size of Widget
		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
		ParentSlot->SetSize(Size.Get());
	}
	Position.Clear();
	Size.Clear();

}

void UCsWidget_TextBlock::Allocate(const uint16& ActiveIndex, FCsSimpleWidgetPayload* Payload, const float &Time, const float &RealTime, const uint64 &Frame, UObject* InOwner, UObject* InParent)
{
	Super::Allocate(ActiveIndex, Payload, Time, RealTime, Frame, InOwner, InParent);

	Text.SetString(Payload->DisplayName);
}

void UCsWidget_TextBlock::DeAllocate()
{
	Super::DeAllocate();

	Text.SetString(ECsCachedString::Str::Empty);
}

void UCsWidget_TextBlock::OnAddToCanvas()
{
	Super::OnAddToCanvas();

	UCanvasPanelSlot* ChildSlot = Cast<UCanvasPanelSlot>(MyText->Slot);
	UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
	ParentSlot->SetAlignment(ChildSlot->GetAlignment());
}

void UCsWidget_TextBlock::Show()
{
	Super::Show();

	Text.SetIsEnabled(true);
	Text.SetVisibility(DefaultVisibility);
}

void UCsWidget_TextBlock::Hide()
{
	Text.SetVisibility(ESlateVisibility::Hidden);
	Text.SetIsEnabled(false);

	Super::Hide();
}

void UCsWidget_TextBlock::SetString(const FString &InString)
{
	Text.SetString(InString);
}