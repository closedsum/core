// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Widget.h"
#include "CsUICore.h"

// Coroutine
#include "Coroutine/CsCoroutineScheduler.h"
// Library
#include "Coroutine/CsLibrary_CoroutineScheduler.h"
#include "Managers/Time/CsLibrary_Manager_Time.h"
	// Common
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_World.h"
#include "Player/CsLibrary_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Library/CsLibrary_Math.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
// Game
#include "Engine/GameInstance.h"
// Widget
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Animation/WidgetAnimation.h"
#include "Animation/UMGSequencePlayer.h"
// Viewport
#include "Blueprint/GameViewportSubsystem.h"
// Components
#include "Components/Widget.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/Border.h"
// Blueprint
#include "Engine/BlueprintGeneratedClass.h"
#include "Engine/BlueprintCore.h"
// World
#include "Engine/World.h"

using LogClassType = NCsUI::NCore::FLog;

CS_DEFINE_STATIC_LOG_LEVEL(NCsWidget::FLibrary, LogClassType::Warning);

namespace NCsWidget
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				const FString _C = TEXT("_C");
			}
		}
	}

	UUserWidget* FLibrary::CreateChecked(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName /*=NAME_None*/)
	{
		CS_IS_PENDING_KILL_CHECKED(Owner)
		CS_IS_SUBCLASS_OF_NULL_CHECKED(UserWidgetClass, UUserWidget)

		UUserWidget* Widget		 = nullptr;
		bool CastOwnerSuccessful = false;

		if (UWidget* W = Cast<UWidget>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*W, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (UWidgetTree* WT = Cast<UWidgetTree>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*WT, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (APlayerController* PC = Cast<APlayerController>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*PC, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (UGameInstance* GI = Cast<UGameInstance>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*GI, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (UWorld* World = Cast<UWorld>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*World, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}

		checkf(CastOwnerSuccessful, TEXT("%s: Owner: %s with Class: %s is NOT of type: UWidget, UWidgetTree, APlayerController, UGameInstance, or UWorld OR can NOT route to UWorld."), *Context, *(Owner->GetName()), *(Owner->GetClass()->GetName()));
		checkf(Widget, TEXT("%s: Failed to create widget of type: %s with Owner: %s with Class: %s."), *Context, *(UserWidgetClass->GetName()), *(Owner->GetName()), *(Owner->GetClass()->GetName()));
		return Widget;
	}

	UUserWidget* FLibrary::CreateSafe(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName /*=NAME_None*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		CS_IS_PTR_NULL_RET_NULL(Owner)
		CS_IS_SUBCLASS_OF_NULL_RET_NULL(UserWidgetClass, UUserWidget)

		UUserWidget* Widget		 = nullptr;
		bool CastOwnerSuccessful = false;

		if (UWidget* W = Cast<UWidget>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*W, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (UWidgetTree* WT = Cast<UWidgetTree>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*WT, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (APlayerController* PC = Cast<APlayerController>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*PC, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (UGameInstance* GI = Cast<UGameInstance>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*GI, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}
		else
		if (UWorld* World = Cast<UWorld>(Owner))
		{
			Widget = UUserWidget::CreateWidgetInstance(*World, UserWidgetClass, WidgetName);
			CastOwnerSuccessful = true;
		}

		if (!Widget)
		{
			if (!CastOwnerSuccessful)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Owner: %s with Class: %s is NOT of type: UWidget, UWidgetTree, APlayerController, UGameInstance, or UWorld."), *Context, *(Owner->GetName()), *(Owner->GetClass()->GetName())));
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to create widget of type: %s with Owner: %s with Class: %s."), *Context, *(UserWidgetClass->GetName()), *(Owner->GetName()), *(Owner->GetClass()->GetName())));
		}
		return Widget;
	}

	int32 FLibrary::GetZOrderChecked(const FString& Context, const UUserWidget* Widget)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		checkf(Widget->Slot, TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName()));

		const UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

		checkf(Slot, TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName()));

		return Slot->GetZOrder();
	}

	void FLibrary::SetZOrderChecked(const FString& Context, UUserWidget* Widget, const int32& ZOrder)
	{
		CS_IS_PTR_NULL_CHECKED(Widget)

		checkf(Widget->Slot, TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName()));

		UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

		checkf(Slot, TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName()));

		Slot->SetZOrder(ZOrder);
	}

	// Load
	#pragma region

	UClass* FLibrary::LoadChecked(const FString& Context, const FSoftObjectPath& Path)
	{
		UObject* O = CsObjectLibrary::LoadChecked(Context, Path);

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		checkf(BpGC, TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName()));

		//checkf(BpGC->ClassGeneratedBy, TEXT("%s: ClassGeneratedBy is NULL for Object: %s."), *Context, *(O->GetName()));

		UBlueprintCore* BpC = nullptr;//Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

		//checkf(BpC, TEXT("%s: Failed to cast Class: %s to UBlueprintCore."), *Context, *(BpGC->ClassGeneratedBy->GetName()));

		checkf(BpC->GeneratedClass, TEXT("%s: Failed to get GeneratedClass from Class: %s."), *Context, *(BpC->GetName()));

		return BpC->GeneratedClass;
	}

	UClass* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		UObject* O = CsObjectLibrary::SafeLoad(Context, Path, Log);

		if (!O)
			return nullptr;

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		if (!BpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName())));
			return nullptr;
		}
		return BpGC;

		/*if (!BpGC->ClassGeneratedBy)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ClassGeneratedBy is NULL for Object: %s."), *Context, *(O->GetName())));
			return nullptr;
		}

		UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

		if (!BpC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast Class: %s to UBlueprintCore."), *Context, *(BpGC->ClassGeneratedBy->GetName())));
			return nullptr;
		}

		if (!BpC->GeneratedClass)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GeneratedClass from Class: %s."), *Context, *(BpC->GetName())));
			return nullptr;
		}
		return BpC->GeneratedClass;*/
	}

	UClass* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		using namespace NCsWidget::NLibrary::NCached;

		checkf(Path.EndsWith(Str::_C), TEXT("%s: Path: %s does NOT end with '_C'."), *Context, *Path);

		UObject* O = CsObjectLibrary::LoadChecked(Context, Path);

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		checkf(BpGC, TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName()));

		//checkf(BpGC->ClassGeneratedBy, TEXT("%s: ClassGeneratedBy is NULL for Object: %s."), *Context, *(O->GetName()));

		UBlueprintCore* BpC = nullptr;//Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

		//checkf(BpC, TEXT("%s: Failed to cast Class: %s to UBlueprintCore."), *Context, *(BpGC->ClassGeneratedBy->GetName()));

		checkf(BpC->GeneratedClass, TEXT("%s: Failed to get GeneratedClass from Class: %s."), *Context, *(BpC->GetName()));

		return BpC->GeneratedClass;
	}

	UClass* FLibrary::SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		using namespace NCsWidget::NLibrary::NCached;

		FString ClassPath = Path;

		if (!ClassPath.EndsWith(Str::_C))
			ClassPath.Append(Str::_C);
			
		UObject* O = CsObjectLibrary::SafeLoad(Context, ClassPath, Log);

		if (!O)
			return nullptr;

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		if (!BpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName())));
			return nullptr;
		}
		return BpGC;

		/*if (!BpGC->ClassGeneratedBy)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: ClassGeneratedBy is NULL for Object: %s."), *Context, *(O->GetName())));
			return nullptr;
		}

		UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

		if (!BpC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast Class: %s to UBlueprintCore."), *Context, *(BpGC->ClassGeneratedBy->GetName())));
			return nullptr;
		}

		if (!BpC->GeneratedClass)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get GeneratedClass from Class: %s."), *Context, *(BpC->GetName())));
			return nullptr;
		}
		return BpC->GeneratedClass;*/
	}

	#pragma endregion Load

	// Get
	#pragma region
	
	UUserWidget* FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		return CsPropertyLibrary::GetObjectPropertyValueByPath<UUserWidget>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, TSoftClassPtr<UUserWidget>& OutSoftClassPtr, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftClassPropertyValueByPath<UUserWidget>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutSoftClassPtr			     = SoftObjectPtr.ToSoftObjectPath();
		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FSoftClassPath& OutSoftClassPath, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftClassPropertyValueByPath<UUserWidget>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutSoftClassPath			 = SoftObjectPtr.ToSoftObjectPath().ToString();
		return OutSuccess;
	}

	bool FLibrary::GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
	{
		FSoftObjectPtr SoftObjectPtr = CsPropertyLibrary::GetSoftClassPropertyValueByPath<UUserWidget>(Context, Object, Object->GetClass(), Path, OutSuccess, Log);
		OutPathAsString				 = SoftObjectPtr.ToString();
		return OutSuccess;
	}

	#pragma endregion Get

	void FLibrary::AddToScreenChecked(const FString& Context, const UObject* WorldContext, UWidget* Widget, ULocalPlayer* Player, const int32& ZOrder)
	{
		CS_IS_PENDING_KILL_CHECKED(WorldContext)
		CS_IS_PENDING_KILL_CHECKED(Widget)
		CS_IS_PENDING_KILL_CHECKED(Player)

		UWorld* World				= CsWorldLibrary::GetChecked(Context, WorldContext);
		UGameViewportSubsystem* GVS = UGameViewportSubsystem::Get(World);

		CS_IS_PTR_NULL_CHECKED(GVS)

		FGameViewportWidgetSlot Slot;
		Slot.ZOrder = ZOrder;

		GVS->AddWidgetForPlayer(Widget, Player, Slot);
	}
}

