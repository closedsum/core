// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/CheckBox.h"
#include "Types/CsTypes.h"
#include "Types/CsTypes_Input.h"
#include "Common/CsCommon.h"
#include "CsUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsUserWidget_OnNativeTick, const FGeometry&, MyGeometry, float, InDeltaTime);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_OnOpenChild, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUserWidget_OnOpenChild, const TEnumAsByte<ECsWidgetType::Type>&);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_OnCloseChild, const uint8&, WidgetType);
DECLARE_MULTICAST_DELEGATE_OneParam(FBindableEvent_CsUserWidget_OnCloseChild, const TEnumAsByte<ECsWidgetType::Type>&);
// ProcessGameEvent
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FBindableDynEvent_CsUserWidget_Override_ProcessGameEvent, const uint8&, GameEvent);

#define CS_WIDGET_DEFINE_TYPE(TYPE)	Type = ECsWidgetType::TYPE; \
									Type_Script = (uint8)Type; \
									WidgetType_MAX = ECsWidgetType::ECsWidgetType_MAX; \
									WidgetTypeToString = &ECsWidgetType::ToString; \
									StringToWidgetType = &ECsWidgetType::ToType;

// Enums
#pragma region

namespace ECsUserWidgetRoutine
{
	enum Type
	{
		ECsUserWidgetRoutine_MAX,
	};
}

namespace ECsUserWidgetRoutine
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		return Type::ECsUserWidgetRoutine_MAX;
	}
}

#define ECS_USER_WIDGET_ROUTINE_MAX (uint8)ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX
typedef ECsUserWidgetRoutine::Type TCsUserWidgetRoutine;

#pragma endregion Enums

// Structs
#pragma region

struct FCsWidget
{
public:
	FString Name;
	FString EditorName;
	FString Path;

	FString PathAndName;

	FCsPrimitiveType<ESlateVisibility> Visibility;
	
	virtual void Init(const FString &inName, const FString &inEditorName, const FString &inPath)
	{
		Name		= inName;
		EditorName  = inEditorName;
		Path		= inPath;
		PathAndName = Path + TEXT(".") + Name;
	}

	virtual void OnNativeTick(const float &InDeltaTime){}

	virtual void SetVisibility(const ESlateVisibility &Visible)
	{
		Visibility = Visible;
	}
};

struct FCsWidget_Bar : FCsWidget
{
public:
	TWeakObjectPtr<class UProgressBar> Bar;

	TCsFloat Percent;

public:
	FCsWidget_Bar()
	{
	}

	void Set(UProgressBar* inBar) 
	{ 
		Bar		   = inBar;
		Visibility = Bar->Visibility;
		Visibility.Clear();
		Percent = Bar->Percent;
		Percent.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UProgressBar* B = Get())
				B->SetVisibility(Visibility.Get());
		}
		if (Visibility != ESlateVisibility::Visible)
		{
			Visibility.Clear();
			Percent.Clear();
			return;
		}
		// Percent
		if (Percent.HasChanged())
		{
			if (UProgressBar* B = Get())
				B->SetPercent(Percent.Get());
		}
		Visibility.Clear();
		Percent.Clear();
	}

	void SetPercent(const float &inPercent)
	{
		Percent	= inPercent;
	}

	UProgressBar* Get() { return Bar.IsValid() ? Bar.Get() : nullptr; }
};

struct FCsWidget_Text : FCsWidget
{
public:
	TWeakObjectPtr<class UTextBlock> Text;

	FCsPrimitiveType<FString> String;
	FCsPrimitiveType<FLinearColor> Color;

public:
	FCsWidget_Text()
	{
	}

	void Set(UTextBlock* inText) 
	{ 
		Text	   = inText;
		Visibility = Text->Visibility;
		Visibility.Clear();
		String = Text->Text.ToString();
		String.Clear();
		Color = Text->ColorAndOpacity.GetSpecifiedColor();
		Color.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UTextBlock* T = Get())
				T->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			String.Clear();
			return;
		}
		// String
		if (String.HasChanged())
		{
			if (UTextBlock* T = Get())
				T->SetText(FText::FromString(String.Get()));
		}
		// Color
		if (Color.HasChanged())
		{
			if (UTextBlock* T = Get())
				T->SetColorAndOpacity(Color.Get());
		}
		Visibility.Clear();
		String.Clear();
		Color.Clear();
	}

	void SetString(const FString &inString)
	{
		String = inString;
	}

	void SetColorAndOpacity(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	UTextBlock* Get() { return Text.IsValid() ? Text.Get() : nullptr; }
};

