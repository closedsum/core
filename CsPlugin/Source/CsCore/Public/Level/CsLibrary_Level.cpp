// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Level/CsLibrary_Level.h"

// Level
#include "Engine/LevelScriptActor.h"
// World
#include "Engine/World.h"

namespace NCsLevel
{
	// Persistent
	#pragma region

	ULevel* FLibrary::GetPersistentLevel(UWorld* World)
	{
		if (!World)
			return nullptr;

		const TArray<ULevel*>& Levels = World->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel())
			{
				return Level;
			}
		}
		return nullptr;
	}

	ULevel* FLibrary::GetPersistentLevel(UObject* WorldContext)
	{
		if (!WorldContext)
			return nullptr;

		return GetPersistentLevel(WorldContext->GetWorld());
	}

	ULevel* FLibrary::GetPersistentLevelChecked(const FString& Context, UWorld* World)
	{
		checkf(World, TEXT("%s: World is NULL."), *Context);

		const TArray<ULevel*>& Levels = World->GetLevels();

		for (ULevel* Level : Levels)
		{
			if (Level->IsPersistentLevel())
			{
				return Level;
			}
		}
		checkf(0, TEXT("%s: Failed to get the Persistent Level from World: %s."), *Context, *(World->GetName()))
		return nullptr;
	}

	ULevel* FLibrary::GetPersistentLevelChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		return GetPersistentLevelChecked(Context, WorldContext->GetWorld());
	}

	FString FLibrary::GetPersistentLevelName(UWorld* World)
	{
		if (World)
			return UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		return FString();
	}

	FString FLibrary::GetPersistentLevelName(UObject* WorldContext)
	{
		if (WorldContext)
			return GetPersistentLevelName(WorldContext->GetWorld());
		return FString();
	}

	FString FLibrary::GetPersistentLevelNameChecked(const FString& Context, UWorld* World)
	{
		checkf(World, TEXT("%s: World is NULL."), *Context);

		return UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
	}

	FString FLibrary::GetPersistentLevelNameChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		return GetPersistentLevelNameChecked(Context, WorldContext->GetWorld());
	}

	FName FLibrary::GetPersistentLevelFName(UWorld* World)
	{
		if (World)
		{
			const FString Name = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			return FName(*Name);
		}
		return NAME_None;
	}

	FName FLibrary::GetPersistentLevelFName(UObject* WorldContext)
	{
		if (WorldContext)
			return GetPersistentLevelFName(WorldContext->GetWorld());
		return NAME_None;
	}

	FName FLibrary::GetPersistentLevelFNameChecked(const FString& Context, UWorld* World)
	{
		checkf(World, TEXT("%s: World is NULL."), *Context);

		const FString Name = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

		return FName(*Name);
	}

	FName FLibrary::GetPersistentLevelFNameChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		return GetPersistentLevelFNameChecked(Context, WorldContext->GetWorld());
	}

	bool FLibrary::IsPersistentLevelName(UWorld* World, const FString& MapPackageName)
	{
		if (!World)
			return false;

		return MapPackageName == UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
	}

	bool FLibrary::IsPersistentLevelName(UObject* WorldContext, const FString& MapPackageName)
	{
		if (!WorldContext)
			return false;

		return IsPersistentLevelName(WorldContext->GetWorld(), MapPackageName);
	}

	ALevelScriptActor* FLibrary::GetPersistentLevelScriptActor(UWorld* World)
	{
		if (ULevel* Level = GetPersistentLevel(World))
			return Level->LevelScriptActor;
		return nullptr;
	}

	ALevelScriptActor* FLibrary::GetPersistentLevelScriptActor(UObject* WorldContext)
	{
		return GetPersistentLevelScriptActor(WorldContext->GetWorld());
	}

	ALevelScriptActor* FLibrary::GetPersistentLevelScriptActorChecked(const FString& Context, UWorld* World)
	{
		checkf(World, TEXT("%s: World is NULL."), *Context);

		ULevel* Level = GetPersistentLevelChecked(Context, World);

		ALevelScriptActor* LevelScriptActor = Level->LevelScriptActor;

		checkf(LevelScriptActor, TEXT("%s: Failed to get LevelScriptActor from Persistent Level: %s."), *Context, *(Level->GetName()));

		return LevelScriptActor;
	}

	ALevelScriptActor* FLibrary::GetPersistentLevelScriptActorChecked(const FString& Context, UObject* WorldContext)
	{
		checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

		return GetPersistentLevelScriptActorChecked(Context, WorldContext->GetWorld());
	}

	#pragma endregion Persistent
}