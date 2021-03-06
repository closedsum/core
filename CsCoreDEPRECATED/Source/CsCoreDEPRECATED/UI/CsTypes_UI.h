// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"
#include "Types/Property/Value/CsProperty_int32.h"
#include "Types/Property/Value/CsProperty_uint32.h"
#include "Types/Property/Value/CsProperty_float.h"
#include "Types/Property/Value/CsProperty_String.h"
#include "Types/Property/Value/CsProperty_LinearColor.h"
#include "Types/CsTypes_View.h"
#include "Types/CsTypes_Load.h"
#include "Types/CsTypes_Math.h"
#include "Managers/Pool/Payload/CsPooledObjectPayload.h"


#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Components/VerticalBox.h"
#include "Runtime/UMG/Public/Components/VerticalBoxSlot.h"
#include "Runtime/UMG/Public/Components/GridPanel.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Border.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/Slider.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"
#include "Runtime/UMG/Public/Components/ComboBoxString.h"
#include "Runtime/UMG/Public/Components/CheckBox.h"
#include "Runtime/UMG/Public/Components/SpinBox.h"
#include "UI/Components/CsSpinBox_Int32.h"

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

	// WidgetActorType
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWidgetActorType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWidgetActorType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWidgetActorType)

struct CSCOREDEPRECATED_API EMCsWidgetActorType : public TCsEnumStructMap<FECsWidgetActorType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWidgetActorType, FECsWidgetActorType, uint8)
};

#pragma endregion WidgetActorType

	// WidgetType
#pragma region

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FECsWidgetType : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsWidgetType)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsWidgetType)

struct CSCOREDEPRECATED_API EMCsWidgetType : public TCsEnumStructMap<FECsWidgetType, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsWidgetType, FECsWidgetType, uint8)
};

#pragma endregion WidgetType

	// SimpleWidgetType
#pragma region

UENUM(BlueprintType)
enum class ECsSimpleWidgetType : uint8
{
	Text					UMETA(DisplayName = "Text"),
	Float					UMETA(DisplayName = "Float"),
	Button					UMETA(DisplayName = "Button"),
	Bar						UMETA(DisplayName = "Bar"),
	ECsSimpleWidgetType_MAX	UMETA(Hidden),
};

struct CSCOREDEPRECATED_API EMCsSimpleWidgetType : public TCsEnumMap<ECsSimpleWidgetType>
{
	CS_ENUM_MAP_BODY(EMCsSimpleWidgetType, ECsSimpleWidgetType)
};

namespace NCsSimpleWidgetType
{
	namespace Ref
	{
		typedef ECsSimpleWidgetType Type;

		extern CSCOREDEPRECATED_API const Type Text;
		extern CSCOREDEPRECATED_API const Type Float;
		extern CSCOREDEPRECATED_API const Type Button;
		extern CSCOREDEPRECATED_API const Type Bar;
		extern CSCOREDEPRECATED_API const Type ECsSimpleWidgetType_MAX;
	}
}

#pragma endregion SimpleWidgetType

	// FCsWidgetActorInfo
#pragma region 

class UBlueprint;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsWidgetActorInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TSoftObjectPtr<UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector2D DrawSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (InlineEditConditionToggle))
	bool bMinDrawDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (editcondition = "bMinDrawDistance"))
	FCsDrawDistance MinDrawDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool ScaleByDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DistanceProjectedOutFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FCsRotatorFlag LockAxes;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (InlineEditConditionToggle))
	bool bMovementFunction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (editcondition = "bMovementFunction"))
	FCsParametricFunction MovementFunction;