struct FCsWidget_Image : FCsWidget
{
public:
	TWeakObjectPtr<class UImage> Image;

	FCsPrimitiveType<FSlateColor> Tint;
	FCsPrimitiveType<FLinearColor> Color;

public:
	FCsWidget_Image()
	{
	}

	void Set(UImage* inImage) 
	{ 
		Image      = inImage;
		Visibility = Image->Visibility;
		Visibility.Clear();
		Tint  = Image->Brush.TintColor;
		Tint.Clear();
		Color = Image->ColorAndOpacity;
		Color.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UImage* I = Get())
				I->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
		// Tint
		if (Tint.HasChanged())
		{
			if (UImage* I = Get())
				I->Brush.TintColor = Tint.Get();
		}
		// Color
		if (Color.HasChanged())
		{
			if (UImage* I = Get())
				I->SetColorAndOpacity(Color.Get());
		}
		Visibility.Clear();
		Tint.Clear();
		Color.Clear();
	}

	void SetTint(const FSlateColor &inTint)
	{
		Tint = inTint;
	}

	void SetColorAndOpacity(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	void SetOpacity(const float &Alpha)
	{
		FLinearColor C = Color.Get();
		C.A			   = Alpha;
		Color		   = C;
	}

	UImage* Get() { return Image.IsValid() ? Image.Get() : nullptr; }
};

struct FCsWidget_Button : FCsWidget
{
public:
	TWeakObjectPtr<class UButton> Button;

	FCsPrimitiveType<FLinearColor> Color;

public:
	FCsWidget_Button()
	{
	}

	void Set(class UButton* inButton)
	{
		Button     = inButton;
		Visibility = Button->Visibility;
		Visibility.Clear();
		Color  = Button->BackgroundColor;
		Color.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UButton* B = Get())
				B->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
		// Color
		if (Color.HasChanged())
		{
			if (UButton* B = Get())
				B->SetBackgroundColor(Color.Get());
		}
		Visibility.Clear();
		Color.Clear();
	}

	void SetBackgroundColor(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	UButton* Get() { return Button.IsValid() ? Button.Get() : nullptr; }
};

struct FCsWidget_CheckBox : FCsWidget
{
public:
	TWeakObjectPtr<class UCheckBox> CheckBox;

	FCsPrimitiveType<ECheckBoxState> State;

	void Set(class UCheckBox* inCheckBox)
	{
		CheckBox   = inCheckBox;
		Visibility = CheckBox->Visibility;
		Visibility.Clear();
		State = CheckBox->GetCheckedState();
		State.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UCheckBox* C = Get())
				C->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
		// CheckBoxState
		if (State.HasChanged())
		{
			if (UCheckBox* C = Get())
				C->SetCheckedState(State.Get());
		}
		Visibility.Clear();
		State.Clear();
	}

	void SetCheckState(const ECheckBoxState &inState)
	{
		State = inState;
	}

	UCheckBox* Get() { return CheckBox.IsValid() ? CheckBox.Get() : nullptr; }
};


struct FCsWidget_LabelAndCheckBox : FCsWidget
{
	FCsWidget_Text Label;
	FCsWidget_CheckBox CheckBox;

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			Label.SetVisibility(Visibility.Get());
			CheckBox.SetVisibility(Visibility.Get());
		}

		Label.OnNativeTick(InDeltaTime);
		CheckBox.OnNativeTick(InDeltaTime);

		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
	}

	void SetCheckState(const bool &IsChecked)
	{
		CheckBox.SetCheckState(IsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}
};

struct FCsWidget_Slider : FCsWidget
{
public:
	TWeakObjectPtr<class USlider> Slider;

	TCsFloat Value;
	FCsPrimitiveType<FLinearColor> HandleColor;

