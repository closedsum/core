// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_Int32.h"
#include "CsCore.h"

// Cache
#pragma region

namespace ECsWidgetInt32Cached
{
	namespace Str
	{
		const FString MyText = TEXT("MyText");
	}
}

#pragma endregion Cache

UCsWidget_Int32::UCsWidget_Int32(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void UCsWidget_Int32::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	Text.Set(MyText);
	const FString& TextName   = ECsCached::Str::Text;
	const FString& MyTextName = ECsWidgetInt32Cached::Str::MyText;
	Text.Init(TextName, MyTextName, GetName() + ECsCached::Str::Dot + TextName);
}

void UCsWidget_Int32::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	Text.OnNativeTick(InDeltaTime);
}

void UCsWidget_Int32::Show()
{
	Super::Show();

	Text.SetIsEnabled(true);
	Text.SetVisibility(DefaultVisibility);
}

void UCsWidget_Int32::Hide()
{
	Text.SetVisibility(ESlateVisibility::Hidden);
	Text.SetIsEnabled(false);

	Super::Hide();
}

UPanelSlot* UCsWidget_Int32::GetChildSlot()
{
	return MyText->Slot;
}

void UCsWidget_Int32::SetValue(const int32 &Value)
{
	Text.SetValue(Value);
}