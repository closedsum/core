// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Level/CsLibrary_Level.h"

// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Level
#include "Engine/Level.h"
#include "Engine/LevelScriptActor.h"
// Package
#include "UObject/Package.h"
// World
#include "Engine/World.h"

namespace NCsLevel
{
	namespace NPersistent
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					// Get
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafeName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafeFName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, SafeIsName);
					// LevelScriptActor
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafeScriptActor);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsLevel::NPersistent::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsLevel::NPersistent::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString& Context) /*=&NCsCore::NLibrary::FLog::Warning*/
		#define WorldLibrary NCsWorld::FLibrary

		// Get
		#pragma region

		ULevel* FLibrary::GetChecked(const FString& Context, const UWorld* World)
		{
			CS_IS_PTR_NULL_CHECKED(World)

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

		ULevel* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			return GetChecked(Context, WorldContext->GetWorld());
		}

		ULevel* FLibrary::GetSafe(const FString& Context, const UWorld* World, LogLevel)
		{
			CS_IS_PTR_NULL_RET_NULL(World)

			const TArray<ULevel*>& Levels = World->GetLevels();

			for (ULevel* Level : Levels)
			{
				if (Level->IsPersistentLevel())
				{
					return Level;
				}
			}
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Persistent Level from World: %s."), *Context, *(World->GetName())));
			return nullptr;
		}

		ULevel* FLibrary::GetSafe(const UWorld* World)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, World, nullptr);
		}

		ULevel* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;
			return GetSafe(Context, World, Log);
		}

		ULevel* FLibrary::GetSafe(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Name
		#pragma region

		FString FLibrary::GetNameChecked(const FString& Context, const UWorld* World)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			return UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		}

		FString FLibrary::GetNameChecked(const FString& Context, const UObject* WorldContext)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			return GetNameChecked(Context, WorldContext->GetWorld());
		}

		FString FLibrary::GetSafeName(const FString& Context, const UWorld* World, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_VALUE(World, FString())

			FString Result = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			if (Result.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Persistent Level Name from World: %s."), *Context, *(World->GetName())));
			}
			return Result;
		}

		FString FLibrary::GetSafeName(const UWorld* World)
		{
			SET_CONTEXT(GetSafeName);

			return GetSafeName(Context, World, nullptr);
		}

		FString FLibrary::GetSafeName(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);
			
			if (!World)
				return FString();
			return GetSafeName(Context, World, Log);
		}

		FString FLibrary::GetSafeName(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafeName);

			return GetSafeName(Context, WorldContext, nullptr);
		}

		FString FLibrary::GetLongPackageNameChecked(const FString& Context, const UObject* WorldContext)
		{
			const FString LevelPath = GetNameChecked(Context, WorldContext);

			int32 Index;
			LevelPath.FindLastChar('/', Index);

			const FString LevelName = LevelPath.Right(LevelPath.Len() - Index - 1);

			return LevelPath;
		}

		FString FLibrary::GetSafeLongPackageName(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			const FString LevelPath = GetSafeName(Context, WorldContext, Log);

			if (LevelPath.IsEmpty())
				return FString();

			int32 Index;
			LevelPath.FindLastChar('/', Index);

			if (Index == INDEX_NONE)
				return FString();

			const FString LevelName = LevelPath.Right(LevelPath.Len() - Index - 1);

			return LevelPath;
		}

		#pragma endregion Name

		// FName
		#pragma region

		FName FLibrary::GetFNameChecked(const FString& Context, const UWorld* World)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			const FString NameAsString = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			checkf(!NameAsString.IsEmpty(), TEXT("%s: Failed to get Persistent Level Name from World: %s."), *Context, *(World->GetName()));
			
			const FName Name = FName(*NameAsString);

			CS_IS_NAME_NONE_CHECKED(Name)
			return Name;
		}

		FName FLibrary::GetFNameChecked(const FString& Context, const UObject* WorldContext)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			return GetFNameChecked(Context, WorldContext->GetWorld());
		}

		FName FLibrary::GetSafeFName(const FString& Context, const UWorld* World, LogLevel)
		{
			CS_IS_PENDING_KILL_RET_VALUE(World, NAME_None)

			const FString NameAsString = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			if (NameAsString.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Persistent Level Name from World: %s."), *Context, *(World->GetName())));
				return NAME_None;
			}

			const FName Name = FName(*NameAsString);

			CS_IS_NAME_NONE_RET_VALUE(Name, NAME_None)
			return Name;
		}

		FName FLibrary::GetSafeFName(const UWorld* World)
		{
			SET_CONTEXT(GetSafeFName);

			return GetSafeFName(Context, World, nullptr);
		}

		FName FLibrary::GetSafeFName(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return NAME_None;
			return GetSafeFName(World);
		}

		FName FLibrary::GetSafeFName(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafeFName);

			return GetSafeFName(Context, WorldContext, nullptr);
		}

		bool FLibrary::IsNameChecked(const FString& Context, const UWorld* World, const FString& MapPackageName)
		{
			CS_IS_PTR_NULL_CHECKED(World)
			CS_IS_STRING_EMPTY_CHECKED(MapPackageName)

			return MapPackageName == UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		}

		bool FLibrary::IsNameChecked(const FString& Context, const UObject* WorldContext, const FString& MapPackageName)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			return IsNameChecked(Context, WorldContext->GetWorld(), MapPackageName);
