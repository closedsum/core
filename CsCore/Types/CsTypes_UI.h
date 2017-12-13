// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"

#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/CheckBox.h"

#include "Runtime/Engine/Classes/Components/TextRenderComponent.h"

#include "CsTypes_UI.generated.h"
#pragma once

// UI
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsWidgetFocus : uint8
{
	Mouse		UMETA(DisplayName = "Mouse"),
	Keyboard	UMETA(DisplayName = "Keyboard"),
	Controller	UMETA(DisplayName = "Controller"),
};

#define ECS_WIDGET_FOCUS_NONE 0
// 1 (2^0 Mouse) + 2 (2^1 Keyboard) + 4 (2^2 Controller)
#define ECS_WIDGET_FOCUS_ALL 7

namespace ECsWidgetActorType
{
	enum Type : uint8;
}

typedef ECsWidgetActorType::Type TCsWidgetActorType;

// WidgetActorTypeToString
typedef FString(*TCsWidgetActorTypeToString)(const TCsWidgetActorType&);
// StringToWidgetActorType
typedef TCsWidgetActorType(*TCsStringToWidgetActorType)(const FString&);

namespace ECsWidgetType
{
	enum Type : uint8;
}

typedef ECsWidgetType::Type TCsWidgetType;

// WidgetTypeToString
typedef FString(*TCsWidgetTypeToString)(const TCsWidgetType&);
// StringToWidgetType
typedef TCsWidgetType(*TCsStringToWidgetType)(const FString&);

USTRUCT(BlueprintType)
struct FCsWidgetActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TAssetPtr<class UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector2D DrawSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtCamera;

private:
	UPROPERTY(Transient)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:
	FCsWidgetActorInfo()
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::UI);

		DrawSize = FVector2D(100.0f, 100.0f);
		Transform = FTransform::Identity;
	}

	FCsWidgetActorInfo& operator=(const FCsWidgetActorInfo& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		DrawSize = B.DrawSize;
		Transform = B.Transform;
		FollowCamera = B.FollowCamera;
		LookAtCamera = B.LookAtCamera;
		return *this;
	}

	bool operator==(const FCsWidgetActorInfo& B) const
	{
		return Blueprint == B.Blueprint &&
			Blueprint_LoadFlags == B.Blueprint_LoadFlags &&
			Blueprint_Internal == B.Blueprint_Internal &&
			DrawSize == B.DrawSize &&
			FollowCamera == B.FollowCamera &&
			LookAtCamera == B.LookAtCamera;
	}

	bool operator!=(const FCsWidgetActorInfo& B) const
	{
		return !(*this == B);
	}

	UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}
};