	void Set(class USlider* inSlider)
	{
		Slider	   = inSlider;
		Visibility = Slider->Visibility;
		Visibility.Clear();
		Value = Slider->Value;
		Value.Clear();
		HandleColor = Slider->SliderHandleColor;
		HandleColor.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (USlider* S = Get())
				S->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
		// Value
		if (Value.HasChanged())
		{
			if (USlider* S = Get())
				S->SetValue(Value.Get());
		}
		// Color
		if (HandleColor.HasChanged())
		{
			if (USlider* S = Get())
				S->SetSliderHandleColor(HandleColor.Get());
		}
		Visibility.Clear();
		Value.Clear();
		HandleColor.Clear();
	}

	void SetValue(const float &inValue)
	{
		Value = inValue;
	}

	void SetHandleColor(const FLinearColor &Color)
	{
		HandleColor = Color;
	}

	USlider* Get() { return Slider.IsValid() ? Slider.Get() : nullptr; }
};

struct FCsWidget_EditableTextBox : FCsWidget
{
public:
	TWeakObjectPtr<class UEditableTextBox> TextBox;

	FCsPrimitiveType<FString> Text;
	FCsPrimitiveType<FLinearColor> Color;

	virtual void Set(class UEditableTextBox* inTextBox)
	{
		TextBox    = inTextBox;
		Visibility = TextBox->Visibility;
		Visibility.Clear();
		Text = TextBox->Text.ToString();
		Text.Clear();
		Color = TextBox->BackgroundColor_DEPRECATED;
		Color.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UEditableTextBox* T = Get())
				T->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
		// Text
		if (Text.HasChanged())
		{
			if (UEditableTextBox* T = Get())
				T->SetText(FText(FText::FromString(Text.Get())));
		}
		// Color
		if (Color.HasChanged())
		{
			if (UEditableTextBox* T = Get())
				T->BackgroundColor_DEPRECATED = Color.Get();
		}
		Visibility.Clear();
		Text.Clear();
		Color.Clear();
	}

	virtual void SetText(const FString &inText)
	{
		Text = inText;
	}

	void SetBackgroundColor(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	UEditableTextBox* Get() { return TextBox.IsValid() ? TextBox.Get() : nullptr; }
};

struct FCsWidget_EditableFloatBox : FCsWidget_EditableTextBox
{
public:
	TCsFloat Value;