namespace NCsWidget
{
	namespace NRender
	{
		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		bool FLibrary::CanEaseChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)
			CS_IS_ENUM_VALID_CHECKED(EMCsEasingType, Easing)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Start, 0.0f)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(End, 0.0f)
			return true;
		}

		bool FLibrary::CanEase(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PTR_NULL(Widget)
			CS_IS_ENUM_VALID(EMCsEasingType, ECsEasingType, Easing)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Start, 0.0f)
			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(End, 0.0f)
			return true;
		}

		float FLibrary::GetPercentChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
		{
			check(CanEaseChecked(Context, Widget, Easing, Start, End, Alpha));
			return CsMathLibrary::Ease(Easing, Alpha, 0.0f, 1.0f, 1.0f);
		}

		void FLibrary::Opacity_EaseChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
		{
			const float Percent = GetPercentChecked(Context, Widget, Easing, Start, End, Alpha);

			Widget->SetRenderOpacity(Percent);
		}

		bool FLibrary::Opacity_SafeEase(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (!CanEase(Context, Widget, Easing, Start, End, Alpha, Log))
				return false;

			const float Percent = CsMathLibrary::Ease(Easing, Alpha, 0.0f, 1.0f, 1.0f);

			Widget->SetRenderOpacity(Percent);
			return true;
		}

		void FLibrary::Scale_EaseChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha)
		{
			const float Percent   = GetPercentChecked(Context, Widget, Easing, Start, End, Alpha);
			const FVector2d Scale = FMath::Lerp(Start, End, Alpha) * FVector2d(1.0f);

			Widget->SetRenderScale(Scale);
		}

		bool FLibrary::Scale_SafeEase(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Alpha, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			if (!CanEase(Context, Widget, Easing, Start, End, Alpha, Log))
				return false;
			const float Percent   = CsMathLibrary::Ease(Easing, Alpha, 0.0f, 1.0f, 1.0f);
			const FVector2d Scale = FMath::Lerp(Start, End, Alpha) * FVector2d(1.0f);

			Widget->SetRenderScale(Scale);
			return true;
		}

	// Anim
	#pragma region

	/*
		FCsRoutineHandle FLibrary::Scale_AnimChecked(const FString& Context, UUserWidget* Widget, const ECsEasingType& Easing, const float& Start, const float& End, const float& Duration)
		{

		}

		char FLibrary::Scale_Anim_Internal(FCsRoutine* R)
		{

		}
		*/

	#pragma endregion Anim
	}
}