private:
	UPROPERTY(Transient)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:
	FCsWidgetActorInfo() :
		Blueprint_LoadFlags(0),
		LifeTime(0.0f),
		bMinDrawDistance(false),
		MinDrawDistance(),
		ScaleByDistance(false),
		FollowCamera(false),
		DistanceProjectedOutFromCamera(0.0f),
		LookAtCamera(false),
		LockAxes(),
		bMovementFunction(false),
		MovementFunction(),
		Blueprint_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::UI);

		DrawSize = FVector2D(100.0f, 100.0f);
		Transform = FTransform::Identity;
	}
	~FCsWidgetActorInfo(){}

	FORCEINLINE FCsWidgetActorInfo& operator=(const FCsWidgetActorInfo& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		LifeTime = B.LifeTime;
		DrawSize = B.DrawSize;
		bMinDrawDistance = B.bMinDrawDistance;
		MinDrawDistance = B.MinDrawDistance;
		ScaleByDistance = B.ScaleByDistance;
		Transform = B.Transform;
		FollowCamera = B.FollowCamera;
		DistanceProjectedOutFromCamera = B.DistanceProjectedOutFromCamera;
		LookAtCamera = B.LookAtCamera;
		LockAxes = B.LockAxes;
		bMovementFunction = B.bMovementFunction;
		MovementFunction = B.MovementFunction;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsWidgetActorInfo& B) const
	{
		return	Blueprint == B.Blueprint &&
				Blueprint_LoadFlags == B.Blueprint_LoadFlags &&
				Blueprint_Internal == B.Blueprint_Internal &&
				LifeTime == B.LifeTime &&
				DrawSize == B.DrawSize &&
				bMinDrawDistance == B.bMinDrawDistance &&
				MinDrawDistance == B.MinDrawDistance &&
				ScaleByDistance == B.ScaleByDistance &&
				FollowCamera == B.FollowCamera &&
				DistanceProjectedOutFromCamera == B.DistanceProjectedOutFromCamera &&
				LookAtCamera == B.LookAtCamera &&
				LockAxes == B.LockAxes &&
				bMovementFunction == B.bMovementFunction &&
				MovementFunction == B.MovementFunction;
	}

	FORCEINLINE bool operator!=(const FCsWidgetActorInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}
};

// PostEditChangeProperty FCsWidgetActorInfo
#define CS_PECP_FCS_WIDGET_ACTOR_INFO(e, PropertyName, MemberName)	if (UStructProperty* StructProperty = Cast<UStructProperty>(e.MemberProperty)) \
																	{ \
																		if (StructProperty->Struct == FCsWidgetActorInfo::StaticStruct()) \
																		{ \
																			if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDrawDistance, Distance)) \
																			{ \
																				MemberName.Square(); \
																			} \
																		} \
																	}

#pragma endregion FCsWidgetActorInfo

	// FCsWidgetComponentInfo
#pragma region

class UBlueprint;

USTRUCT(BlueprintType)
struct CSCOREDEPRECATED_API FCsWidgetComponentInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint")
	TSoftObjectPtr<UBlueprint> Blueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Blueprint", meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Blueprint_LoadFlags;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FVector2D DrawSize;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (InlineEditConditionToggle))
	bool bMinDrawDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (editcondition = "bMinDrawDistance"))
	FCsDrawDistance MinDrawDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool ScaleByDistance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowOwner;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FTransform Transform;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float DistanceProjectedOutFromCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	bool LookAtCamera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	FCsRotatorFlag LockAxes;

private:
	UPROPERTY(Transient)
	class UBlueprintGeneratedClass* Blueprint_Internal;

public:
	FCsWidgetComponentInfo() :
		Blueprint_LoadFlags(0),
		bMinDrawDistance(false),
		MinDrawDistance(),
		ScaleByDistance(false),
		FollowOwner(false),
		FollowCamera(false),
		DistanceProjectedOutFromCamera(0.0f),
		LookAtCamera(false),
		LockAxes(),
		Blueprint_Internal(nullptr)
	{
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::Game);
		CS_SET_BLUEPRINT_BITFLAG(Blueprint_LoadFlags, ECsLoadFlags::UI);

		DrawSize = FVector2D(100.0f, 100.0f);
		Transform = FTransform::Identity;
	}
	~FCsWidgetComponentInfo(){}

	FORCEINLINE FCsWidgetComponentInfo& operator=(const FCsWidgetComponentInfo& B)
	{
		Blueprint = B.Blueprint;
		Blueprint_LoadFlags = B.Blueprint_LoadFlags;
		Blueprint_Internal = B.Blueprint_Internal;
		DrawSize = B.DrawSize;
		bMinDrawDistance = B.bMinDrawDistance;
		MinDrawDistance = B.MinDrawDistance;
		ScaleByDistance = B.ScaleByDistance;
		FollowOwner = B.FollowOwner;
		Transform = B.Transform;
		FollowCamera = B.FollowCamera;
		DistanceProjectedOutFromCamera = B.DistanceProjectedOutFromCamera;
		LookAtCamera = B.LookAtCamera;
		LockAxes = B.LockAxes;
		return *this;
	}

	FORCEINLINE bool operator==(const FCsWidgetComponentInfo& B) const
	{
		return	Blueprint == B.Blueprint &&
				Blueprint_LoadFlags == B.Blueprint_LoadFlags &&
				Blueprint_Internal == B.Blueprint_Internal &&
				DrawSize == B.DrawSize &&
				bMinDrawDistance == B.bMinDrawDistance &&
				MinDrawDistance == B.MinDrawDistance &&
				ScaleByDistance == B.ScaleByDistance &&
				FollowOwner == B.FollowOwner &&
				FollowCamera == B.FollowCamera &&
				DistanceProjectedOutFromCamera == B.DistanceProjectedOutFromCamera &&
				LookAtCamera == B.LookAtCamera &&
				LockAxes == B.LockAxes;
	}

	FORCEINLINE bool operator!=(const FCsWidgetComponentInfo& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE UBlueprintGeneratedClass* Get() const
	{
		return Blueprint_Internal;
	}
};

