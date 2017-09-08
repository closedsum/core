// Copyright 2017 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "UI/CsUserWidget.h"
#include "CsTypes.h"
#include "CsWidget_Fullscreen.generated.h"

// Enums
#pragma region

namespace ECsWidgetFullscreenRoutine
{
	enum Type
	{
		FadeOut_Internal = ECsUserWidgetRoutine::ECsUserWidgetRoutine_MAX,
		FadeIn_Internal,
		ECsWidgetFullscreenRoutine_MAX,
	};
}

namespace ECsWidgetFullscreenRoutine
{
	typedef FCsPrimitiveType_MultiValue_FString_Enum_ThreeParams TCsString;

	namespace Str
	{
		const TCsString FadeOut_Internal = TCsString(TEXT("OnBoard_Internal"), TEXT("onboard_internal"), TEXT("onboard internal"));
		const TCsString FadeIn_Internal = TCsString(TEXT("LoadDataMapping_Internal"), TEXT("loaddatamapping_internal"), TEXT("load data mapping internal"));
	}

	FORCEINLINE FString ToString(const Type &EType)
	{
		if (EType == Type::FadeOut_Internal) { return Str::FadeOut_Internal.Value; }
		if (EType == Type::FadeIn_Internal) { return Str::FadeIn_Internal.Value; }
		return CS_INVALID_ENUM_TO_STRING;
	}

	FORCEINLINE Type ToType(const FString &String)
	{
		if (String == Str::FadeOut_Internal) { return Type::FadeOut_Internal; }
		if (String == Str::FadeIn_Internal) { return Type::FadeIn_Internal; }
		return Type::ECsWidgetFullscreenRoutine_MAX;
	}
}

#define ECS_WIDGET_FULLSCREEN_ROUTINE_MAX (uint8)ECsWidgetFullscreenRoutine::ECsWidgetFullscreenRoutine_MAX
typedef ECsWidgetFullscreenRoutine::Type TCsWidgetFullscreenRoutine;

#pragma endregion Enums

UCLASS()
class CSCORE_API UCsWidget_Fullscreen : public UCsUserWidget
{
	GENERATED_UCLASS_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	virtual void Init() override;

	UPROPERTY(meta = (BindWidget))
	UImage* Fullscreen_Image;

	FCsWidget_Image Fullscreen;

	// Routines
#pragma region
public:

	virtual bool AddRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;
	virtual bool RemoveRoutine_Internal(struct FCsRoutine* Routine, const uint8 &InType) override;

#pragma endregion Routines

// Fading
#pragma region
public:
	
	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void FadeOut(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color);
	struct FCsRoutine* FadeOut_Internal_Routine;

	UFUNCTION(BlueprintCallable, Category = "Widget")
	virtual void FadeIn(const TEnumAsByte<ECsEasingType::Type> &EasingType, const float &Start, const float &End, const float &Time, const FLinearColor &Color);
	struct FCsRoutine* FadeIn_Internal_Routine;

	static char Fade_Internal(struct FCsRoutine* r);

#pragma endregion Fading
};