namespace NCsWidget
{
	namespace NPosition
	{
		namespace NScreen
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeBySlot2d);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeBySlot2f);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeAbsoluteByCachedGeometry2d);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeAbsoluteByCachedGeometry2f);
					}
				}
			}

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			#define USING_NS_CACHED using namespace NCsWidget::NPosition::NScreen::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NPosition::NScreen::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName

			FVector2d FLibrary::GetBySlot2dChecked(const FString& Context, UWidget* Widget)
			{
				CS_IS_PENDING_KILL_CHECKED(Widget)

				checkf(Widget->Slot, TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName()));

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

				checkf(Slot, TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName()));
				checkf(Widget->GetVisibility() != ESlateVisibility::Collapsed, TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName()));
				return Slot->GetPosition();
			}

			FVector2f FLibrary::GetBySlot2fChecked(const FString& Context, UWidget* Widget)
			{
				return CsMathLibrary::Convert(GetBySlot2dChecked(Context, Widget));
			}

			FVector2d FLibrary::GetSafeBySlot2d(const FString& Context, UWidget* Widget, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (!Widget)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget is NULL."), *Context));
					return FVector2d(-1.0);
				}

				if (!Widget->Slot)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName())));
					return FVector2d(-1.0);
				}

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

				if (!Slot)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName())));
					return FVector2d(-1.0);
				}

				if (Widget->GetVisibility() == ESlateVisibility::Collapsed)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName())));
					return FVector2d(-1.0);
				}
				return Slot->GetPosition();
			}

			FVector2f FLibrary::GetSafeBySlot2f(const FString& Context, UWidget* Widget, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				return CsMathLibrary::Convert(GetSafeBySlot2d(Context, Widget, Log));
			}

			FVector2d FLibrary::GetSafeBySlot2d(UWidget* Widget)
			{
				SET_CONTEXT(GetSafeBySlot2d);

				return GetSafeBySlot2d(Context, Widget, nullptr);
			}

			FVector2f FLibrary::GetSafeBySlot2f(UWidget* Widget)
			{
				SET_CONTEXT(GetSafeBySlot2f);

				return GetSafeBySlot2f(Context, Widget, nullptr);
			}

			FVector2d FLibrary::GetAbsoluteByCachedGeometry2dChecked(const FString& Context, UWidget* Widget)
			{
				CS_IS_PENDING_KILL_CHECKED(Widget)

				checkf(Widget->GetVisibility() != ESlateVisibility::Collapsed, TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName()));
				checkf(Widget->GetVisibility() != ESlateVisibility::Hidden, TEXT("%s: %s's Visibility == ESlateVisibility::Hidden is NOT Valid when getting position."), *Context, *(Widget->GetName()));
				return Widget->GetCachedGeometry().GetAbsolutePosition();
			}

			FVector2f FLibrary::GetAbsoluteByCachedGeometry2fChecked(const FString& Context, UWidget* Widget)
			{
				return CsMathLibrary::Convert(GetAbsoluteByCachedGeometry2dChecked(Context, Widget));
			}

			FVector2d FLibrary::GetSafeAbsoluteByCachedGeometry2d(const FString& Context, UWidget* Widget, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (!Widget)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget is NULL."), *Context));
					return FVector2d(-1.0);
				}

				if (Widget->GetVisibility() == ESlateVisibility::Collapsed)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName())));
					return FVector2d(-1.0);
				}

				if (Widget->GetVisibility() == ESlateVisibility::Hidden)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s's Visibility == ESlateVisibility::Hidden is NOT Valid when getting position."), *Context, *(Widget->GetName())));
					return FVector2d(-1.0);
				}
				return Widget->GetCachedGeometry().GetAbsolutePosition();
			}

			FVector2f FLibrary::GetSafeAbsoluteByCachedGeometry2f(const FString& Context, UWidget* Widget, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				return CsMathLibrary::Convert(GetSafeAbsoluteByCachedGeometry2d(Context, Widget, Log));
			}

			FVector2d FLibrary::GetSafeAbsoluteByCachedGeometry2d(UWidget* Widget)
			{
				SET_CONTEXT(GetSafeAbsoluteByCachedGeometry2d);

				return GetSafeAbsoluteByCachedGeometry2d(Context, Widget, nullptr);
			}

			FVector2f FLibrary::GetSafeAbsoluteByCachedGeometry2f(UWidget* Widget)
			{
				SET_CONTEXT(GetSafeAbsoluteByCachedGeometry2f);

				return GetSafeAbsoluteByCachedGeometry2f(Context, Widget, nullptr);
			}

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
		}
	}
}

