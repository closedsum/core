// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_TextBlock.h"
#include "CsCore.h"

namespace ECsWidgetTextBlockCachedString
{
	namespace Str
	{
		const FString MyText = TEXT("MyText");
	}
}

UCsWidget_TextBlock::UCsWidget_TextBlock(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_TextBlock::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	Text.Set(MyText);
	const FString& TextName   = ECsCached::Str::Text;
	const FString& MyTextName = ECsWidgetTextBlockCachedString::Str::MyText;
	Text.Init(TextName, MyTextName, GetName() + ECsCached::Str::Dot + TextName);
}

void UCsWidget_TextBlock::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Text.OnNativeTick(InDeltaTime);
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

UPanelSlot* UCsWidget_TextBlock::GetChildSlot()
{
	return MyText->Slot;
}

void UCsWidget_TextBlock::SetString(const FString &InString)
{
	Text.SetString(InString);
}