// PostEditChangeProperty FCsWidgetComponentInfo
#define CS_PECP_FCS_WIDGET_COMPONENT_INFO(e, PropertyName, MemberName)	if (UStructProperty* StructProperty = Cast<UStructProperty>(e.MemberProperty)) \
																		{ \
																			if (StructProperty->Struct == FCsWidgetComponentInfo::StaticStruct()) \
																			{ \
																				if (PropertyName == GET_MEMBER_NAME_CHECKED(FCsDrawDistance, Distance)) \
																				{ \
																					MemberName.Square(); \
																				} \
																			} \
																		}

#pragma endregion FCsWidgetComponentInfo

	// HorizTextAligment
#pragma region

struct CSCOREDEPRECATED_API EMHorizTextAligment : public TCsEnumMap<EHorizTextAligment>
{
	CS_ENUM_MAP_BODY(EMHorizTextAligment, EHorizTextAligment)
};

namespace ECsHorizTextAligment
{
	namespace Ref
	{
		typedef EHorizTextAligment Type;

		extern CSCOREDEPRECATED_API const Type EHTA_Left;
		extern CSCOREDEPRECATED_API const Type EHTA_Center;
		extern CSCOREDEPRECATED_API const Type EHTA_Right;
	}
}

#pragma endregion HorizTextAligment

	// VerticalTextAligment
#pragma region

struct CSCOREDEPRECATED_API EMVerticalTextAligment : public TCsEnumMap<EVerticalTextAligment>
{
	CS_ENUM_MAP_BODY(EMVerticalTextAligment, EVerticalTextAligment)
};

namespace ECsVerticalTextAligment
{
	namespace Ref
	{
		typedef EVerticalTextAligment Type;

		extern CSCOREDEPRECATED_API const Type EVRTA_TextTop;
		extern CSCOREDEPRECATED_API const Type EVRTA_TextCenter;
		extern CSCOREDEPRECATED_API const Type EVRTA_TextBottom;
		extern CSCOREDEPRECATED_API const Type EVRTA_QuadTop;
	}
}

#pragma endregion VerticalTextAligment

	// ButtonState
#pragma region

UENUM(BlueprintType)
enum class ECsButtonState : uint8
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

struct CSCOREDEPRECATED_API EMCsButtonState : public TCsEnumMap<ECsButtonState>
{
	CS_ENUM_MAP_BODY(EMCsButtonState, ECsButtonState)
};

namespace NCsButtonState
{
	namespace Ref
	{
		typedef ECsButtonState Type;

		extern CSCOREDEPRECATED_API const Type None;
		extern CSCOREDEPRECATED_API const Type FirstHover;
		extern CSCOREDEPRECATED_API const Type Hover;
		extern CSCOREDEPRECATED_API const Type FirstUnHover;
		extern CSCOREDEPRECATED_API const Type FirstPressed;
		extern CSCOREDEPRECATED_API const Type Pressed;
		extern CSCOREDEPRECATED_API const Type FirstReleased;
		extern CSCOREDEPRECATED_API const Type ECsButtonState_MAX;
	}
}

#define ECS_BUTTON_STATE_MAX (uint8)ECsButtonState::ECsButtonState_MAX

#pragma endregion ButtonState

#pragma endregion UI

// Property
#pragma region

	// SlateVisibility
#pragma region

struct CSCOREDEPRECATED_API TCsProperty_ESlateVisibility : public TCsProperty<ESlateVisibility>
{
public:

	TCsProperty_ESlateVisibility()
	{
		DefaultValue = ESlateVisibility::Hidden;
	}
	~TCsProperty_ESlateVisibility() {}

	TCsProperty_ESlateVisibility& operator=(const ESlateVisibility& B)
	{
		Value = B;
		Resolve();
		return *this;
	}