namespace NCsWidget
{
	namespace NPosition
	{
		namespace NViewport
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NViewport::FLibrary, GetSafeByCachedGeometry);
					}
				}
			}

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			#define USING_NS_CACHED using namespace NCsWidget::NPosition::NViewport::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NPosition::NViewport::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName

			void FLibrary::GetByCachedGeometryChecked(const FString& Context, UWidget* Widget, FVector2d& OutPixelPosition, FVector2d& OutViewportPosition)
			{
				const FVector2d AbsolutePosition = CsWidgetScreenPositionLibrary::GetAbsoluteByCachedGeometry2dChecked(Context, Widget);

				USlateBlueprintLibrary::AbsoluteToViewport(Widget->GetWorld(), AbsolutePosition, OutPixelPosition, OutViewportPosition);
			}

			void FLibrary::GetByCachedGeometryChecked(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition)
			{
				FVector2d PixelPosition;
				FVector2d ViewportPosition;
				GetByCachedGeometryChecked(Context, Widget, PixelPosition, ViewportPosition);

				OutPixelPosition	= CsMathLibrary::Convert(PixelPosition);
				OutViewportPosition = CsMathLibrary::Convert(ViewportPosition);
			}

			void FLibrary::GetSafeByCachedGeometry(const FString& Context, UWidget* Widget, FVector2d& OutPixelPosition, FVector2d& OutViewportPosition, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				const FVector2d AbsolutePosition = CsWidgetScreenPositionLibrary::GetSafeAbsoluteByCachedGeometry2d(Context, Widget, Log);

				if (AbsolutePosition == FVector2d(-1.0))
				{
					OutPixelPosition = FVector2d(-1.0f);
					OutViewportPosition = FVector2d(-1.0f);
					return;
				}
				USlateBlueprintLibrary::AbsoluteToViewport(Widget->GetWorld(), AbsolutePosition, OutPixelPosition, OutViewportPosition);
			}

			void FLibrary::GetSafeByCachedGeometry(const FString& Context, UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				FVector2d PixelPosition;
				FVector2d ViewportPosition;
				GetSafeByCachedGeometry(Context, Widget, PixelPosition, ViewportPosition, Log);

				OutPixelPosition    = CsMathLibrary::Convert(PixelPosition);
				OutViewportPosition = CsMathLibrary::Convert(ViewportPosition);
			}

			void FLibrary::GetSafeByCachedGeometry(UWidget* Widget, FVector2d& OutPixelPosition, FVector2d& OutViewportPosition)
			{
				SET_CONTEXT(GetSafeByCachedGeometry);

				GetSafeByCachedGeometry(Context, Widget, OutPixelPosition, OutViewportPosition, nullptr);
			}

			void FLibrary::GetSafeByCachedGeometry(UWidget* Widget, FVector2f& OutPixelPosition, FVector2f& OutViewportPosition)
			{
				SET_CONTEXT(GetSafeByCachedGeometry);

				GetSafeByCachedGeometry(Context, Widget, OutPixelPosition, OutViewportPosition, nullptr);
			}

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
		}
	}
}