;		}

		bool FLibrary::SafeIsName(const FString& Context, const UWorld* World, const FString& MapPackageName, LogLevel)
		{
			CS_IS_PTR_NULL(World)
			CS_IS_STRING_EMPTY(MapPackageName)

			return MapPackageName == UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		}

		bool FLibrary::SafeIsName(const UWorld* World, const FString& MapPackageName)
		{
			SET_CONTEXT(SafeIsName);

			return SafeIsName(Context, World, MapPackageName, nullptr);
		}

		bool FLibrary::SafeIsName(const FString& Context, const UObject* WorldContext, const FString& MapPackageName, LogLevel)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return false;

			CS_IS_STRING_EMPTY(MapPackageName)

			return SafeIsName(Context, World, MapPackageName, Log);
		}

		bool FLibrary::SafeIsName(const UObject* WorldContext, const FString& MapPackageName)
		{
			SET_CONTEXT(SafeIsName);

			return SafeIsName(Context, WorldContext, MapPackageName, nullptr);
		}

		#pragma endregion FName

		// Path
		#pragma region

		bool FLibrary::IsPathChecked(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path)
		{
			const FString MapPackageName = GetLongPackageNameChecked(Context, WorldContext);

			CS_IS_SOFT_OBJECT_PATH_VALID_CHECKED(Path)

			const FString URL = Path.GetLongPackageName();

			return MapPackageName == URL;
		}

		bool FLibrary::SafeIsPath(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, LogLevel)
		{
			const FString MapPackageName = GetSafeLongPackageName(Context, WorldContext, Log);

			if (MapPackageName.IsEmpty())
				return false;

			CS_IS_SOFT_OBJECT_PATH_VALID(Path)

			const FString URL = Path.GetLongPackageName();

			return MapPackageName == URL;
		}

		#pragma endregion Path

		// LevelScriptActor
		#pragma region

		FString FLibrary::PrintObjectAndClass(ALevelScriptActor* Actor)
		{
			return FString::Printf(TEXT("LevelScriptActor: %s with Class: %s"), *(Actor->GetName()), *(Actor->GetClass()->GetName()));
		}

		ALevelScriptActor* FLibrary::GetScriptActorChecked(const FString& Context, const UWorld* World)
		{
			CS_IS_PTR_NULL_CHECKED(World)

			ULevel* Level						= GetChecked(Context, World);
			ALevelScriptActor* LevelScriptActor = Level->LevelScriptActor;

			checkf(LevelScriptActor, TEXT("%s: Failed to get LevelScriptActor from Persistent Level: %s."), *Context, *(Level->GetName()));
			return LevelScriptActor;
		}

		ALevelScriptActor* FLibrary::GetScriptActorChecked(const FString& Context, const UObject* WorldContext)
		{
			CS_IS_PTR_NULL_CHECKED(WorldContext)

			return GetScriptActorChecked(Context, WorldContext->GetWorld());
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(const FString& Context, const UWorld* World, LogLevel)
		{
			if (ULevel* Level = GetSafe(Context, World, Log))
			{
				if (!Level->LevelScriptActor)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Level: %s does NOT have a LevelScriptActor."), *Context, *(Level->GetName())));
					return nullptr;
				}
				return Level->LevelScriptActor;
			}
			return nullptr;
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(const UWorld* World)
		{
			SET_CONTEXT(GetSafeScriptActor);

			return GetSafeScriptActor(Context, World, nullptr);
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;
			return GetSafeScriptActor(Context, World, Log);
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafeScriptActor);

			return GetSafeScriptActor(Context, WorldContext, nullptr);
		}

		#pragma endregion LevelScriptActor

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
		#undef WorldLibrary
	}
}