	FORCEINLINE friend bool operator==(const ESlateVisibility &Lhs, const TCsProperty_ESlateVisibility &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_ESlateVisibility &Lhs, const ESlateVisibility &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const ESlateVisibility &Lhs, const TCsProperty_ESlateVisibility &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_ESlateVisibility &Lhs, const ESlateVisibility &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef TCsProperty_ESlateVisibility TCsESlateVisibility;

#pragma endregion SlateVisibility

	// SlateColor
#pragma region

struct CSCOREDEPRECATED_API TCsProperty_FSlateColor : public TCsProperty<FSlateColor>
{
public:

	TCsProperty_FSlateColor()
	{
		DefaultValue = FSlateColor();
	}
	~TCsProperty_FSlateColor() {}

	TCsProperty_FSlateColor& operator=(const FSlateColor& B)
	{
		Value = B;
		Resolve();
		return *this;
	}

	FORCEINLINE friend bool operator==(const FSlateColor &Lhs, const TCsProperty_FSlateColor &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_FSlateColor &Lhs, const FSlateColor &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const FSlateColor &Lhs, const TCsProperty_FSlateColor &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_FSlateColor &Lhs, const FSlateColor &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef TCsProperty_FSlateColor TCsFSlateColor;

#pragma endregion SlateColor

	// CheckBoxState
#pragma region

struct CSCOREDEPRECATED_API TCsProperty_ECheckBoxState : public TCsProperty<ECheckBoxState>
{
public:

	TCsProperty_ECheckBoxState()
	{
		DefaultValue = ECheckBoxState::Unchecked;
	}
	~TCsProperty_ECheckBoxState() {}

	TCsProperty_ECheckBoxState& operator=(const ECheckBoxState& B)
	{
		Value = B;
		Resolve();
		return *this;
	}

	FORCEINLINE friend bool operator==(const ECheckBoxState &Lhs, const TCsProperty_ECheckBoxState &Rhs)
	{
		return Lhs == Rhs.Value;
	}

	FORCEINLINE friend bool operator==(const TCsProperty_ECheckBoxState &Lhs, const ECheckBoxState &Rhs)
	{
		return Lhs.Value == Rhs;
	}

	FORCEINLINE friend bool operator!=(const ECheckBoxState &Lhs, const TCsProperty_ECheckBoxState &Rhs)
	{
		return !(Lhs == Rhs);
	}

	FORCEINLINE friend bool operator!=(const TCsProperty_ECheckBoxState &Lhs, const ECheckBoxState &Rhs)
	{
		return !(Lhs == Rhs);
	}
};

typedef TCsProperty_ECheckBoxState TCsECheckBoxState;

#pragma endregion CheckBoxState

#pragma endregion Property

// Structs
#pragma region

	// FCsWidget
#pragma region

struct CSCOREDEPRECATED_API FCsWidget
{
public:
	FString Name;
	FString EditorName;
	FString Path;

	FString PathAndName;

	TCsESlateVisibility Visibility;

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
	virtual void SetIsEnabled(const bool &InIsEnabled){}

	FORCEINLINE virtual void SetVisibility(const ESlateVisibility &Visible)
	{
		Visibility = Visible;
	}
};

#pragma endregion FCsWidget

	// FCsWidget_Bar
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Bar : public FCsWidget
{
public:
	TWeakObjectPtr<class UProgressBar> Bar;

	TCsFloat Percent;
	TCsFLinearColor Color;

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
		Color = Bar->FillColorAndOpacity;
		Color.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UProgressBar* B = Get())
				B->SetVisibility(Visibility.Get());
		}
		if (Visibility == ESlateVisibility::Collapsed ||
			Visibility == ESlateVisibility::Hidden)
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
		// Color
		if (Color.HasChanged())
		{
			if (UProgressBar* B = Get())
				B->SetFillColorAndOpacity(Color.Get());
		}
		Visibility.Clear();
		Percent.Clear();
		Color.Clear();
	}

	FORCEINLINE void SetPercent(const float &inPercent)
	{
		Percent = inPercent;
	}

	FORCEINLINE void SetColor(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	FORCEINLINE UProgressBar* Get() { return Bar.IsValid() ? Bar.Get() : nullptr; }
};

#pragma endregion FCsWidget_Bar

	// FCsWidget_Text
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Text : public FCsWidget
{
public:
	TWeakObjectPtr<class UTextBlock> Text;

	TCsFString String;
	TCsFLinearColor Color;

public:
	FCsWidget_Text(){}
	~FCsWidget_Text() {}

	virtual void Set(UTextBlock* inText)
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

	FORCEINLINE virtual void SetIsEnabled(const bool &InIsEnabled) override
	{
		if (UTextBlock* T = Get())
			T->SetIsEnabled(InIsEnabled);
	}

	FORCEINLINE virtual void SetString(const FString &inString)
	{
		String = inString;
	}

	FORCEINLINE void SetColorAndOpacity(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	FORCEINLINE UTextBlock* Get() { return Text.IsValid() ? Text.Get() : nullptr; }
};

#pragma endregion FCsWidget_Text

	// FCsWidget_Float
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Float : public FCsWidget_Text
{
	TCsFloat Value;

	FCsWidget_Float() {}
	~FCsWidget_Float() {}

	virtual void Set(UTextBlock* inText) override
	{
		Text = inText;
		Visibility = Text->Visibility;
		Visibility.Clear();
		String = Text->Text.ToString();
		String.Clear();
		Value = FCString::Atof(*(String.Get()));
		Value.Clear();
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
		// Value
		if (Value.HasChanged())
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

	FORCEINLINE virtual void SetString(const FString &inString) override
	{
		String = inString;

		if (String.HasChanged())
			Value = FCString::Atof(*inString);
	}

	FORCEINLINE void SetValue(const float &inValue)
	{
		Value = inValue;
		
		if (Value.HasChanged())
			String = FString::SanitizeFloat(inValue);
	}
};

#pragma endregion FCsWidget_Float

	// FCsWidget_Int32
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Int32 : public FCsWidget_Text
{
	TCsInt32 Value;

	FCsWidget_Int32() {}
	~FCsWidget_Int32() {}

	virtual void Set(UTextBlock* inText) override
	{
		Text = inText;
		Visibility = Text->Visibility;
		Visibility.Clear();
		String = Text->Text.ToString();
		String.Clear();
		Value = FCString::Atoi(*(String.Get()));
		Value.Clear();
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
		// Value
		if (Value.HasChanged())
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

	FORCEINLINE virtual void SetString(const FString &inString) override
	{
		String = inString;

		if (String.HasChanged())
			Value = FCString::Atoi(*inString);
	}

	FORCEINLINE void SetValue(const float &inValue)
	{
		Value = inValue;

		if (Value.HasChanged())
			String = FString::FromInt(inValue);
	}
};

#pragma endregion FCsWidget_Int32

	// FCsWidget_Image
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Image : public FCsWidget
{
public:
	TWeakObjectPtr<class UImage> Image;

	TCsFSlateColor Tint;
	TCsFLinearColor Color;

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

	FORCEINLINE void SetTint(const FSlateColor &inTint)
	{
		Tint = inTint;
	}

	FORCEINLINE void SetColorAndOpacity(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	FORCEINLINE void SetOpacity(const float &Alpha)
	{
		FLinearColor C = Color.Get();
		C.A = Alpha;
		Color = C;
	}

	FORCEINLINE UImage* Get() { return Image.IsValid() ? Image.Get() : nullptr; }
};

#pragma endregion FCsWidget_Image

	// FCsWidget_Button
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Button : public FCsWidget
{
public:
	TWeakObjectPtr<class UButton> Button;

	TCsFLinearColor Color;

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

	FORCEINLINE void SetBackgroundColor(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	FORCEINLINE UButton* Get() { return Button.IsValid() ? Button.Get() : nullptr; }
};

#pragma endregion FCsWidget_Button

	// FCsWidget_CheckBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_CheckBox : public FCsWidget
{
public:
	TWeakObjectPtr<class UCheckBox> CheckBox;

	TCsECheckBoxState State;

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

	FORCEINLINE void SetCheckState(const ECheckBoxState &inState)
	{
		State = inState;
	}

	FORCEINLINE UCheckBox* Get() { return CheckBox.IsValid() ? CheckBox.Get() : nullptr; }
};

#pragma endregion FCsWidget_CheckBox

	// FCsWidget_LabelAndCheckBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_LabelAndCheckBox : public FCsWidget
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

	FORCEINLINE void SetCheckState(const bool &IsChecked)
	{
		CheckBox.SetCheckState(IsChecked ? ECheckBoxState::Checked : ECheckBoxState::Unchecked);
	}
};

#pragma endregion FCsWidget_LabelAndCheckBox

	// FCsWidget_Slider
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Slider : public FCsWidget
{
public:
	TWeakObjectPtr<class USlider> Slider;

	TCsFloat Value;
	TCsFLinearColor HandleColor;

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

	FORCEINLINE void SetValue(const float &inValue)
	{
		Value = inValue;
	}

	FORCEINLINE void SetHandleColor(const FLinearColor &Color)
	{
		HandleColor = Color;
	}

	FORCEINLINE USlider* Get() { return Slider.IsValid() ? Slider.Get() : nullptr; }
};

#pragma endregion FCsWidget_Slider

	// FCsWidget_EditableTextBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_EditableTextBox : public FCsWidget
{
public:
	TWeakObjectPtr<class UEditableTextBox> TextBox;

	TCsFString Text;
	TCsFLinearColor Color;

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

	FORCEINLINE virtual void SetText(const FString &inText)
	{
		Text = inText;
	}

	FORCEINLINE void SetBackgroundColor(const FLinearColor &inColor)
	{
		Color = inColor;
	}

	FORCEINLINE UEditableTextBox* Get() { return TextBox.IsValid() ? TextBox.Get() : nullptr; }
};

#pragma endregion FCsWidget_EditableTextBox

	// FCsWidget_EditableFloatBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_EditableFloatBox : public FCsWidget_EditableTextBox
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

		for (int32 I = 0; I < Max; ++I)
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

#pragma endregion FCsWidget_EditableFloatBox

	// FCsWidget_SliderAndEditableFloatBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_SliderAndEditableFloatBox : public FCsWidget
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

	FORCEINLINE void SetValue(const float &inValue)
	{
		Slider.SetValue(inValue);
		FloatBox.SetValue(inValue);
	}
};

#pragma endregion FCsWidget_SliderAndEditableFloatBox

	// FCsWidget_LabelAndSliderAndEditableFloatBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_LabelAndSliderAndEditableFloatBox : public FCsWidget
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

	FORCEINLINE void SetValue(const float &inValue)
	{
		Slider.SetValue(inValue);
		FloatBox.SetValue(inValue);
	}

	FORCEINLINE void SetValue(const FText &Text)
	{
		FloatBox.SetText(Text.ToString());
		Slider.SetValue(FloatBox.Value.Get());
	}
};

#pragma endregion FCsWidget_LabelAndSliderAndEditableFloatBox

	// FCsWidget_SpinBox
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_SpinBox : public FCsWidget
{
public:
	TWeakObjectPtr<class USpinBox> SpinBox;

	TCsFloat Value;
	TCsFloat MinValue;
	TCsFloat MaxValue;

	FCsWidget_SpinBox() {}
	~FCsWidget_SpinBox() {}

	void Set(class USpinBox* inSpinBox)
	{
		SpinBox = inSpinBox;
		Visibility = SpinBox->Visibility;
		Visibility.Clear();
		Value = SpinBox->Value;
		Value.Clear();
		MinValue = SpinBox->GetMinValue();
		MinValue.Clear();
		MaxValue = SpinBox->GetMaxValue();
		MaxValue.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (USpinBox* S = Get())
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
			if (USpinBox* S = Get())
				S->SetValue(Value.Get());
		}
		// MinValue
		if (MinValue.HasChanged())
		{
			if (USpinBox* S = Get())
			{
				S->SetMinValue(MinValue.Get());
				S->SetMinSliderValue(MinValue.Get());
			}
		}
		// MaxValue
		if (MaxValue.HasChanged())
		{
			if (USpinBox* S = Get())
			{
				S->SetMaxValue(MaxValue.Get());
				S->SetMaxSliderValue(MaxValue.Get());
			}
		}
		Visibility.Clear();
		Value.Clear();
		MinValue.Clear();
		MaxValue.Clear();
	}

	FORCEINLINE void SetValue(const float &inValue)
	{
		Value = inValue;
	}

	FORCEINLINE void SetMinValue(const float &inMinValue)
	{
		MinValue = inMinValue;
	}

	FORCEINLINE void SetMaxValue(const float &inMaxValue)
	{
		MaxValue = inMaxValue;
	}

	FORCEINLINE USpinBox* Get() { return SpinBox.IsValid() ? SpinBox.Get() : nullptr; }
};

#pragma endregion FCsWidget_SpinBox

	// FCsWidget_SpinBox_int32
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_SpinBox_int32 : public FCsWidget
{
public:
	TWeakObjectPtr<class UCsSpinBox_Int32> SpinBox;

	TCsInt32 Value;
	TCsInt32 MinValue;
	TCsInt32 MaxValue;

	FCsWidget_SpinBox_int32() {}
	~FCsWidget_SpinBox_int32() {}

	void Set(class UCsSpinBox_Int32* inSpinBox)
	{
		SpinBox = inSpinBox;
		Visibility = SpinBox->Visibility;
		Visibility.Clear();
		Value = FMath::FloorToInt(SpinBox->Value);
		Value.Clear();
		MinValue = FMath::FloorToInt(SpinBox->GetMinValue());
		MinValue.Clear();
		MaxValue = FMath::FloorToInt(SpinBox->GetMaxValue());
		MaxValue.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UCsSpinBox_Int32* S = Get())
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
			if (UCsSpinBox_Int32* S = Get())
				S->SetValue(Value.Get());
		}
		// MinValue
		if (MinValue.HasChanged())
		{
			if (UCsSpinBox_Int32* S = Get())
			{
				S->SetMinValue(MinValue.Get());
				S->SetMinSliderValue(MinValue.Get());
			}
		}
		// MaxValue
		if (MaxValue.HasChanged())
		{
			if (UCsSpinBox_Int32* S = Get())
			{
				S->SetMaxValue(MaxValue.Get());
				S->SetMaxSliderValue(MaxValue.Get());
			}
		}
		Visibility.Clear();
		Value.Clear();
		MinValue.Clear();
		MaxValue.Clear();
	}

	FORCEINLINE void SetValue(const int32 &inValue)
	{
		Value = FMath::Clamp(inValue, MinValue.Get(), MaxValue.Get());
	}

	FORCEINLINE void IncrementValue()
	{
		++Value;
		Value = FMath::Clamp(Value.Get(), MinValue.Get(), MaxValue.Get());
	}

	FORCEINLINE void DecrementValue()
	{
		--Value;
		Value = FMath::Clamp(Value.Get(), MinValue.Get(), MaxValue.Get());
	}

	FORCEINLINE void SetMinValue(const int32 &inMinValue)
	{
		MinValue = inMinValue;
	}

	FORCEINLINE void SetMaxValue(const int32 &inMaxValue)
	{
		MaxValue = inMaxValue;
	}

	FORCEINLINE UCsSpinBox_Int32* Get() { return SpinBox.IsValid() ? SpinBox.Get() : nullptr; }
};

#pragma endregion FCsWidget_SpinBox_int32