namespace NCsWidget
{
	namespace NPosition
	{
		namespace NWorld
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NWorld::FLibrary, GetSafeBySlot);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NWorld::FLibrary, GetSafeByCachedGeometry);
					}
				}
			}

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			#define USING_NS_CACHED using namespace NCsWidget::NPosition::NWorld::NLibrary::NCached;
			#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NPosition::NWorld::NLibrary::NCached; \
				const FString& Context = Str::__FunctionName

			bool FLibrary::GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection)
			{
				// Get PlayerController associated with ControllerId
				APlayerController* PC = CsPCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);
				
				// Get Screen Position of the Widget
				FVector2d ScreenPosition = CsWidgetScreenPositionLibrary::GetBySlot2dChecked(Context, Widget);
				
				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, ScreenPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
			{
				// Deproject Screen to World
				FVector3d Position;
				FVector3d Direction;
				const bool Result = GetBySlotChecked(Context, WorldContext, ControllerId, Widget, Position, Direction);

				OutPosition  = CsMathLibrary::Convert(Position);
				OutDirection = CsMathLibrary::Convert(Direction);
				return Result;
			}

			bool FLibrary::GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				// Get PlayerController associated with ControllerId
				APlayerController* PC = CsPCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);
				
				// Get Screen Position of the Widget
				FVector2d ScreenPosition = CsWidgetScreenPositionLibrary::GetBySlot2dChecked(Context, Widget);

				if (ScreenPosition == FVector2d(-1.0f))
					return false;

				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, ScreenPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				// Deproject Screen to World
				FVector3d Position;
				FVector3d Direction;
				const bool Result = GetSafeBySlot(Context, WorldContext, ControllerId, Widget, Position, Direction);

				OutPosition  = CsMathLibrary::Convert(Position);
				OutDirection = CsMathLibrary::Convert(Direction);
				return Result;
			}

			bool FLibrary::GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection)
			{
				SET_CONTEXT(GetSafeBySlot);

				return GetSafeBySlot(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}

			bool FLibrary::GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
			{
				SET_CONTEXT(GetSafeBySlot);

				return GetSafeBySlot(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}

			bool FLibrary::GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection)
			{
				// Get PlayerController associated with ControllerId
				APlayerController* PC = CsPCLocalLibrary::GetChecked(Context, WorldContext, ControllerId);

				// Get Pixel Position of the Widget
				FVector2d PixelPosition;
				FVector2d ViewportPosition;
				CsWidgetViewportPositionLibrary::GetByCachedGeometryChecked(Context, Widget, PixelPosition, ViewportPosition);

				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, PixelPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
			{
				// Deproject Screen to World
				FVector3d Position;
				FVector3d Direction;
				const bool Result = GetByCachedGeometryChecked(Context, WorldContext, ControllerId, Widget, Position, Direction);
				
				OutPosition  = CsMathLibrary::Convert(Position);
				OutDirection = CsMathLibrary::Convert(Direction);

				return Result;
			}

			bool FLibrary::GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				// Get PlayerController associated with ControllerId
				APlayerController* PC = CsPCLocalLibrary::GetSafe(Context, WorldContext, ControllerId, Log);
				// Get Screen Position of the Widget
				// Get Pixel Position of the Widget

				FVector2d PixelPosition;
				FVector2d ViewportPosition;
				CsWidgetViewportPositionLibrary::GetSafeByCachedGeometry(Context, Widget, PixelPosition, ViewportPosition, Log);

				if (PixelPosition == FVector2d(-1.0f))
					return false;

				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, PixelPosition, OutPosition, OutDirection);;
			}

			bool FLibrary::GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				// Deproject Screen to World
				FVector3d Position;
				FVector3d Direction;
				const bool Result = GetSafeByCachedGeometry(Context, WorldContext, ControllerId, Widget, Position, Direction);

				OutPosition  = CsMathLibrary::Convert(Position);
				OutDirection = CsMathLibrary::Convert(Direction);
				return Result;
			}

			bool FLibrary::GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3d& OutPosition, FVector3d& OutDirection)
			{
				SET_CONTEXT(GetSafeByCachedGeometry);

				return GetSafeByCachedGeometry(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}

			bool FLibrary::GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector3f& OutPosition, FVector3f& OutDirection)
			{
				SET_CONTEXT(GetSafeByCachedGeometry);

				return GetSafeByCachedGeometry(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}

			#undef USING_NS_CACHED
			#undef SET_CONTEXT
		}
	}
}

