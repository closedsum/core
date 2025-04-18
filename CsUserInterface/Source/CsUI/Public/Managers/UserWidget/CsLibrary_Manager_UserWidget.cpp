// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/UserWidget/CsLibrary_Manager_UserWidget.h"

// Library
#include "Library/CsLibrary_Valid.h"

#if WITH_EDITOR
// Library
#include "Game/CsLibrary_GameState.h"
#endif // #if WITH_EDITOR

namespace NCsUserWidget
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsUserWidget::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsUserWidget::NManager::FLibrary, GetSafe);
				}
			}
		}

		using PayloadType = NCsUserWidget::NPayload::IPayload;

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&NCsUI::FLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsUserWidget::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_UserWidget* FLibrary::GetChecked(const FString& Context, const UObject* ContextObject)
		{
			UObject* ContextRoot					  = GetContextRootChecked(Context, ContextObject);
			UCsManager_UserWidget* Manager_UserWidget = UCsManager_UserWidget::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_UserWidget)
			return Manager_UserWidget;
		}

		UCsManager_UserWidget* FLibrary::GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) /*= &NCsUI::FLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_UserWidget* Manager_UserWidget = UCsManager_UserWidget::GetSafe(Context, ContextRoot, Log);

			if (!Manager_UserWidget)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_UserWidget."), *Context));
			}
			return Manager_UserWidget;
		}

		UCsManager_UserWidget* FLibrary::GetSafe(const UObject* ContextObject)
		{
			using namespace NCsUserWidget::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		// Payload
		#pragma region

		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsUserWidgetPooled& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}

		#pragma endregion Payload

		// Spawn
		#pragma region

		const FCsUserWidgetPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsUserWidgetPooled& Type, PayloadType* Payload)
		{
			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		#pragma endregion Spawn

		namespace NSetPositionInViewports
		{
			int32 FLibrary::AllocateChecked(const FString& Context, const UObject* WorldContext, UUserWidget* Widget)
			{
				return CsWidgetManagerLibrary::GetChecked(Context, WorldContext)->SetPositionInViewports.Allocate(Widget);
			}

			void FLibrary::DeallocateChecked(const FString& Context, const UObject* WorldContext, const int32& ID)
			{
				CsWidgetManagerLibrary::GetChecked(Context, WorldContext)->SetPositionInViewports.Deallocate(ID);
			}

			void FLibrary::UpdateWorldPositionAndOffsetChecked(const FString& Context, const UObject* WorldContext, const int32& ID, const FVector3f& WorldPosition, const FVector2f& Offset)
			{
				CsWidgetManagerLibrary::GetChecked(Context, WorldContext)->SetPositionInViewports.UpdateWorldPositionAndOffset(ID, WorldPosition, Offset);
			}
		}
	}
}