	// FCsWidget_SpinBox_uint32
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_SpinBox_uint32 : public FCsWidget
{
public:
	TWeakObjectPtr<class UCsSpinBox_Int32> SpinBox;

	TCsUint32 Value;
	TCsUint32 MinValue;
	TCsUint32 MaxValue;

	FCsWidget_SpinBox_uint32() {}
	~FCsWidget_SpinBox_uint32() {}

	void Set(class UCsSpinBox_Int32* inSpinBox)
	{
		SpinBox = inSpinBox;
		Visibility = SpinBox->Visibility;
		Visibility.Clear();
		Value = FMath::Max(0, FMath::FloorToInt(SpinBox->Value));
		Value.Clear();
		MinValue = FMath::Max(0, FMath::FloorToInt(SpinBox->GetMinValue()));
		MinValue.Clear();
		MaxValue = FMath::Max(0, FMath::FloorToInt(SpinBox->GetMaxValue()));
		MaxValue.Clear();
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UCsSpinBox_Int32* S = Get())
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
			if (UCsSpinBox_Int32* S = Get())
				S->SetValue(Value.Get());
		}
		// MinValue
		if (MinValue.HasChanged())
		{
			if (UCsSpinBox_Int32* S = Get())
			{
				S->SetMinValue(MinValue.Get());
				S->SetMinSliderValue(MinValue.Get());
			}
		}
		// MaxValue
		if (MaxValue.HasChanged())
		{
			if (UCsSpinBox_Int32* S = Get())
			{
				S->SetMaxValue(MaxValue.Get());
				S->SetMaxSliderValue(MaxValue.Get());
			}
		}
		Visibility.Clear();
		Value.Clear();
		MinValue.Clear();
		MaxValue.Clear();
	}

	FORCEINLINE void SetValue(const uint32 &inValue)
	{
		Value = FMath::Clamp(inValue, MinValue.Get(), MaxValue.Get());
	}

	FORCEINLINE void IncrementValue()
	{
		if (Value == UINT32_MAX || Value >= MaxValue)
			return;
		++Value;
	}

	FORCEINLINE void DecrementValue()
	{
		if (Value == 0 || Value <= MinValue)
			return;
		--Value;
	}

	FORCEINLINE void SetMinValue(const uint32 &inMinValue)
	{
		MinValue = inMinValue;
	}

	FORCEINLINE void SetMaxValue(const uint32 &inMaxValue)
	{
		MaxValue = inMaxValue;
	}

	FORCEINLINE UCsSpinBox_Int32* Get() { return SpinBox.IsValid() ? SpinBox.Get() : nullptr; }
};