	virtual void Set(class UEditableTextBox* inTextBox) override
	{
		TextBox = inTextBox;
		Visibility = TextBox->Visibility;
		Visibility.Clear();
		SetText(TextBox->Text.ToString());
		Text.Clear();
		Value.Clear();
		Color = TextBox->BackgroundColor_DEPRECATED;
		Color.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UEditableTextBox* T = Get())
				T->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
		// Text
		if (Text.HasChanged() || Value.HasChanged())
		{
			if (UEditableTextBox* T = Get())
				T->SetText(FText(FText::FromString(Text.Get())));
		}
		// Color
		if (Color.HasChanged())
		{
			if (UEditableTextBox* T = Get())
				T->BackgroundColor_DEPRECATED = Color.Get();
		}
		Visibility.Clear();
		Text.Clear();
		Value.Clear();
		Color.Clear();
	}

	virtual void SetText(const FString &inText)
	{
		const int32 Len = inText.Len();

		if (Len == CS_EMPTY)
			return;
		if (Len > 4)
			return;
		if (Text == inText)
			return;

		FString First = inText[0] == '.' ? TEXT(".") : TEXT("");
		FString Second = Len > 1 && inText[1] == '.' ? TEXT(".") : TEXT("");
		FString Third = Len > 2 && inText[2] == '.' ? TEXT(".") : TEXT("");
		FString Fourth = Len > 3 && inText[3] == '.' ? TEXT(".") : TEXT("");

		int32 FirstValue = INDEX_NONE;
		int32 SecondValue = INDEX_NONE;
		int32 ThirdValue = INDEX_NONE;
		int32 FourthValue = INDEX_NONE;

		const int32 Max = 10;

		for (int32 I = 0; I < Max; I++)
		{
			if (inText[0] == FString::FromInt(I)[0])
			{
				First	   = FString::FromInt(I);
				FirstValue = I;
				continue;
			}
			if (Len > 1 &&
				inText[1] == FString::FromInt(I)[0])
			{
				Second		= FString::FromInt(I);
				SecondValue = I;
				continue;
			}
			if (Len > 2 &&
				inText[2] == FString::FromInt(I)[0])
			{
				Third	   = FString::FromInt(I);
				ThirdValue = I;
				continue;
			}
			if (Len > 3 &&
				inText[3] == FString::FromInt(I)[0])
			{
				Fourth	    = FString::FromInt(I);
				FourthValue = I;
			}
		}

		// Blank -> Do Nothing
		if (First == TEXT(""))
			return;
		// .
		if (First == TEXT("."))
		{
			// .. or . -> Do Nothing
			if (Second == TEXT(".") || Second == TEXT(""))
				return;
			Text = First + Second;
			Value = (float)SecondValue / 10.0f;
			// .N. -> return .N
			if (Third == TEXT(".") || Third == TEXT(""))
				return;
			Text = Text.Get() + Third;
			Value = Value.Get() + ((float)ThirdValue / 100.0f);
			return;
		}
		// 0
		if (First == FString::FromInt(0))
		{
			// 0
			if (Second == TEXT(""))
			{
				Text = First;
				Value = 0.0f;
				return;
			}
			// 0.
			if (Second == TEXT("."))
			{
				// 0.. or 0.
				if (Third == TEXT(".") || Third == TEXT(""))
				{
					Text = First;
					Value = 0.0f;
					return;
				}
				Text = First + Second + Third;
				Value = ((float)ThirdValue / 10.0f);
				// 0.N. -> return 0.N
				if (Fourth == TEXT(".") || Fourth == TEXT(""))
					return;
				Text = Text.Get() + Fourth;
				Value = ((float)ThirdValue / 10.0f) + ((float)FourthValue / 100.0f);
				return;
			}
			Text = TEXT("1.0");
			Value = 1.0f;
			return;
		}
		// > 1
		Text = TEXT("1.0");
		Value = 1.0f;
	}

	void SetValue(const float &inValue)
	{
		Value = FMath::Clamp(inValue, 0.0f, 1.0f);

		if (Value == 0.0f)
		{
			Text = TEXT("0.0f");
		}
		else
		if (Value < 1.0f)
		{
			const int32 Tenths = FMath::FloorToInt(Value * 10.0f);
			int32 Hundredths = FMath::FloorToInt((Value * 100.0f) - 10.0f);

			if (Hundredths < 0)
				Hundredths = 0;

			Value = ((float)Tenths / 10.0f) + ((float)Hundredths / 100.0f);
			Text = TEXT("0.") + FString::FromInt(Tenths);
			Text = Hundredths > 0 ? Text.Get() + FString::FromInt(Hundredths) : Text.Get();
		}
		else
		{
			Text = TEXT("1.0");
		}
	}
};

struct FCsWidget_SliderAndEditableFloatBox : FCsWidget
{
	FCsWidget_Slider Slider;
	FCsWidget_EditableFloatBox FloatBox;

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			Slider.SetVisibility(Visibility.Get());
			FloatBox.SetVisibility(Visibility.Get());
		}

		Slider.OnNativeTick(InDeltaTime);
		FloatBox.OnNativeTick(InDeltaTime);

		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
	}

	void SetValue(const float &inValue)
	{
		Slider.SetValue(inValue);
		FloatBox.SetValue(inValue);
	}
};

struct FCsWidget_LabelAndSliderAndEditableFloatBox : FCsWidget
{
	FCsWidget_Text Label;
	FCsWidget_Slider Slider;
	FCsWidget_EditableFloatBox FloatBox;

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			Label.SetVisibility(Visibility.Get());
			Slider.SetVisibility(Visibility.Get());
			FloatBox.SetVisibility(Visibility.Get());
		}

		Label.OnNativeTick(InDeltaTime);
		Slider.OnNativeTick(InDeltaTime);
		FloatBox.OnNativeTick(InDeltaTime);

		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
	}

	void SetValue(const float &inValue)
	{
		Slider.SetValue(inValue);
		FloatBox.SetValue(inValue);
	}

	void SetValue(const FText &Text)
	{
		FloatBox.SetText(Text.ToString());
		Slider.SetValue(FloatBox.Value.Get());
	}
};

