// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Trace/CsLibrary_Manager_Trace.h"

// Library
#include "Kismet/GameplayStatics.h"
#include "Library/CsLibrary_Viewport.h"
#include "Library/CsLibrary_Player.h"
#include "Library/CsLibrary_Valid.h"
#include "Game/CsLibrary_GameState.h"
// Managers
#include "Managers/Trace/CsManager_Trace.h"

namespace NCsTrace
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsTrace::NManager::FLibrary, GetSafe);
				}

				namespace Name
				{
					const FName TraceScreenToWorldChecked = FName("TraceScreenToWorldChecked");
				}
			}
		}

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsTrace::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_Trace* FLibrary::GetChecked(const FString& Context, UObject* ContextObject)
		{
			UObject* ContextRoot			 = GetContextRootChecked(Context, ContextObject);
			UCsManager_Trace* Manager_Trace  = UCsManager_Trace::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_Trace)
			return Manager_Trace;
		}

		UCsManager_Trace* FLibrary::GetSafe(const FString& Context, UObject* ContextObject, void(*Log)(const FString&) /*= &FCsLog::Warning*/)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, ContextObject, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(ContextRoot);

			if (!Manager_Trace)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_Trace."), *Context));
			}
			return Manager_Trace;
		}

		UCsManager_Trace* FLibrary::GetSafe(UObject* ContextObject)
		{
			using namespace NCsTrace::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, ContextObject, nullptr);
		}

		#pragma endregion Get

		#define ResponseType NCsTrace::NResponse::FResponse
		ResponseType* FLibrary::TraceScreenToWorldChecked(const FString& Context, UObject* WorldContext, const FVector2D& ScreenPosition, const float& Distance, const ECollisionChannel& Channel)
		{
		#undef ResponseType

			using namespace NCsTrace::NManager::NLibrary::NCached;

			CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Distance, 0.0f)

			checkf(Channel != ECollisionChannel::ECC_MAX, TEXT("%s: Channel: ECC_MAX is NOT Valid."), *Context);

			typedef NCsViewport::NLocal::NPlayer::FLibrary ViewportLibrary;

			FVector WorldOrigin;
			FVector WorldDirection;

			if (ViewportLibrary::DeprojectScreenToWorldChecked(Context, WorldContext, ScreenPosition, WorldOrigin, WorldDirection))
			{
				UObject* ContextRoot = GetContextRootChecked(Context, WorldContext);

				UCsManager_Trace* Manager_Trace = UCsManager_Trace::Get(ContextRoot);

				typedef NCsTrace::NRequest::FRequest RequestType;

				RequestType* Request    = Manager_Trace->AllocateRequest();
				Request->ProfileName	= Name::TraceScreenToWorldChecked;
				Request->Type			= ECsTraceType::Line;
				Request->Method			= ECsTraceMethod::Multi;
				Request->Query			= ECsTraceQuery::Channel;
				Request->Start			= WorldOrigin;
				Request->End			= WorldOrigin + WorldDirection * Distance;
				Request->Channel		= Channel;

				return Manager_Trace->Trace(Request);
			}
			return nullptr;
		}
	}
}