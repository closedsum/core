// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_TextBlock.h"
#include "CsCore.h"

namespace ECsWidgetTextBlockCachedString
{
	namespace Str
	{
		const FString Text = TEXT("Text");
		const FString MyText = TEXT("MyText");
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
	const FString& TextName   = ECsWidgetTextBlockCachedString::Str::Text;
	const FString& MyTextName = ECsWidgetTextBlockCachedString::Str::MyText;
	Text.Init(TextName, MyTextName, GetName() + ECsCachedString::Str::Dot + TextName);

	HasNativeContructed = true;
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

void UCsWidget_TextBlock::SetString(const FString &InString)
{
	Text.SetString(InString);
}