struct FCsWidget_ButtonAndText : FCsWidget
{
	FCsWidget_Button Button;
	FCsWidget_Text Text;

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			Button.SetVisibility(Visibility.Get());
			Text.SetVisibility(Visibility.Get());
		}

		Button.OnNativeTick(InDeltaTime);
		Text.OnNativeTick(InDeltaTime);

		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
	}
};

struct FCsWidget_LabelAndButtonAndText : FCsWidget
{
	FCsWidget_Text Label;
	FCsWidget_Button Button;
	FCsWidget_Text Text;

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			Label.SetVisibility(Visibility.Get());
			Button.SetVisibility(Visibility.Get());
			Text.SetVisibility(Visibility.Get());
		}

		Label.OnNativeTick(InDeltaTime);
		Button.OnNativeTick(InDeltaTime);
		Text.OnNativeTick(InDeltaTime);

		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
		{
			Visibility.Clear();
			return;
		}
	}
};

struct FCsWidget_Loading
{
public:
	FCsWidget_Text Loading;
	FCsWidget_Text Processing;
	FCsWidget_Text Finished;
	FCsWidget_Bar Bar;
	FCsWidget_Text Total;

	FCsPrimitiveType<ESlateVisibility> Visibility;

	bool IsActive;
	bool IsShuttingDown;

	int32 TotalCount;
	int32 CurrentCount;

	float Megabytes;
	float Kilobytes;
	int32 Bytes;

	float Seconds;

	bool ShouldDisplayAnimateDots;
	float AnimateDotTime;
	uint8 AnimateDotCount;

	// Finished
	bool ShouldDisplayFinished;
	float FinishedTime;

	// Completed
	bool ShouldDisplayCompleted;
	float CompletedTime;

	FCsWidget_Loading()
	{
		IsActive	 = false;
		CurrentCount = 0;
	}

	void OnNativeTick(const float &InDeltaTime)
	{
		if (Visibility == ESlateVisibility::Visible)
		{
			OnNativeTick_AnimateDots(InDeltaTime);
			OnNativeTick_HandleFinished(InDeltaTime);
			OnNativeTick_HandleCompleted(InDeltaTime);
		}

		Loading.OnNativeTick(InDeltaTime);
		Processing.OnNativeTick(InDeltaTime);
		Finished.OnNativeTick(InDeltaTime);
		Bar.OnNativeTick(InDeltaTime);
		Total.OnNativeTick(InDeltaTime);

		Visibility.Clear();
	}

	void Activate()
	{
		IsActive	   = true;
		IsShuttingDown = false;

		SetVisibility(ESlateVisibility::Visible);

		Loading.SetString(TEXT("Loading ... "));
		Processing.SetString(TEXT(""));
		Finished.SetString(TEXT(""));
		Bar.SetPercent(0.0f);
		Total.SetString(TEXT("0 mb (0 kb, 0 bytes) 0 seconds"));

		ShouldDisplayAnimateDots = true;
	}

	void DeActivate()
	{
		IsShuttingDown = true;

		Loading.SetString(TEXT(""));
		Processing.SetString(TEXT(""));
		Finished.SetString(TEXT(""));
		Bar.SetPercent(0.0f);
		Total.SetString(TEXT(""));

		SetVisibility(ESlateVisibility::Hidden);

		TotalCount   = 0;
		CurrentCount = 0;

		Megabytes = 0.0f;
		Kilobytes = 0.0f;
		Bytes	  = 0;

		Seconds = 0.0f;

		ShouldDisplayAnimateDots = false;
		AnimateDotTime			 = 0.0f;
		AnimateDotCount			 = 0;

		ShouldDisplayFinished = false;
		FinishedTime		  = 0.0f;

		ShouldDisplayCompleted = false;
		CompletedTime		   = 0.0f;
	}

	void SetVisibility(const ESlateVisibility &inVisibility)
	{
		Visibility = inVisibility;

		Loading.SetVisibility(inVisibility);
		Processing.SetVisibility(inVisibility);
		Finished.SetVisibility(inVisibility);
		Bar.SetVisibility(inVisibility);
		Total.SetVisibility(inVisibility);
	}

	void SetTotalCount(const int32 &inTotalCount)
	{
		CurrentCount   = 0;
		TotalCount	   = inTotalCount;
		FString String = TEXT("Loading ... 0% (") + FString::FromInt(CurrentCount) + TEXT("/") + FString::FromInt(TotalCount) = TEXT(")");

		Loading.SetString(String);
	}

