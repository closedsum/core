// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
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

void UCsWidget_TextBlock::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	// Position
	if (Position.HasChanged())
	{
		UCanvasPanelSlot* ParentSlot = Cast<UCanvasPanelSlot>(Slot);
		ParentSlot->SetPosition(Position.Get());
	}
	// Size
	if (!Size.HasChanged())
	{
		SetDesiredSizeInViewport(Size.Get());

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

void UCsWidget_TextBlock::SetPosition(const FVector2D &InPosition)
{
	Position = InPosition;
}

void UCsWidget_TextBlock::SetSize(const FVector2D &InSize)
{
	Size = InSize;
}