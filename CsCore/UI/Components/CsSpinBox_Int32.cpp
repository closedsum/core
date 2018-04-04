// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "UI/Components/CsSpinBox_Int32.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/Font.h"

#define LOCTEXT_NAMESPACE "UMG"

/////////////////////////////////////////////////////
// USpinBox

USpinBox_Int32::USpinBox_Int32(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	if (!IsRunningDedicatedServer())
	{
		static ConstructorHelpers::FObjectFinder<UFont> RobotoFontObj(TEXT("/Engine/EngineFonts/Roboto"));
		Font = FSlateFontInfo(RobotoFontObj.Object, 12, FName("Bold"));
	}

	// Grab other defaults from slate arguments.
	SSpinBox<int32>::FArguments Defaults;

	Value = Defaults._Value.Get();
	MinValue = Defaults._MinValue.Get().Get(0);
	MaxValue = Defaults._MaxValue.Get().Get(0);
	MinSliderValue = Defaults._MinSliderValue.Get().Get(0);
	MaxSliderValue = Defaults._MaxSliderValue.Get().Get(0);
	Delta = Defaults._Delta.Get();
	SliderExponent = Defaults._SliderExponent.Get();
	MinDesiredWidth = Defaults._MinDesiredWidth.Get();
	ClearKeyboardFocusOnCommit = Defaults._ClearKeyboardFocusOnCommit.Get();
	SelectAllTextOnCommit = Defaults._SelectAllTextOnCommit.Get();

	WidgetStyle = *Defaults._Style;
	ForegroundColor = FSlateColor(FLinearColor::Black);
}

void USpinBox_Int32::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	MySpinBox.Reset();
}

TSharedRef<SWidget> USpinBox_Int32::RebuildWidget()
{
	MySpinBox = SNew(SSpinBox<int32>)
	.Style(&WidgetStyle)
	.Font(Font)
	.ClearKeyboardFocusOnCommit(ClearKeyboardFocusOnCommit)
	.SelectAllTextOnCommit(SelectAllTextOnCommit)
	.OnValueChanged(BIND_UOBJECT_DELEGATE(FOnInt32ValueChanged, HandleOnValueChanged))
	.OnValueCommitted(BIND_UOBJECT_DELEGATE(FOnInt32ValueCommitted, HandleOnValueCommitted))
	.OnBeginSliderMovement(BIND_UOBJECT_DELEGATE(FSimpleDelegate, HandleOnBeginSliderMovement))
	.OnEndSliderMovement(BIND_UOBJECT_DELEGATE(FOnInt32ValueChanged, HandleOnEndSliderMovement))
	;
	
	return MySpinBox.ToSharedRef();
}

void USpinBox_Int32::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	MySpinBox->SetDelta(Delta);
	MySpinBox->SetSliderExponent(SliderExponent);
	MySpinBox->SetMinDesiredWidth(MinDesiredWidth);

	MySpinBox->SetForegroundColor(ForegroundColor);

	// Set optional values
	bOverride_MinValue ? SetMinValue(MinValue) : ClearMinValue();
	bOverride_MaxValue ? SetMaxValue(MaxValue) : ClearMaxValue();
	bOverride_MinSliderValue ? SetMinSliderValue(MinSliderValue) : ClearMinSliderValue();
	bOverride_MaxSliderValue ? SetMaxSliderValue(MaxSliderValue) : ClearMaxSliderValue();

	// Always set the value last so that the max/min values are taken into account.
	TAttribute<int32> ValueBinding = PROPERTY_BINDING(int32, Value);
	MySpinBox->SetValue(ValueBinding);
}

int32 USpinBox_Int32::GetValue() const
{
	if (MySpinBox.IsValid())
	{
		return MySpinBox->GetValue();
	}

	return Value;
}

void USpinBox_Int32::SetValue(const int32 &InValue)
{
	Value = InValue;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetValue(InValue);
	}
}

// MIN VALUE
int32 USpinBox_Int32::GetMinValue() const
{
	int32 ReturnVal = TNumericLimits<int32>::Lowest();

	if (MySpinBox.IsValid())
	{
		ReturnVal = MySpinBox->GetMinValue();
	}
	else if (bOverride_MinValue)
	{
		ReturnVal = MinValue;
	}

	return ReturnVal;
}

void USpinBox_Int32::SetMinValue(const int32 &InMinValue)
{
	bOverride_MinValue = true;
	MinValue = InMinValue;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMinValue(InMinValue);
	}
}