	void SetCurrentCount(const int32 &inCurrentCount)
	{
		CurrentCount			      = inCurrentCount;
		const FString Dots			  = GetDots();
		const float Percent			  = (float)CurrentCount / (float)TotalCount;
		const FString PercentAsString = UCsCommon::GetFloatAsStringWithPrecision(Percent, 2);
		const FString String		  = TEXT("Loading ") + Dots + TEXT(" ") + PercentAsString + TEXT("% (") + FString::FromInt(CurrentCount) + TEXT("/") + FString::FromInt(TotalCount) + TEXT(")");

		Loading.SetString(String);
		Bar.SetPercent(Percent);
	}

	void OnNativeTick_AnimateDots(const float &InDeltaTime)
	{
		if (!ShouldDisplayAnimateDots)
			return;

		const float AnimTime = 0.2f;
		AnimateDotTime += InDeltaTime;

		if (AnimateDotTime >= AnimTime)
		{
			AnimateDotCount++;

			const FString Dots			  = GetDots();
			const float Percent			  = (float)CurrentCount / (float)TotalCount;
			const FString PercentAsString = UCsCommon::GetFloatAsStringWithPrecision(Percent, 2);
			const FString String		  = TEXT("Loading ") + Dots + TEXT(" ") + PercentAsString + TEXT("% (") + FString::FromInt(CurrentCount) + TEXT("/") + FString::FromInt(TotalCount) + TEXT(")");

			Loading.SetString(String);

			AnimateDotTime = 0.0f;
		}
	}

	FString GetDots()
	{
		const uint8 MaxDots = 3;
		AnimateDotCount %= MaxDots;

		if (AnimateDotCount == 0)
			return TEXT(".  ");
		if (AnimateDotCount == 1)
			return TEXT(" . ");
		if (AnimateDotCount == 2)
			return TEXT("  .");
		return TEXT("...");
	}

	void SetProcessing(const FString &Reference)
	{
		Processing.SetString(TEXT("Processing: ") + Reference);
	}

	void SetFinished(const FString &Reference, const int32 &Count, const float &inMegabytes, const float &inKilobytes, const float &inBytes, const float &Time)
	{
		SetCurrentCount(Count);

		const FString MegabytesAsString = UCsCommon::GetFloatAsStringWithPrecision(inMegabytes, 2);
		const FString KilobytesAsString = UCsCommon::GetFloatAsStringWithPrecision(inKilobytes, 2);
		const FString SecondsAsString   = UCsCommon::GetFloatAsStringWithPrecision(Seconds, 2);
		const FString String = TEXT("Finished: ") + Reference + TEXT(" ") + MegabytesAsString + TEXT("mb (") + KilobytesAsString + TEXT(" kb ") + FString::FromInt(inBytes) + TEXT(" bytes) ") + SecondsAsString + TEXT(" seconds");

		Finished.SetString(String);

		FinishedTime = 0.0f;
		ShouldDisplayFinished = true;

		UpdateTotal(inMegabytes, inKilobytes, inBytes, Time);
	}

	void OnNativeTick_HandleFinished(const float &InDeltaTime)
	{
		if (!ShouldDisplayFinished)
			return;

		FinishedTime += InDeltaTime;
		const float DisplayTime = 1.0f;

		if (FinishedTime > DisplayTime)
		{
			Finished.SetString(TEXT(""));

			ShouldDisplayFinished = false;
		}
	}

	void UpdateTotal(const float &inMegabytes, const float &inKilobytes, const int32 &inBytes, const float &Time)
	{
		Megabytes += inMegabytes;
		Kilobytes += inKilobytes;
		Bytes += inBytes;

		Seconds += Time;

		const FString MegabytesAsString = UCsCommon::GetFloatAsStringWithPrecision(inMegabytes, 2);
		const FString KilobytesAsString = UCsCommon::GetFloatAsStringWithPrecision(inKilobytes, 2);
		const FString SecondsAsString   = UCsCommon::GetFloatAsStringWithPrecision(Seconds, 2);

		const FString String = MegabytesAsString + TEXT("mb (") + KilobytesAsString + TEXT(" kb ") + FString::FromInt(inBytes) + TEXT(" bytes) ") + SecondsAsString + TEXT(" seconds");

		Total.SetString(String);
	}

