// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Widget/CsPooledWidget_TextBlock.h"
#include "CsCore.h"

namespace ECsPooledWidgetTextBlockCached
{
	namespace Str
	{
		const FString Text = TEXT("Text");
	}
}

UCsPooledWidget_TextBlock::UCsPooledWidget_TextBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsPooledWidget_TextBlock::NativeConstruct()
{
	Super::NativeConstruct();

	if (HasNativeContructed)
		return;

	Text.Set(MyText);
	const FString& MemberName = ECsPooledWidgetTextBlockCached::Str::Text;
	Text.Init(MemberName, MemberName, GetName() + ECsCached::Str::Dot + MemberName);

	HasNativeContructed = true;
}

void UCsPooledWidget_TextBlock::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Text.OnNativeTick(InDeltaTime);
}

void UCsPooledWidget_TextBlock::Allocate(FCsWidgetPayload* Payload)
{
	Super::Allocate(Payload);

	Text.SetString(Payload->DisplayName);
}

void UCsPooledWidget_TextBlock::DeAllocate()
{
	Super::DeAllocate();

	Text.SetString(ECsCached::Str::Empty);
}

void UCsPooledWidget_TextBlock::Show()
{
	Super::Show();

	Text.SetIsEnabled(true);
	Text.SetVisibility(DefaultVisibility);
}

void UCsPooledWidget_TextBlock::Hide()
{
	Text.SetVisibility(ESlateVisibility::Hidden);
	Text.SetIsEnabled(false);

	Super::Hide();
}

UPanelSlot* UCsPooledWidget_TextBlock::GetChildSlot()
{
	return MyText->Slot;
}

void UCsPooledWidget_TextBlock::SetString(const FString &InString)
{
	Text.SetString(InString);
}