namespace ECsHorizTextAligment
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString EHTA_Left = TCsString(TEXT("EHTA_Left"), TEXT("ehta_left"), TEXT("left"));
		const TCsString EHTA_Center = TCsString(TEXT("EHTA_Center"), TEXT("ehta_center"), TEXT("center"));
		const TCsString EHTA_Right = TCsString(TEXT("EHTA_Right"), TEXT("ehta_right"), TEXT("right"));
	}

	FORCEINLINE FString ToString(const EHorizTextAligment &EType)
	{
		if (EType == EHorizTextAligment::EHTA_Left) { return Str::EHTA_Left.Value; }
		if (EType == EHorizTextAligment::EHTA_Center) { return Str::EHTA_Center.Value; }
		if (EType == EHorizTextAligment::EHTA_Right) { return Str::EHTA_Right.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EHorizTextAligment ToType(const FString &String)
	{
		if (String == Str::EHTA_Left) { return EHorizTextAligment::EHTA_Left; }
		if (String == Str::EHTA_Center) { return EHorizTextAligment::EHTA_Center; }
		if (String == Str::EHTA_Right) { return EHorizTextAligment::EHTA_Right; }
		return EHorizTextAligment::EHTA_Left;
	}
}

namespace ECsVerticalTextAligment
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString EVRTA_TextTop = TCsString(TEXT("EVRTA_TextTop"), TEXT("evrta_texttop"), TEXT("text top"));
		const TCsString EVRTA_TextCenter = TCsString(TEXT("EVRTA_TextCenter"), TEXT("evrta_textcenter"), TEXT("text center"));
		const TCsString EVRTA_TextBottom = TCsString(TEXT("EVRTA_TextBottom"), TEXT("evrta_textbottom"), TEXT("text bottom"));
		const TCsString EVRTA_QuadTop = TCsString(TEXT("EVRTA_QuadTop"), TEXT("evrta_quadtop"), TEXT("quad top"));
	}

	FORCEINLINE FString ToString(const EVerticalTextAligment &EType)
	{
		if (EType == EVerticalTextAligment::EVRTA_TextTop) { return Str::EVRTA_TextTop.Value; }
		if (EType == EVerticalTextAligment::EVRTA_TextCenter) { return Str::EVRTA_TextCenter.Value; }
		if (EType == EVerticalTextAligment::EVRTA_TextBottom) { return Str::EVRTA_TextBottom.Value; }
		if (EType == EVerticalTextAligment::EVRTA_QuadTop) { return Str::EVRTA_QuadTop.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE EVerticalTextAligment ToType(const FString &String)
	{
		if (String == Str::EVRTA_TextTop) { return EVerticalTextAligment::EVRTA_TextTop; }
		if (String == Str::EVRTA_TextCenter) { return EVerticalTextAligment::EVRTA_TextCenter; }
		if (String == Str::EVRTA_TextBottom) { return EVerticalTextAligment::EVRTA_TextBottom; }
		if (String == Str::EVRTA_QuadTop) { return EVerticalTextAligment::EVRTA_QuadTop; }
		return EVerticalTextAligment::EVRTA_TextTop;
	}
}

UENUM(BlueprintType)
namespace ECsButtonState
{
	enum Type
	{
		None				UMETA(DisplayName = "None"),
		FirstHover			UMETA(DisplayName = "FirstHover"),
		Hover				UMETA(DisplayName = "Hover"),
		FirstUnHover		UMETA(DisplayName = "FirstUnHover"),
		FirstPressed		UMETA(DisplayName = "FirstPressed"),
		Pressed				UMETA(DisplayName = "Pressed"),
		FirstReleased		UMETA(DisplayName = "FirstReleased"),
		ECsButtonState_MAX	UMETA(Hidden),
	};
}

namespace ECsButtonState
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString None = TCsString(TEXT("None"), TEXT("none"), TEXT("none"));
		const TCsString FirstHover = TCsString(TEXT("FirstHover"), TEXT("firsthover"), TEXT("first hover"));
		const TCsString Hover = TCsString(TEXT("Hover"), TEXT("hover"), TEXT("hover"));
		const TCsString FirstUnHover = TCsString(TEXT("FirstUnHover"), TEXT("firstunhover"), TEXT("first unhover"));
		const TCsString FirstPressed = TCsString(TEXT("FirstPressed"), TEXT("firstpressed"), TEXT("first pressed"));
		const TCsString Pressed = TCsString(TEXT("Pressed"), TEXT("pressed"), TEXT("pressed"));
		const TCsString FirstReleased = TCsString(TEXT("FirstReleased"), TEXT("firstreleased"), TEXT("first released"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::None) { return Str::None.Value; }
		if (EType == Type::FirstHover) { return Str::FirstHover.Value; }
		if (EType == Type::Hover) { return Str::Hover.Value; }
		if (EType == Type::FirstUnHover) { return Str::FirstUnHover.Value; }
		if (EType == Type::FirstPressed) { return Str::FirstPressed.Value; }
		if (EType == Type::Pressed) { return Str::Pressed.Value; }
		if (EType == Type::FirstReleased) { return Str::FirstReleased.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::None) { return Type::None; }
		if (String == Str::FirstHover) { return Type::FirstHover; }
		if (String == Str::Hover) { return Type::Hover; }
		if (String == Str::FirstUnHover) { return Type::FirstUnHover; }
		if (String == Str::FirstPressed) { return Type::FirstPressed; }
		if (String == Str::Pressed) { return Type::Pressed; }
		if (String == Str::FirstReleased) { return Type::FirstReleased; }
		return Type::ECsButtonState_MAX;
	}
}

#define ECS_BUTTON_STATE_MAX (uint8)ECsButtonState::ECsButtonState_MAX
typedef TEnumAsByte<ECsButtonState::Type> TCsButtonState;

