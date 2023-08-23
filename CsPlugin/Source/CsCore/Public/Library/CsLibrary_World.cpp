// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_World.h"
#include "CsCore.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
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

	bool FLibrary::IsPlayInGame(UWorld* World)
	{
		return World && World->WorldType == EWorldType::Game;
	}

	bool FLibrary::IsPlayInEditor(UWorld* World)
	{
		return World && World->WorldType == EWorldType::Editor;
	}

	bool FLibrary::IsPlayInPIE(UWorld* World)
	{
		return World && World->WorldType == EWorldType::PIE;
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
}