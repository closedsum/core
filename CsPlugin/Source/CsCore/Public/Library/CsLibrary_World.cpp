// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_World.h"
#include "CsCore.h"

// World
#include "Engine/World.h"
#include "Engine/Engine.h"

#if WITH_EDITOR
#include "Editor.h"
#include "EditorViewportClient.h"
#endif // #if WITH_EDITOR

bool FCsLibrary_World::IsPlayInGame(UWorld* World)
{
	return World && World->WorldType == EWorldType::Game;
}

bool FCsLibrary_World::IsPlayInEditor(UWorld* World)
{
	return World && World->WorldType == EWorldType::Editor;
}

bool FCsLibrary_World::IsPlayInPIE(UWorld* World)
{
	return World && World->WorldType == EWorldType::PIE;
}

bool FCsLibrary_World::IsPlayInEditorPreview(UWorld* World)
{
	return World && World->WorldType == EWorldType::EditorPreview;
}

bool FCsLibrary_World::IsPlayInGameOrPIE(UWorld* World)
{
	return World && (World->WorldType == EWorldType::Game || World->WorldType == EWorldType::PIE);
}

bool FCsLibrary_World::IsAnyWorldContextEditorOrEditorPreview()
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

bool FCsLibrary_World::IsEditorPreviewOrphaned(UObject* WorldContext)
{
	if (UWorld* World = WorldContext->GetWorld())
	{
#if WITH_EDITOR
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
#endif // #if WITH_EDITOR
	}
	return false;
}