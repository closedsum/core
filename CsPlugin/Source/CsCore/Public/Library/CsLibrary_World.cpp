// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_World.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_ConsoleVariable.h"
#include "Library/CsLibrary_Valid.h"
// World
#include "Engine/World.h"
#include "Engine/Engine.h"

#if WITH_EDITOR
#include "Editor.h"
#include "EditorViewportClient.h"
#endif // #if WITH_EDITOR

namespace NCsWorld
{
	namespace NLibrary
	{
		namespace NCached
		{
			namespace Str
			{
				CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWorld::FLibrary, GetSafe);
			}
		}
	}

	// Get
	#pragma region

	UWorld* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
	{
		CS_IS_PTR_NULL_CHECKED(WorldContext)

		UWorld* World = WorldContext->GetWorld();

		checkf(World, TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName()));

		return World;
	}

	UWorld* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		CS_IS_PTR_NULL_RET_NULL(WorldContext)

		UWorld* World = WorldContext->GetWorld();

		if (!World)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get World from WorldContext: %s."), *Context, *(WorldContext->GetName())));
			return nullptr;
		}
		return World;
	}

	UWorld* FLibrary::GetSafe(const UObject* WorldContext)
	{
		using namespace NCsWorld::NLibrary::NCached;

		const FString& Context = Str::GetSafe;

		return GetSafe(Context, WorldContext, nullptr);
	}

	UObject* FLibrary::GetAsObjectChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked(Context, WorldContext);
	}

	UObject* FLibrary::GetSafeAsObject(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
	{
		return GetSafe(Context, WorldContext, Log);
	}

	#pragma endregion Get

	// WorldType
	#pragma region

	bool FLibrary::IsGameWorld(UWorld* World)
	{
		return World && World->IsGameWorld();
	}

	bool FLibrary::IsPlayInGame(UWorld* World)
	{
		return World && World->WorldType == EWorldType::Game;
	}

	bool FLibrary::IsPlayInEditor(UWorld* World)
	{
		return World && World->WorldType == EWorldType::Editor;
	}

	bool FLibrary::IsPlayInEditor(const UObject* WorldContext)
	{
		return IsPlayInEditor(GetSafe(WorldContext));
	}

	bool FLibrary::IsPlayInPIE(UWorld* World)
	{
		return World && World->WorldType == EWorldType::PIE;
	}

	bool FLibrary::IsPlayInPIE(const UObject* WorldContext)
	{
		return IsPlayInPIE(GetSafe(WorldContext));
	}

	bool FLibrary::IsPlayInEditorPreview(UWorld* World)
	{
		return World && World->WorldType == EWorldType::EditorPreview;
	}

	bool FLibrary::IsPlayInEditorPreview(const UObject* WorldContext)
	{
		return IsPlayInEditorPreview(GetSafe(WorldContext));
	}

	bool FLibrary::IsPlayInGameOrPIE(UWorld* World)
	{
		return World && (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE);
	}

	bool FLibrary::IsPlayInGameOrPIE(const UObject* WorldContext)
	{
		return IsPlayInGameOrPIE(GetSafe(WorldContext));
	}

	bool FLibrary::IsPlayInEditorOrEditorPreview(UWorld* World)
	{
		return World && (World->WorldType == EWorldType::Editor || World->WorldType == EWorldType::EditorPreview);
	}

	bool FLibrary::IsPlayInEditorOrEditorPreview(const UObject* WorldContext)
	{
		return IsPlayInEditorOrEditorPreview(GetSafe(WorldContext));
	}

	bool FLibrary::IsAnyWorldContextEditorOrEditorPreview()
	{
		const TIndirectArray<FWorldContext>& WorldContexts = GEngine->GetWorldContexts();

		for (const FWorldContext& Context : WorldContexts)
		{
			if (Context.WorldType == EWorldType::Editor ||
				Context.WorldType == EWorldType::EditorPreview)
			{
				return true;
			}
		}
		return false;
	}

	bool FLibrary::IsEditorPreviewOrphaned(UObject* WorldContext)
	{
		if (!WorldContext)
			return false;

	#if WITH_EDITOR
		if (UWorld* World = WorldContext->GetWorld())
		{
			if (GEditor)
			{
				const TArray<FEditorViewportClient*>& ViewportClients = GEditor->GetAllViewportClients();

				for (FEditorViewportClient* VC : ViewportClients)
				{
					if (VC->GetWorld() == World)
					{
						return false;
					}
				}
				return true;
			}
		}
	#endif // #if WITH_EDITOR
		return false;
	}

	#pragma endregion WorldType

	const FString& FLibrary::GetStreamingLevelsPrefixChecked(const FString& Context, const UObject* WorldContext)
	{
		return GetChecked(Context, WorldContext)->StreamingLevelsPrefix;
	}

	// Spawn
	#pragma region

	AActor* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, UClass* Class)
	{
		CS_IS_PTR_NULL_CHECKED(Class)

		AActor* A = GetChecked(Context, WorldContext)->SpawnActor(Class);

		checkf(A, TEXT("%s: Context: Failed to Spawn Actor from Class: %s."), *(Class->GetName()));
		return A;
	}

	#pragma endregion Spawn

	namespace NSeamlessTravelHandler
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWorld::NSeamlessTravelHandler::FLibrary, IsInTransition);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsWorld::NSeamlessTravelHandler::FLibrary, GetbTransitionInProgress);
				}
			}
		}

	#define USING_NS_CACHED using namespace NCsWorld::NSeamlessTravelHandler::NLibrary::NCached;
	#define SET_CONTEXT(__FunctionName) using namespace NCsWorld::NSeamlessTravelHandler::NLibrary::NCached; \
		const FString& Context = Str::##__FunctionName

		bool FLibrary::IsInTransition(const UWorld* World)
		{
			SET_CONTEXT(IsInTransition);

			CS_IS_PENDING_KILL_CHECKED(World)

			FWorldContext* WorldContext			  = GEngine->GetWorldContextFromWorld(World);
			const FSeamlessTravelHandler& Handler = WorldContext->SeamlessTravelHandler;

			return Handler.IsInTransition();
		}

	// bTransitionInProgress

		bool* FLibrary::GetbTransitionInProgress(UWorld* World)
		{
			SET_CONTEXT(GetbTransitionInProgress);

			CS_IS_PENDING_KILL_CHECKED(World)

			FWorldContext* WorldContext	    = GEngine->GetWorldContextFromWorld(World);
			FSeamlessTravelHandler& Handler = WorldContext->SeamlessTravelHandler;

			// Get pointer to start of struct
			FURL* PendingTravelURL = ((FURL*)(&Handler));
			char* Base = (char*)PendingTravelURL;

			// Offset by PendingTravelURL
			size_t Offset = sizeof(FURL);
			// Offset by LoadedPackage
			Offset += sizeof(UObject*);
			// Offset by CurrentWorld
			Offset += sizeof(UWorld*);
			// Offset by LoadedWorld
			Offset += sizeof(UWorld*);

			bool& bTransitionInProgress = *((bool*)(Base + Offset));
			return &bTransitionInProgress;
		}

		void FLibrary::EnableTransitionInProgress(UWorld* World)
		{
			bool* bTransitionInProgress = GetbTransitionInProgress(World);
			*bTransitionInProgress		= true;
		}

		void FLibrary::DisableTransitionInProgress(UWorld* World)
		{
			bool* bTransitionInProgress = GetbTransitionInProgress(World);
			*bTransitionInProgress		= false;
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
	}

	namespace NPIE
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					const FString net_AllowPIESeamlessTravel = TEXT("net.AllowPIESeamlessTravel");
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsWorld::NPIE::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsWorld::NPIE::NLibrary::NCached; \
			const FString& Context = Str::##__FunctionName
		#define CVarLibrary NCsConsole::NVariable::FLibrary

		void FLibrary::EnableSeamlessTravelChecked(const FString& Context)
		{
			USING_NS_CACHED

			CVarLibrary::EnableChecked(Context, Str::net_AllowPIESeamlessTravel);
		}

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef CVarLibrary
	}
}