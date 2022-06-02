// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Widget.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Load.h"
// Library
#include "Library/CsLibrary_Property.h"
#include "Object/CsLibrary_Object.h"
#include "Library/CsLibrary_Player.h"
#include "Kismet/GameplayStatics.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Library/CsLibrary_Valid.h"
// Player
#include "GameFramework/PlayerController.h"
// Game
#include "Engine/GameInstance.h"
// Widget
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
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

namespace NCsWidget
{
	UUserWidget* FLibrary::CreateSafe(const FString& Context, UObject* Owner, TSubclassOf<UUserWidget> UserWidgetClass, const FName& WidgetName /*=NAME_None*/, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(Owner)

		if (!UserWidgetClass.Get())
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: UserWidgetClass is NULL."), *Context));
			return nullptr;
		}

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
		typedef NCsObject::FLibrary ObjectLibrary;
		
		UObject* O = ObjectLibrary::LoadChecked(Context, Path);

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		checkf(BpGC, TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName()));

		checkf(BpGC->ClassGeneratedBy, TEXT("%s: ClassGeneratedBy is NULL for Object: %s."), *Context, *(O->GetName()));

		UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

		checkf(BpC, TEXT("%s: Failed to cast Class: %s to UBlueprintCore."), *Context, *(BpGC->ClassGeneratedBy->GetName()));

		checkf(BpC->GeneratedClass, TEXT("%s: Failed to get GeneratedClass from Class: %s."), *Context, *(BpC->GetName()));

		return BpC->GeneratedClass;
	}

	UClass* FLibrary::SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		UObject* O = ObjectLibrary::SafeLoad(Context, Path, Log);

		if (!O)
			return nullptr;

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		if (!BpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName())));
			return nullptr;
		}

		if (!BpGC->ClassGeneratedBy)
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
		return BpC->GeneratedClass;
	}

	UClass* FLibrary::LoadChecked(const FString& Context, const FString& Path)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		checkf(Path.EndsWith(ECsLoadCached::Str::_C), TEXT("%s: Path: %s does NOT end with '_C'."), *Context, *Path);

		UObject* O = ObjectLibrary::LoadChecked(Context, Path);

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		checkf(BpGC, TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName()));

		checkf(BpGC->ClassGeneratedBy, TEXT("%s: ClassGeneratedBy is NULL for Object: %s."), *Context, *(O->GetName()));

		UBlueprintCore* BpC = Cast<UBlueprintCore>(BpGC->ClassGeneratedBy);

		checkf(BpC, TEXT("%s: Failed to cast Class: %s to UBlueprintCore."), *Context, *(BpGC->ClassGeneratedBy->GetName()));

		checkf(BpC->GeneratedClass, TEXT("%s: Failed to get GeneratedClass from Class: %s."), *Context, *(BpC->GetName()));

		return BpC->GeneratedClass;
	}

	UClass* FLibrary::SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
	{
		typedef NCsObject::FLibrary ObjectLibrary;

		if (!Path.EndsWith(ECsLoadCached::Str::_C))
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Path: %s does NOT end with '_C'."), *Context, *Path));
			return nullptr;
		}
			
		UObject* O = ObjectLibrary::SafeLoad(Context, Path, Log);

		if (!O)
			return nullptr;

		UBlueprintGeneratedClass* BpGC = Cast<UBlueprintGeneratedClass>(O);

		if (!BpGC)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast Object: %s to UBlueprintGeneratedClass."), *Context, *(O->GetName())));
			return nullptr;
		}

		if (!BpGC->ClassGeneratedBy)
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
		return BpC->GeneratedClass;
	}

	#pragma endregion Load

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
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeBySlot);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeAbsoluteByCachedGeometry);
					}
				}
			}

			FVector2D FLibrary::GetBySlotChecked(const FString& Context, UWidget* Widget)
			{
				CS_IS_PTR_NULL_CHECKED(Widget)

				checkf(Widget->Slot, TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName()));

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

				checkf(Slot, TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName()));

				checkf(Widget->GetVisibility() != ESlateVisibility::Collapsed, TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName()));

				return Slot->GetPosition();
			}

			FVector2D FLibrary::GetSafeBySlot(const FString& Context, UWidget* Widget, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
			{
				if (!Widget)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget is NULL."), *Context));
					return FVector2D(-1.0f);
				}

				if (!Widget->Slot)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName())));
					return FVector2D(-1.0f);
				}

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

				if (!Slot)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName())));
					return FVector2D(-1.0f);
				}

				if (Widget->GetVisibility() == ESlateVisibility::Collapsed)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName())));
					return FVector2D(-1.0f);
				}
				return Slot->GetPosition();
			}

			FVector2D FLibrary::GetSafeBySlot(UWidget* Widget)
			{
				using namespace NCsWidget::NPosition::NScreen::NLibrary::NCached;

				const FString& Context = Str::GetSafeBySlot;

				return GetSafeBySlot(Context, Widget, nullptr);
			}

			FVector2D FLibrary::GetAbsoluteByCachedGeometryChecked(const FString& Context, UWidget* Widget)
			{
				CS_IS_PTR_NULL_CHECKED(Widget)

				checkf(Widget->GetVisibility() != ESlateVisibility::Collapsed, TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName()));

				checkf(Widget->GetVisibility() != ESlateVisibility::Hidden, TEXT("%s: %s's Visibility == ESlateVisibility::Hidden is NOT Valid when getting position."), *Context, *(Widget->GetName()));

				return Widget->GetCachedGeometry().GetAbsolutePosition();
			}

			FVector2D FLibrary::GetSafeAbsoluteByCachedGeometry(const FString& Context, UWidget* Widget, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
			{
				if (!Widget)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget is NULL."), *Context));
					return FVector2D(-1.0f);
				}

				if (Widget->GetVisibility() == ESlateVisibility::Collapsed)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s's Visibility == ESlateVisibility::Collapsed is NOT Valid when getting position."), *Context, *(Widget->GetName())));
					return FVector2D(-1.0f);
				}

				if (Widget->GetVisibility() == ESlateVisibility::Hidden)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: %s's Visibility == ESlateVisibility::Hidden is NOT Valid when getting position."), *Context, *(Widget->GetName())));
					return FVector2D(-1.0f);
				}
				return Widget->GetCachedGeometry().GetAbsolutePosition();
			}

			FVector2D FLibrary::GetSafeAbsoluteByCachedGeometry(UWidget* Widget)
			{
				using namespace NCsWidget::NPosition::NScreen::NLibrary::NCached;

				const FString& Context = Str::GetSafeAbsoluteByCachedGeometry;

				return GetSafeAbsoluteByCachedGeometry(Context, Widget, nullptr);
			}
		}

		namespace NViewport
		{
			namespace NLibrary
			{
				namespace NCached
				{
					namespace Str
					{
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeByCachedGeometry);
					}
				}
			}

			void FLibrary::GetByCachedGeometryChecked(const FString& Context, UWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition)
			{
				typedef NCsWidget::NPosition::NScreen::FLibrary WidgetScreenPositionLibrary;

				const FVector2D AbsolutePosition = WidgetScreenPositionLibrary::GetAbsoluteByCachedGeometryChecked(Context, Widget);

				USlateBlueprintLibrary::AbsoluteToViewport(Widget->GetWorld(), AbsolutePosition, OutPixelPosition, OutViewportPosition);
			}

			void FLibrary::GetSafeByCachedGeometry(const FString& Context, UWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
			{
				typedef NCsWidget::NPosition::NScreen::FLibrary WidgetScreenPositionLibrary;

				const FVector2D AbsolutePosition = WidgetScreenPositionLibrary::GetSafeAbsoluteByCachedGeometry(Context, Widget, Log);

				if (AbsolutePosition == FVector2D(-1.0f))
				{
					OutPixelPosition = FVector2D(-1.0f);
					OutViewportPosition = FVector2D(-1.0f);
					return;
				}

				USlateBlueprintLibrary::AbsoluteToViewport(Widget->GetWorld(), AbsolutePosition, OutPixelPosition, OutViewportPosition);
			}

			void FLibrary::GetSafeByCachedGeometry(UWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition)
			{
				using namespace NCsWidget::NPosition::NViewport::NLibrary::NCached;

				const FString& Context = Str::GetSafeByCachedGeometry;

				GetSafeByCachedGeometry(Context, Widget, OutPixelPosition, OutViewportPosition, nullptr);
			}
		}

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

			bool FLibrary::GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection)
			{
				// Get PlayerController associated with ControllerId
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);
				// Get Screen Position of the Widget
				typedef NCsWidget::NPosition::NScreen::FLibrary WidgetScreenPositionLibrary;

				FVector2D ScreenPosition = WidgetScreenPositionLibrary::GetBySlotChecked(Context, Widget);
				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, ScreenPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
			{
				// Get PlayerController associated with ControllerId
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log);
				// Get Screen Position of the Widget
				typedef NCsWidget::NPosition::NScreen::FLibrary WidgetScreenPositionLibrary;

				FVector2D ScreenPosition = WidgetScreenPositionLibrary::GetBySlotChecked(Context, Widget);

				if (ScreenPosition == FVector2D(-1.0f))
					return false;

				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, ScreenPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection)
			{
				using namespace NCsWidget::NPosition::NWorld::NLibrary::NCached;

				const FString& Context = Str::GetSafeBySlot;

				return GetSafeBySlot(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}

			bool FLibrary::GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection)
			{
				// Get PlayerController associated with ControllerId
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetLocalChecked(Context, WorldContext, ControllerId);
				// Get Pixel Position of the Widget
				typedef NCsWidget::NPosition::NViewport::FLibrary WidgetScreenPositionLibrary;

				FVector2D PixelPosition;
				FVector2D ViewportPosition;
				WidgetScreenPositionLibrary::GetByCachedGeometryChecked(Context, Widget, PixelPosition, ViewportPosition);
				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, PixelPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
			{
				// Get PlayerController associated with ControllerId
				typedef NCsPlayer::NController::FLibrary PlayerControllerLibrary;

				APlayerController* PC = PlayerControllerLibrary::GetSafeLocal(Context, WorldContext, ControllerId, Log);
				// Get Screen Position of the Widget
				// Get Pixel Position of the Widget
				typedef NCsWidget::NPosition::NViewport::FLibrary WidgetScreenPositionLibrary;

				FVector2D PixelPosition;
				FVector2D ViewportPosition;
				WidgetScreenPositionLibrary::GetSafeByCachedGeometry(Context, Widget, PixelPosition, ViewportPosition, Log);

				if (PixelPosition == FVector2D(-1.0f))
					return false;

				// Deproject Screen to World
				return UGameplayStatics::DeprojectScreenToWorld(PC, PixelPosition, OutPosition, OutDirection);
			}

			bool FLibrary::GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UWidget* Widget, FVector& OutPosition, FVector& OutDirection)
			{
				using namespace NCsWidget::NPosition::NWorld::NLibrary::NCached;

				const FString& Context = Str::GetSafeByCachedGeometry;

				return GetSafeByCachedGeometry(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}
		}
	}

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

		UWidgetAnimation* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& AnimName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName);
		}

		UWidgetAnimation* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& AnimName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), AnimName, Log);
		}

		UWidgetAnimation* FLibrary::GetSafe(UUserWidget* Widget, const FName& AnimName)
		{
			using namespace NCsWidget::NAnimation::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Widget, AnimName, nullptr);
		}

		float FLibrary::GetLengthChecked(const FString& Context, const UWidgetAnimation* Animation)
		{
			CS_IS_PTR_NULL_CHECKED(Animation);

			const float Time = Animation->GetEndTime() - Animation->GetStartTime();

			checkf(Time > 0.0f, TEXT("%s: The 'length' (GetEndTime() - GetStartTime()) of Animation: %s is NOT > 0.0f."), *Context, *(Animation->GetName()));
			return Time;
		}

		#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

		void FLibrary::PlayChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			CS_IS_VALID_CHECKED(Params);

			typedef NCsProperty::FLibrary PropertyLibrary;

			UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.GetName());

			if (Params.GetEndAtTime() > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.GetStartAtTime(), Params.GetEndAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
			else
				Widget->PlayAnimation(Animation, Params.GetStartAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
		}

		void FLibrary::SafePlay(const FString& Context, UUserWidget* Widget, const ParamsType& Params, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Widget)

			CS_IS_VALID_EXIT(Params)

			typedef NCsProperty::FLibrary PropertyLibrary;

			UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.GetName(), Log);

			if (!Animation)
				return;

			if (Params.GetEndAtTime() > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.GetStartAtTime(), Params.GetEndAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
			else
				Widget->PlayAnimation(Animation, Params.GetStartAtTime(), Params.GetNumLoopsToPlay(), (EUMGSequencePlayMode::Type)Params.GetPlayMode(), Params.GetPlaybackSpeed());
		}

		void FLibrary::SafePlay(UUserWidget* Widget, const ParamsType& Params)
		{
			using namespace NCsWidget::NAnimation::NLibrary::NCached;

			const FString& Context = Str::SafePlay;

			return SafePlay(Context, Widget, Params, nullptr);
		}

		#undef ParamsType

		void FLibrary::PlayChecked(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			CS_IS_VALID_CHECKED(Params);

			typedef NCsProperty::FLibrary PropertyLibrary;

			UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		}

		void FLibrary::SafePlay(const FString& Context, UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Widget)

			CS_IS_VALID_EXIT(Params)

			typedef NCsProperty::FLibrary PropertyLibrary;

			UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name, Log);

			if (!Animation)
				return;

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		}

		void FLibrary::SafePlay(UUserWidget* Widget, const FCsUserWidgetAnimPlayParams& Params)
		{
			using namespace NCsWidget::NAnimation::NLibrary::NCached;

			const FString& Context = Str::SafePlay;

			return SafePlay(Context, Widget, Params, nullptr);
		}
	}

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

		UTextBlock* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueChecked<UTextBlock>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UTextBlock* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValue<UTextBlock>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UTextBlock* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			using namespace NCsWidget::NTextBlock::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}
	}

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

		UButton* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueChecked<UButton>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UButton* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValue<UButton>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UButton* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			using namespace NCsWidget::NButton::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}
	}

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

		UImage* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueChecked<UImage>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UImage* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValue<UImage>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UImage* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			using namespace NCsWidget::NImage::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}
	}

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

		UProgressBar* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueChecked<UProgressBar>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UProgressBar* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValue<UProgressBar>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UProgressBar* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			using namespace NCsWidget::NProgressBar::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}
	}

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

		UBorder* FLibrary::GetChecked(const FString& Context, UUserWidget* Widget, const FName& PropertyName)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValueChecked<UBorder>(Context, Widget, Widget->GetClass(), PropertyName);
		}

		UBorder* FLibrary::GetSafe(const FString& Context, UUserWidget* Widget, const FName& PropertyName, void(*Log)(const FString&) /*=&NCsUI::FLog; :Warning*/)
		{
			CS_IS_PTR_NULL_RET_NULL(Widget)

			typedef NCsProperty::FLibrary PropertyLibrary;

			return PropertyLibrary::GetObjectPropertyValue<UBorder>(Context, Widget, Widget->GetClass(), PropertyName, Log);
		}

		UBorder* FLibrary::GetSafe(UUserWidget* Widget, const FName& PropertyName)
		{
			using namespace NCsWidget::NBorder::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, Widget, PropertyName, nullptr);
		}
	}
}