void USpinBox_Int32::ClearMinValue()
{
	bOverride_MinValue = false;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMinValue(TOptional<int32>());
	}
}

// MAX VALUE
int32 USpinBox_Int32::GetMaxValue() const
{
	int32 ReturnVal = TNumericLimits<int32>::Max();

	if (MySpinBox.IsValid())
	{
		ReturnVal = MySpinBox->GetMaxValue();
	}
	else if (bOverride_MaxValue)
	{
		ReturnVal = MaxValue;
	}

	return ReturnVal;
}

void USpinBox_Int32::SetMaxValue(const int32 &InMaxValue)
{
	bOverride_MaxValue = true;
	MaxValue = InMaxValue;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMaxValue(InMaxValue);
	}
}
void USpinBox_Int32::ClearMaxValue()
{
	bOverride_MaxValue = false;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMaxValue(TOptional<int32>());
	}
}

// MIN SLIDER VALUE
int32 USpinBox_Int32::GetMinSliderValue() const
{
	int32 ReturnVal = TNumericLimits<int32>::Min();

	if (MySpinBox.IsValid())
	{
		ReturnVal = MySpinBox->GetMinSliderValue();
	}
	else if (bOverride_MinSliderValue)
	{
		ReturnVal = MinSliderValue;
	}

	return ReturnVal;
}

void USpinBox_Int32::SetMinSliderValue(const int32 &InMinSliderValue)
{
	bOverride_MinSliderValue = true;
	MinSliderValue = InMinSliderValue;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMinSliderValue(InMinSliderValue);
	}
}

void USpinBox_Int32::ClearMinSliderValue()
{
	bOverride_MinSliderValue = false;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMinSliderValue(TOptional<int32>());
	}
}

// MAX SLIDER VALUE
int32 USpinBox_Int32::GetMaxSliderValue() const
{
	int32 ReturnVal = TNumericLimits<int32>::Max();

	if (MySpinBox.IsValid())
	{
		ReturnVal = MySpinBox->GetMaxSliderValue();
	}
	else if (bOverride_MaxSliderValue)
	{
		ReturnVal = MaxSliderValue;
	}

	return ReturnVal;
}

void USpinBox_Int32::SetMaxSliderValue(const int32 &InMaxSliderValue)
{
	bOverride_MaxSliderValue = true;
	MaxSliderValue = InMaxSliderValue;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMaxSliderValue(InMaxSliderValue);
	}
}

void USpinBox_Int32::ClearMaxSliderValue()
{
	bOverride_MaxSliderValue = false;
	if (MySpinBox.IsValid())
	{
		MySpinBox->SetMaxSliderValue(TOptional<int32>());
	}
}

void USpinBox_Int32::SetForegroundColor(const FSlateColor &InForegroundColor)
{
	ForegroundColor = InForegroundColor;
	if ( MySpinBox.IsValid() )
	{
		MySpinBox->SetForegroundColor(ForegroundColor);
	}
}

// Event handlers
void USpinBox_Int32::HandleOnValueChanged(int32 InValue)
{
	if ( !IsDesignTime() )
	{
		OnValueChanged.Broadcast(InValue);
	}
}

void USpinBox_Int32::HandleOnValueCommitted(int32 InValue, ETextCommit::Type CommitMethod)
{
	if ( !IsDesignTime() )
	{
		OnValueCommitted.Broadcast(InValue, CommitMethod);
	}
}

void USpinBox_Int32::HandleOnBeginSliderMovement()
{
	if ( !IsDesignTime() )
	{
		OnBeginSliderMovement.Broadcast();
	}
}

void USpinBox_Int32::HandleOnEndSliderMovement(int32 InValue)
{
	if ( !IsDesignTime() )
	{
		OnEndSliderMovement.Broadcast(InValue);
	}
}

void USpinBox_Int32::PostLoad()
{
	Super::PostLoad();

	if ( GetLinkerUE4Version() < VER_UE4_DEPRECATE_UMG_STYLE_ASSETS )
	{
		if ( Style_DEPRECATED != nullptr )
		{
			const FSpinBoxStyle* StylePtr = Style_DEPRECATED->GetStyle<FSpinBoxStyle>();
			if ( StylePtr != nullptr )
			{
				WidgetStyle = *StylePtr;
			}

			Style_DEPRECATED = nullptr;
		}
	}
}


#if WITH_EDITOR

const FText USpinBox_Int32::GetPaletteCategory()
{
	return LOCTEXT("Input", "Input");
}

#endif

/////////////////////////////////////////////////////

#undef LOCTEXT_NAMESPACE
