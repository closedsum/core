// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_Widget.h"
#include "CsUI.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"
#include "Library/CsLibrary_Property.h"
#include "Kismet/GameplayStatics.h"
#include "Library/CsLibrary_Player.h"
#include "Blueprint/SlateBlueprintLibrary.h"
// Widget
#include "Blueprint/UserWidget.h"
// Components
#include "Components/CanvasPanelSlot.h"
// World
#include "Engine/World.h"

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
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeBySlot);
						CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWidget::NPosition::NScreen::FLibrary, GetSafeAbsoluteByCachedGeometry);
					}
				}
			}

			FVector2D FLibrary::GetBySlotChecked(const FString& Context, UUserWidget* Widget)
			{
				CS_IS_PTR_NULL_CHECKED(Widget)

				checkf(Widget->Slot, TEXT("%s: Widget: %s's Slot is NULL."), *Context, *(Widget->GetName()));

				UCanvasPanelSlot* Slot = Cast<UCanvasPanelSlot>(Widget->Slot);

				checkf(Slot, TEXT("%s: Widget: %s's Slot is NOT of type: UCavnasPanelSlot."), *Context, *(Widget->GetName()));

				return Slot->GetPosition();
			}

			FVector2D FLibrary::GetSafeBySlot(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
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
				return Slot->GetPosition();
			}

			FVector2D FLibrary::GetSafeBySlot(UUserWidget* Widget)
			{
				using namespace NCsWidget::NPosition::NScreen::NLibrary::NCached;

				const FString& Context = Str::GetSafeBySlot;

				return GetSafeBySlot(Context, Widget, nullptr);
			}

			FVector2D FLibrary::GetAbsoluteByCachedGeometryChecked(const FString& Context, UUserWidget* Widget)
			{
				CS_IS_PTR_NULL_CHECKED(Widget)

				return Widget->GetCachedGeometry().GetAbsolutePosition();
			}

			FVector2D FLibrary::GetSafeAbsoluteByCachedGeometry(const FString& Context, UUserWidget* Widget, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
			{
				if (!Widget)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Widget is NULL."), *Context));
					return FVector2D(-1.0f);
				}
				return Widget->GetCachedGeometry().GetAbsolutePosition();
			}

			FVector2D FLibrary::GetSafeAbsoluteByCachedGeometry(UUserWidget* Widget)
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

			void FLibrary::GetByCachedGeometryChecked(const FString& Context, UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition)
			{
				typedef NCsWidget::NPosition::NScreen::FLibrary WidgetScreenPositionLibrary;

				const FVector2D AbsolutePosition = WidgetScreenPositionLibrary::GetAbsoluteByCachedGeometryChecked(Context, Widget);

				USlateBlueprintLibrary::AbsoluteToViewport(Widget->GetWorld(), AbsolutePosition, OutPixelPosition, OutViewportPosition);
			}

			void FLibrary::GetSafeByCachedGeometry(const FString& Context, UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
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

			void FLibrary::GetSafeByCachedGeometry(UUserWidget* Widget, FVector2D& OutPixelPosition, FVector2D& OutViewportPosition)
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

			bool FLibrary::GetBySlotChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
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

			bool FLibrary::GetSafeBySlot(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
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

			bool FLibrary::GetSafeBySlot(UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
			{
				using namespace NCsWidget::NPosition::NWorld::NLibrary::NCached;

				const FString& Context = Str::GetSafeBySlot;

				return GetSafeBySlot(Context, WorldContext, ControllerId, Widget, OutPosition, OutDirection, nullptr);
			}

			bool FLibrary::GetByCachedGeometryChecked(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
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

			bool FLibrary::GetSafeByCachedGeometry(const FString& Context, UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
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

			bool FLibrary::GetSafeByCachedGeometry(UObject* WorldContext, const int32& ControllerId, UUserWidget* Widget, FVector& OutPosition, FVector& OutDirection)
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

		#define ParamsType NCsUserWidget::NAnim::NPlay::FParams

		void FLibrary::PlayChecked(const FString& Context, UUserWidget* Widget, const ParamsType& Params)
		{
			CS_IS_PTR_NULL_CHECKED(Widget)

			check(Params.IsValidChecked(Context));

			typedef NCsProperty::FLibrary PropertyLibrary;

			UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValueChecked<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name);

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
		}

		void FLibrary::SafePlay(const FString& Context, UUserWidget* Widget, const ParamsType& Params, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Widget)

			if (!Params.IsValid(Context, Log))
				return;

			typedef NCsProperty::FLibrary PropertyLibrary;

			UWidgetAnimation* Animation = PropertyLibrary::GetObjectPropertyValue<UWidgetAnimation>(Context, Widget, Widget->GetClass(), Params.Name, Log);

			if (!Animation)
				return;

			if (Params.EndAtTime > 0.0f)
				Widget->PlayAnimationTimeRange(Animation, Params.StartAtTime, Params.EndAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
			else
				Widget->PlayAnimation(Animation, Params.StartAtTime, Params.NumLoopsToPlay, (EUMGSequencePlayMode::Type)Params.PlayMode, Params.PlaybackSpeed);
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

			check(Params.IsValidChecked(Context));

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

			if (!Params.IsValid(Context, Log))
				return;

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
}