namespace NCsWidget
{
	namespace NAnimation
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NAnimation::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NAnimation::FLibrary, SafePlay);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsWidget::NAnimation::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NAnimation::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		using ParamsType = NCsUserWidget::NAnim::NPlay::FParams;

		UWidgetAnimation* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName)
		{
			CS_IS_PENDING_KILL_CHECKED(Widget)

			return CsPropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName);
		}

		UWidgetAnimation* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& AnimName, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName, Log);
		}

		UWidgetAnimation* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& AnimName, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			OutSuccess = false;

			CS_IS_PENDING_KILL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName, OutSuccess, Log);
		}

		UWidgetAnimation* FLibrary::GetSafe(UUserWidget* Widget, const FName& AnimName)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, Widget, AnimName, nullptr);
		}

		float FLibrary::GetLengthChecked(const FString& Context, const UWidgetAnimation* Animation)
		{
			CS_IS_PENDING_KILL_CHECKED(Animation);

			const float Time = Animation->GetEndTime() - Animation->GetStartTime();

			checkf(Time > 0.0f, TEXT("%s: The 'length' (GetEndTime() - GetStartTime()) of Animation: %s is NOT > 0.0f."), *Context, *(Animation->GetName()));
			return Time;
		}

		void FLibrary::PlayChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params)
		{
			CS_IS_PENDING_KILL_CHECKED(Widget)
			CS_IS_VALID_CHECKED(Params);

			UWidgetAnimation* Animation = CsPropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.GetName());

			if (Params.GetEndAtTime() > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.GetStartAtTime(), Params.GetEndAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
			else
				Widget->PlayAnimation(Animation, Params.GetStartAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
		}

		void FLibrary::SafePlay(const FString& Context, UUserWidget* Widget, const ParamsType& Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL_EXIT(Widget)
			CS_IS_VALID_EXIT(Params)

			UWidgetAnimation* Animation = CsPropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.GetName(), Log);

			if (!Animation)
				return;

			if (Params.GetEndAtTime() > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.GetStartAtTime(), Params.GetEndAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
			else
				Widget->PlayAnimation(Animation, Params.GetStartAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
		}

		void FLibrary::SafePlay(UUserWidget* Widget, const ParamsType& Params)
		{
			SET_CONTEXT(SafePlay);

			return SafePlay(Context, Widget, Params, nullptr);
		}

		void FLibrary::PlayChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
		{
			CS_IS_PENDING_KILL_CHECKED(Widget)
			CS_IS_VALID_CHECKED(Params);

			UWidgetAnimation* Animation = CsPropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		}

		bool FLibrary::SafePlay(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL(Widget)
			CS_IS_VALID(Params)

			UWidgetAnimation* Animation = CsPropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name, Log);

			if (!Animation)
				return false;

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			return true;
		}

		bool FLibrary::SafePlay(UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
		{
			SET_CONTEXT(SafePlay);

			return SafePlay(Context, Widget, Params, nullptr);
		}

		void FLibrary::PlayChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params)
		{
			CS_IS_PENDING_KILL_CHECKED(Widget)
			CS_IS_VALID_CHECKED(Params);

			UWidgetAnimation* Animation = CsPropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		}

		bool FLibrary::SafePlay(const FString& Context, UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL(Widget)
			CS_IS_VALID(Params)

			UWidgetAnimation* Animation = CsPropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name, Log);

			if (!Animation)
				return false;

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			return true;
		}

		bool FLibrary::SafePlay(UUserWidget* Widget, const FCsUserWidget_Anim_PlayParams& Params)
		{
			SET_CONTEXT(SafePlay);

			return SafePlay(Context, Widget, Params, nullptr);
		}

		bool FLibrary::SafeHasFinished(const FString& Context, const UUserWidget* Widget, const UWidgetAnimation* Animation, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL(Widget)
			CS_IS_PENDING_KILL(Animation)

			// TODO: Check Widget contains Animation

			// Active
			{
				const TArray<TObjectPtr<UUMGSequencePlayer>>& ActiveSequencePlayers = Widget->ActiveSequencePlayers;
			
				for (const TObjectPtr<UUMGSequencePlayer>& Player : ActiveSequencePlayers)
				{
					if (UUMGSequencePlayer* Ptr = Player.Get())
					{
						if (Ptr->GetAnimation() == Animation)
						{
							const float ElapsedTime = Ptr->GetCurrentTime().AsSeconds() - Animation->GetStartTime();
							const float Duration    = Animation->GetEndTime() - Animation->GetStartTime();;

							if (ElapsedTime >= Duration ||
								FMath::Abs(ElapsedTime - Duration) <= KINDA_SMALL_NUMBER)
							{
								return true;
							}
						}
					}
				}
			}
			// Stopped
			{
				const TArray<TObjectPtr<UUMGSequencePlayer>>& StoppedSequencePlayers = Widget->StoppedSequencePlayers;

				for (const TObjectPtr<UUMGSequencePlayer>& Player : StoppedSequencePlayers)
				{
					if (UUMGSequencePlayer* Ptr = Player.Get())
					{
						if (Ptr->GetAnimation() == Animation)
						{
							const float ElapsedTime = Ptr->GetCurrentTime().AsSeconds() - Animation->GetStartTime();
							const float Duration    = Animation->GetEndTime() - Animation->GetStartTime();;

							if (ElapsedTime >= Duration ||
								FMath::Abs(ElapsedTime - Duration) <= KINDA_SMALL_NUMBER)
							{
								return true;
							}
						}
					}
				}
			}
			return false;
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}

