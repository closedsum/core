// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "UI/Simple/CsWidget_ButtonAndText.h"
#include "CsCore.h"

// Managers
#include "Managers/Input/CsManager_Input.h"

// Cache
#pragma region

namespace ECsWidgetButtonAndTextCached
{
	namespace Str
	{
		const FString ButtonAndText = TEXT("ButtonAndText");
		const FString Button = TEXT("Button");
		const FString MyButton = TEXT("MyButton");
		const FString Text = TEXT("Text");
		const FString MyText = TEXT("MyText");
	}
}

#pragma endregion Cache

UCsWidget_ButtonAndText::UCsWidget_ButtonAndText(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	DefaultVisibility = ESlateVisibility::Visible;
}

void UCsWidget_ButtonAndText::OnNativeConstruct()
{
	Super::OnNativeConstruct();

	// Button
	ButtonAndText.Button.Set(MyButton);
	const FString& MemberName   = ECsWidgetButtonAndTextCached::Str::ButtonAndText;
	const FString& MyButtonName = ECsWidgetButtonAndTextCached::Str::MyButton;
	const FString& ButtonName   = ECsWidgetButtonAndTextCached::Str::Button;
	ButtonAndText.Button.Init(ButtonName, MyButtonName, GetName() + ECsCached::Str::Dot + MemberName);

	MyButton->OnPressed.AddDynamic(this, &UCsWidget_ButtonAndText::MyButton_OnPressed);

	// Text
	ButtonAndText.Text.Set(MyText);
	const FString& MyTextName = ECsWidgetButtonAndTextCached::Str::MyText;
	const FString& TextName   = ECsWidgetButtonAndTextCached::Str::Text;
	ButtonAndText.Text.Init(TextName, MyTextName, GetName() + ECsCached::Str::Dot + MemberName);
}

void UCsWidget_ButtonAndText::OnNativeTick(const FGeometry& MyGeometry, const float &InDeltaTime)
{
	Super::OnNativeTick(MyGeometry, InDeltaTime);

	ButtonAndText.OnNativeTick(InDeltaTime);
}

void UCsWidget_ButtonAndText::Show()
{
	Super::Show();

	ButtonAndText.SetIsEnabled(true);
	ButtonAndText.SetVisibility(DefaultVisibility);
	ButtonAndText.Button.SetVisibility(ESlateVisibility::Visible);
	ButtonAndText.Text.SetVisibility(ESlateVisibility::HitTestInvisible);
}

void UCsWidget_ButtonAndText::Hide()
{
	ButtonAndText.SetVisibility(ESlateVisibility::Hidden);
	ButtonAndText.SetIsEnabled(false);

	Super::Hide();
}

UPanelSlot* UCsWidget_ButtonAndText::GetChildSlot()
{
	return MyButton->Slot;
}

void UCsWidget_ButtonAndText::MyButton_OnPressed()
{
	UCsManager_Input* Manager_Input = UCsManager_Input::Get(GetWorld());

	Manager_Input->QueueInput(InputAction_OnPressed, ECsInputEvent::FirstPressed);

	MousePosition_OnPressed = Manager_Input->CurrentMousePosition;
}

void UCsWidget_ButtonAndText::MyButton_OnReleased()
{
	UCsManager_Input* Manager_Input = UCsManager_Input::Get(GetWorld());
	MousePosition_OnReleased		= Manager_Input->CurrentMousePosition;
}

void UCsWidget_ButtonAndText::MyButton_OnHovered(){}

void UCsWidget_ButtonAndText::SetImage(class UMaterialInstanceConstant* Material)
{
	MyButton->WidgetStyle.Normal.SetResourceObject(Material);
	MyButton->WidgetStyle.Hovered.SetResourceObject(Material);
	MyButton->WidgetStyle.Pressed.SetResourceObject(Material);
}

void UCsWidget_ButtonAndText::SetString(const FString& InString)
{
	ButtonAndText.Text.SetString(InString);
}