#pragma endregion FCsWidget_SpinBox_uint32

	// FCsWidget_ButtonAndText
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_ButtonAndText : public FCsWidget
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

#pragma endregion FCsWidget_ButtonAndText

	// FCsWidget_LabelAndButtonAndText
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_LabelAndButtonAndText : public FCsWidget
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

#pragma endregion FCsWidget_LabelAndButtonAndText

	// FCsWidget_Loading
#pragma region

struct CSCOREDEPRECATED_API FCsWidget_Loading
{
public:
	FCsWidget_Text Loading;
	FCsWidget_Text Processing;
	FCsWidget_Text Finished;
	FCsWidget_Bar Bar;
	FCsWidget_Text Total;

	TCsESlateVisibility Visibility;

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

#pragma endregion FCsWidget_Loading

#pragma endregion Structs

	// FCsWidgetPayload
#pragma region

struct CSCOREDEPRECATED_API FCsWidgetPayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	FString DisplayName;

	FVector2D Size;

	FIntPoint Offset;

	float LifeTime;

	FCsWidgetPayload() 
	{
		Reset();
	}
	~FCsWidgetPayload() {}

// ICsPooledObjectPayload
#pragma region
public:

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	UObject* GetInstigator() const
	{
		return Instigator;
	}

	UObject* GetOwner() const
	{
		return Owner;
	}