#pragma endregion UI

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

	FCsWidget() {}
	virtual ~FCsWidget() {}

	virtual void Init(const FString &inName, const FString &inEditorName, const FString &inPath)
	{
		Name = inName;
		EditorName = inEditorName;
		Path = inPath;
		PathAndName = Path + TEXT(".") + Name;
	}

	virtual void OnNativeTick(const float &InDeltaTime) {}

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

	~FCsWidget_Bar() {}

	void Set(UProgressBar* inBar)
	{
		Bar = inBar;
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
		Percent = inPercent;
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

	~FCsWidget_Text() {}

	void Set(UTextBlock* inText)
	{
		Text = inText;
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

struct FCsWidget_Float : FCsWidget_Text
{
	FCsWidget_Float() {}
	~FCsWidget_Float() {}
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

	~FCsWidget_Image() {}

	void Set(UImage* inImage)
	{
		Image = inImage;
		Visibility = Image->Visibility;
		Visibility.Clear();
		Tint = Image->Brush.TintColor;
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
		C.A = Alpha;
		Color = C;
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

	~FCsWidget_Button() {}

	void Set(class UButton* inButton)
	{
		Button = inButton;
		Visibility = Button->Visibility;
		Visibility.Clear();
		Color = Button->BackgroundColor;
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

	FCsWidget_CheckBox() {}
	~FCsWidget_CheckBox() {}

	void Set(class UCheckBox* inCheckBox)
	{
		CheckBox = inCheckBox;
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

	FCsWidget_LabelAndCheckBox() {}
	~FCsWidget_LabelAndCheckBox() {}

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

	FCsWidget_Slider() {}
	~FCsWidget_Slider() {}

	void Set(class USlider* inSlider)
	{
		Slider = inSlider;
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

	FCsWidget_EditableTextBox() {}
	~FCsWidget_EditableTextBox() {}

	virtual void Set(class UEditableTextBox* inTextBox)
	{
		TextBox = inTextBox;
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

	FCsWidget_EditableFloatBox() {}
	~FCsWidget_EditableFloatBox() {}

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
				First = FString::FromInt(I);
				FirstValue = I;
				continue;
			}
			if (Len > 1 &&
				inText[1] == FString::FromInt(I)[0])
			{
				Second = FString::FromInt(I);
				SecondValue = I;
				continue;
			}
			if (Len > 2 &&
				inText[2] == FString::FromInt(I)[0])
			{
				Third = FString::FromInt(I);
				ThirdValue = I;
				continue;
			}
			if (Len > 3 &&
				inText[3] == FString::FromInt(I)[0])
			{
				Fourth = FString::FromInt(I);
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

	FCsWidget_SliderAndEditableFloatBox() {}
	~FCsWidget_SliderAndEditableFloatBox() {}

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

	FCsWidget_LabelAndSliderAndEditableFloatBox() {}
	~FCsWidget_LabelAndSliderAndEditableFloatBox() {}

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

	FCsWidget_ButtonAndText() {}
	~FCsWidget_ButtonAndText() {}

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

	FCsWidget_LabelAndButtonAndText() {}
	~FCsWidget_LabelAndButtonAndText() {}

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
		IsActive = false;
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
		IsActive = true;
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

		TotalCount = 0;
		CurrentCount = 0;

		Megabytes = 0.0f;
		Kilobytes = 0.0f;
		Bytes = 0;

		Seconds = 0.0f;

		ShouldDisplayAnimateDots = false;
		AnimateDotTime = 0.0f;
		AnimateDotCount = 0;

		ShouldDisplayFinished = false;
		FinishedTime = 0.0f;

		ShouldDisplayCompleted = false;
		CompletedTime = 0.0f;
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
		CurrentCount = 0;
		TotalCount = inTotalCount;
		FString String = TEXT("Loading ... 0% (") + FString::FromInt(CurrentCount) + TEXT("/") + FString::FromInt(TotalCount) = TEXT(")");

		Loading.SetString(String);
	}

	FString GetFloatAsStringWithPrecision(float TheFloat, const uint8 Precision)
	{
		const TCHAR* TheDot = TEXT(".");

		FString FloatString = FString::SanitizeFloat(TheFloat);

		//No . ?
		if (!FloatString.Contains(TheDot))
		{
			return FloatString;
		}

		//Split
		FString LeftS;
		FString RightS;

		FloatString.Split(TheDot, &LeftS, &RightS);

		if (Precision == 0)
			return LeftS;

		//Add dot back to LeftS
		LeftS += TheDot;

		//Get the Single Number after the precision amount
		// so in .1273, get the 7
		FString RightSFirstTruncated = "";
		if (RightS.Len() - 1 >= Precision)
		{
			RightSFirstTruncated = RightS.Mid(Precision, 1);
		}

		//Truncate the RightS
		// 	.1273 becomes .12 with precision 2
		RightS = RightS.Left(Precision);

		//Round Up if There was any truncated portion
		if (RightSFirstTruncated != "")
		{
			if (FCString::Atod(*RightSFirstTruncated) >= 5)
			{
				//.1273 becomes .13
				RightS = FString::FromInt(FCString::Atod(*RightS) + 1);
			}
		}

		return LeftS + RightS;
	}

	void SetCurrentCount(const int32 &inCurrentCount)
	{
		CurrentCount = inCurrentCount;
		const FString Dots = GetDots();
		const float Percent = (float)CurrentCount / (float)TotalCount;
		const FString PercentAsString = GetFloatAsStringWithPrecision(Percent, 2);
		const FString String = TEXT("Loading ") + Dots + TEXT(" ") + PercentAsString + TEXT("% (") + FString::FromInt(CurrentCount) + TEXT("/") + FString::FromInt(TotalCount) + TEXT(")");

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

			const FString Dots = GetDots();
			const float Percent = (float)CurrentCount / (float)TotalCount;
			const FString PercentAsString = GetFloatAsStringWithPrecision(Percent, 2);
			const FString String = TEXT("Loading ") + Dots + TEXT(" ") + PercentAsString + TEXT("% (") + FString::FromInt(CurrentCount) + TEXT("/") + FString::FromInt(TotalCount) + TEXT(")");

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

		const FString MegabytesAsString = GetFloatAsStringWithPrecision(inMegabytes, 2);
		const FString KilobytesAsString = GetFloatAsStringWithPrecision(inKilobytes, 2);
		const FString SecondsAsString = GetFloatAsStringWithPrecision(Seconds, 2);
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

		const FString MegabytesAsString = GetFloatAsStringWithPrecision(inMegabytes, 2);
		const FString KilobytesAsString = GetFloatAsStringWithPrecision(inKilobytes, 2);
		const FString SecondsAsString = GetFloatAsStringWithPrecision(Seconds, 2);

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