	void SetCompleted()
	{
		Loading.SetString(TEXT("Loading Finished"));
		Processing.SetString(TEXT(""));
		Finished.SetString(TEXT(""));

		ShouldDisplayAnimateDots = false;

		ShouldDisplayCompleted = true;
		CompletedTime = 0.0f;
	}

	void OnNativeTick_HandleCompleted(const float &InDeltaTime)
	{
		if (!ShouldDisplayCompleted)
			return;

		CompletedTime += InDeltaTime;
		const float DisplayTime = 1.0f;

		if (CompletedTime > DisplayTime)
			DeActivate();
	}
};

#pragma endregion Structs

UCLASS()
class CSCORE_API UCsUserWidget : public UUserWidget
{
	GENERATED_UCLASS_BODY()

public:

	virtual void Init();
	virtual void OnPostProcessInput(const float &DeltaTime);
	virtual void OnLastTick(const float &DeltaSeconds);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	FName ShortCode;

	TCsWidgetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	uint8 Type_Script;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnNativeTick OnNativeTick_ScriptEvent;

	UPROPERTY()
	bool HasNativeContructed;

	UPROPERTY()
	bool HasInitFinished;

	TWeakObjectPtr<AActor> MyOwner;

	UFUNCTION(BlueprintCallable, Category = "UI")
	AActor* GetMyOwner();

	UPROPERTY()
	int32 Focus;

	virtual void SetFocus(const ECsWidgetFocus &InFocus);
	virtual void SetFocus(const int32 &InFocus);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Show();
	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void Hide();

	TCsWidgetType WidgetType_MAX;

	TCsWidgetTypeToString WidgetTypeToString;
	TCsStringToWidgetType StringToWidgetType;

	TArray<TCsWidgetType> ChildWidgetTypes;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<UCsUserWidget*> ChildWidgets;

	TMap<TCsWidgetType, TArray<UCsUserWidget*>> ChildWidgetsMap;

	UPROPERTY(BlueprintReadWrite, Category = "UI")
	TArray<UCsUserWidget*> ActiveChildWidgets;

	TMap<TCsWidgetType, TArray<UCsUserWidget*>> ActiveChildWidgetsMap;

// Get
#pragma region

	virtual UCsUserWidget* GetChildWidget(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UCsUserWidget* GetChildWidget_Script(const uint8 &WidgetType);

	virtual UCsUserWidget* GetActiveChildWidget(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual UCsUserWidget* GetActiveChildWidget_Script(const uint8 &WidgetType);

#pragma endregion Get

	virtual void SetChildFocus(const TCsWidgetType &WidgetType, const int32 &InFocus);

// Open / Close Child
#pragma region

	virtual void OpenChild(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void OpenChild_Script(const uint8 &WidgetType);

	FBindableEvent_CsUserWidget_OnOpenChild OnOpenChild_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnOpenChild OnOpenChild_ScriptEvent;

	virtual bool IsChildOpened(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsChildOpened_Script(const uint8 &WidgetType);

	virtual void CloseChild(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void CloseChild_Script(const uint8 &WidgetType);

	FBindableEvent_CsUserWidget_OnCloseChild OnCloseChild_Event;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnCloseChild OnCloseChild_ScriptEvent;

	virtual void CloseAllChildrenExcept(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual void CloseAllChildrenExcept_Script(const uint8 &WidgetType);

	virtual bool IsChildClosed(const TCsWidgetType &WidgetType);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool IsChildClosed_Script(const uint8 &WidgetType);

#pragma endregion Open / Close Child

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

	static void RemoveRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

#pragma endregion Routines

	virtual bool ProcessGameEvent(const TCsGameEvent &GameEvent);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool ProcessGameEvent_Script(const uint8 &GameEvent);

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_Override_ProcessGameEvent Override_ProcessGameEvent_ScriptEvent;

	virtual bool ChildWidgets_ProcessGameEvent(const TCsGameEvent &GamEvent);

	UFUNCTION(BlueprintCallable, Category = "UI")
	virtual bool ChildWidgets_ProcessGameEvent_Script(const uint8 &GameEvent);
};