namespace NCsWidget
{
	namespace NTextBlock
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NTextBlock::FLibrary, GetSafe);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsWidget::NTextBlock::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NTextBlock::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		UTextBlock* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PENDING_KILL_CHECKED(Widget)

			return CsPropertyLibrary::GetObjectPropertyValueChecked<UTextBlock>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UTextBlock* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UTextBlock>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UTextBlock* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}

namespace NCsWidget
{
	namespace NButton
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NButton::FLibrary, GetSafe);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsWidget::NButton::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NButton::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		UButton* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			return CsPropertyLibrary::GetObjectPropertyValueChecked<UButton>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UButton* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UButton>(Context, Widget, Widget->GetClass(), PropertyName, OutSuccess, Log);
		}

		UButton* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}

namespace NCsWidget
{
	namespace NImage
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NImage::FLibrary, GetSafe);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsWidget::NImage::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NImage::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		UImage* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			return CsPropertyLibrary::GetObjectPropertyValueChecked<UImage>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UImage* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UImage>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UImage* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}

namespace NCsWidget
{
	namespace NProgressBar
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NProgressBar::FLibrary, GetSafe);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsWidget::NProgressBar::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NProgressBar::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		UProgressBar* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PENDING_KILL_CHECKED(Widget)

			return CsPropertyLibrary::GetObjectPropertyValueChecked<UProgressBar>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UProgressBar* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PENDING_KILL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UProgressBar>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UProgressBar* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}

namespace NCsWidget
{
	namespace NBorder
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NBorder::FLibrary, GetSafe);
				}
			}
		}

		CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

		#define USING_NS_CACHED using namespace NCsWidget::NBorder::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWidget::NBorder::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName

		UBorder* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			return CsPropertyLibrary::GetObjectPropertyValueChecked<UBorder>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UBorder* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			return CsPropertyLibrary::GetObjectPropertyValue<UBorder>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UBorder* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}
}