	UObject* GetParent() const
	{
		return Parent;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;

		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;


		DisplayName = NCsCached::Str::Empty;
		Size = FVector2D::ZeroVector;
		Offset = FIntPoint::ZeroValue;
		LifeTime = 0.0f;
	}

#pragma endregion ICsPooledObjectPayload
};

#pragma endregion FCsWidgetPayload

	// FCsWidgetActorPayload
#pragma region

struct CSCOREDEPRECATED_API FCsWidgetActorPayload : public ICsPooledObjectPayload
{
public:

	bool bAllocated;

	UObject* Instigator;

	UObject* Owner;

	UObject* Parent;

	TWeakObjectPtr<class UUserWidget> Widget;

	FVector2D Size;

	float LifeTime;

	bool bMinDrawDistance;

	FCsDrawDistance MinDrawDistance;

	bool ScaleByDistance;

	FTransform Transform;

	bool FollowCamera;

	float DistanceProjectedOutFromCamera;

	bool LookAtCamera;

	FCsRotatorFlag LockAxes;

	bool bMovementFunction;

	FCsParametricFunction MovementFunction;

	int32 Int32;

	float Float;

	FString String;

	FCsWidgetActorPayload()
	{
		Reset();
	}
	~FCsWidgetActorPayload() {}

// ICsPooledObjectPayload
#pragma region
public:

	const bool& IsAllocated() const
	{
		return bAllocated;
	}

	UObject* GetInstigator() const
	{
		return Instigator;
	}

	UObject* GetOwner() const
	{
		return Owner;
	}

	UObject* GetParent() const
	{
		return Parent;
	}

	void Allocate()
	{
		bAllocated = true;
	}

	void Reset()
	{
		bAllocated = false;

		Instigator = nullptr;
		Owner = nullptr;
		Parent = nullptr;

		Widget.Reset();
		Widget = nullptr;
		Size = FVector2D::ZeroVector;
		LifeTime = 0.0f;
		bMinDrawDistance = false;
		MinDrawDistance.Reset();
		ScaleByDistance = false;
		Transform = FTransform::Identity;
		FollowCamera = false;
		DistanceProjectedOutFromCamera = 0.0f;
		LookAtCamera = false;
		LockAxes.Reset();
		bMovementFunction = false;

		Int32 = 0;
		Float = 0.0f;
		String = NCsCached::Str::Empty;
	}

#pragma endregion ICsPooledObjectPayload

	FORCEINLINE class UUserWidget* GetWidget() { return Widget.IsValid() ? Widget.Get() : nullptr; }
	template<typename T>
	FORCEINLINE T* GetWidget() { return Cast<T>(GetWidget()); }
};

#pragma endregion FCsWidgetActorPayload