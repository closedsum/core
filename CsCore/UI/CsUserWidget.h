// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/SlateWrapperTypes.h"
#include "Runtime/UMG/Public/Components/ProgressBar.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/Image.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "CsTypes.h"
#include "CsCommon.h"
#include "CsUserWidget.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FBindableDynEvent_CsUserWidget_OnNativeTick, const FGeometry&, MyGeometry, float, InDeltaTime);

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
	FCsPrimitiveType<ESlateVisibility> Visibility;

	virtual void OnNativeTick(const float &InDeltaTime)
	{
	}

	virtual void SetVisibility(const ESlateVisibility &Visible)
	{
		Visibility = Visible;
	}
};

struct FCsWidget_Bar : FCsWidget
{
public:
	TWeakObjectPtr<class UProgressBar> Bar;

	FCsPrimitiveType<float> Percent;

public:
	FCsWidget_Bar()
	{
	}

	void Set(UProgressBar* inBar) { Bar = inBar; }

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

	void Set(UTextBlock* inText) { Text = inText; }

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UTextBlock* T = Get())
				T->SetVisibility(Visibility.Get());
		}
		if (Visibility != ESlateVisibility::Visible)
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
		Image = inImage;
		Tint  = Image->Brush.TintColor;
		Color = Image->ColorAndOpacity;
	}

	virtual void OnNativeTick(const float &InDeltaTime) override
	{
		// Visibility
		if (Visibility.HasChanged())
		{
			if (UImage* I = Get())
				I->SetVisibility(Visibility.Get());
		}
		if (Visibility != ESlateVisibility::Visible)
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	FName ShortCode;

	TCsWidgetType Type;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "OO Default")
	uint8 Type_Script;

	UPROPERTY(BlueprintAssignable, Category = "UI")
	FBindableDynEvent_CsUserWidget_OnNativeTick OnNativeTick_ScriptEvent;

	bool HasInitFinished;

	virtual void Init();
	virtual void Show();
	virtual void Hide();

// Routines
#pragma region
public:

	static void AddRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

	static void RemoveRoutine(UObject* InWidget, struct FCsRoutine* Routine, const uint8 &InType);
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType);

#pragma endregion Routines
};