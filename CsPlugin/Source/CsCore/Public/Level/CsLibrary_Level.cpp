// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Level/CsLibrary_Level.h"

// Library
#include "Library/CsLibrary_World.h"
// Level
#include "Engine/LevelScriptActor.h"
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
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafeName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafeFName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, SafeIsName);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsLevel::NPersistent::FLibrary, GetSafeScriptActor);
				}
			}
		}

		ULevel* FLibrary::GetChecked(const FString& Context, UWorld* World)
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

		ULevel* FLibrary::GetChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			return GetChecked(Context, WorldContext->GetWorld());
		}

		ULevel* FLibrary::GetSafe(const FString& Context, UWorld* World, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			if (!World)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: World is NULL."), *Context));
				return nullptr;
			}

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

		ULevel* FLibrary::GetSafe(UWorld* World)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, World, nullptr);
		}

		ULevel* FLibrary::GetSafe(const FString& Context, UObject* WorldContext, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			return GetSafe(Context, World, Log);
		}

		ULevel* FLibrary::GetSafe(UObject* WorldContext)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

			return GetSafe(Context, WorldContext, nullptr);
		}

		// Name
		#pragma region

		FString FLibrary::GetNameChecked(const FString& Context, UWorld* World)
		{
			checkf(World, TEXT("%s: World is NULL."), *Context);

			return UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		}

		FString FLibrary::GetNameChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			return GetNameChecked(Context, WorldContext->GetWorld());
		}

		FString FLibrary::GetSafeName(const FString& Context, UWorld* World, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			if (!World)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: World is NULL."), *Context));
				return FString();
			}

			FString Result = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			if (Result.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Persistent Level Name from World: %s."), *Context, *(World->GetName())));
			}
			return Result;
		}

		FString FLibrary::GetSafeName(UWorld* World)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafeName;

			return GetSafeName(Context, World, nullptr);
		}

		FString FLibrary::GetSafeName(const FString& Context, UObject* WorldContext, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);
			
			if (!World)
				return FString();

			return GetSafeName(Context, World, Log);
		}

		FString FLibrary::GetSafeName(UObject* WorldContext)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafeName;

			return GetSafeName(Context, WorldContext, nullptr);
		}

		#pragma endregion Name

		// FName
		#pragma region

		FName FLibrary::GetFNameChecked(const FString& Context, UWorld* World)
		{
			checkf(World, TEXT("%s: World is NULL."), *Context);

			const FString Name = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			return FName(*Name);
		}

		FName FLibrary::GetFNameChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			return GetFNameChecked(Context, WorldContext->GetWorld());
		}

		FName FLibrary::GetSafeFName(const FString& Context, UWorld* World, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			if (!World)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: World is NULL."), *Context));
				return NAME_None;
			}

			const FString Name = UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);

			if (Name.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Persistent Level Name from World: %s."), *Context, *(World->GetName())));
				return NAME_None;
			}
			return FName(*Name);
		}

		FName FLibrary::GetSafeFName(UWorld* World)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafeFName;

			return GetSafeFName(Context, World, nullptr);
		}

		FName FLibrary::GetSafeFName(const FString& Context, UObject* WorldContext, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return NAME_None;

			return GetSafeFName(World);
		}

		FName FLibrary::GetSafeFName(UObject* WorldContext)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafeFName;

			return GetSafeFName(Context, WorldContext, nullptr);
		}

		bool FLibrary::IsNameChecked(const FString& Context, UWorld* World, const FString& MapPackageName)
		{
			checkf(World, TEXT("World is NULL."), *Context);

			checkf(!MapPackageName.IsEmpty(), TEXT("MapPackageName is EMPTY."), *Context);

			return MapPackageName == UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		}

		bool FLibrary::IsNameChecked(const FString& Context, UObject* WorldContext, const FString& MapPackageName)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			return IsNameChecked(Context, WorldContext->GetWorld(), MapPackageName);
;		}

		bool FLibrary::SafeIsName(const FString& Context, UWorld* World, const FString& MapPackageName, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			if (!World)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: World is NULL."), *Context));
				return false;
			}

			if (MapPackageName.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: MapPackageName is EMPTY."), *Context));
				return false;
			}
			return MapPackageName == UWorld::StripPIEPrefixFromPackageName(World->GetOutermost()->GetName(), World->StreamingLevelsPrefix);
		}

		bool FLibrary::SafeIsName(UWorld* World, const FString& MapPackageName)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::SafeIsName;

			return SafeIsName(Context, World, MapPackageName, nullptr);
		}

		bool FLibrary::SafeIsName(const FString& Context, UObject* WorldContext, const FString& MapPackageName, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return false;

			if (MapPackageName.IsEmpty())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: MapPackageName is EMPTY."), *Context));
				return false;
			}
			return SafeIsName(Context, World, MapPackageName, Log);
		}

		bool FLibrary::SafeIsName(UObject* WorldContext, const FString& MapPackageName)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::SafeIsName;

			return SafeIsName(Context, WorldContext, MapPackageName, nullptr);
		}

		#pragma endregion FName

		// LevelScriptActor
		#pragma region

		FString FLibrary::PrintObjectAndClass(ALevelScriptActor* Actor)
		{
			return FString::Printf(TEXT("LevelScriptActor: %s with Class: %s"), *(Actor->GetName()), *(Actor->GetClass()->GetName()));
		}

		ALevelScriptActor* FLibrary::GetScriptActorChecked(const FString& Context, UWorld* World)
		{
			checkf(World, TEXT("%s: World is NULL."), *Context);

			ULevel* Level = GetChecked(Context, World);

			ALevelScriptActor* LevelScriptActor = Level->LevelScriptActor;

			checkf(LevelScriptActor, TEXT("%s: Failed to get LevelScriptActor from Persistent Level: %s."), *Context, *(Level->GetName()));

			return LevelScriptActor;
		}

		ALevelScriptActor* FLibrary::GetScriptActorChecked(const FString& Context, UObject* WorldContext)
		{
			checkf(WorldContext, TEXT("%s: WorldContext is NULL."), *Context);

			return GetScriptActorChecked(Context, WorldContext->GetWorld());
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(const FString& Context, UWorld* World, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
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

		ALevelScriptActor* FLibrary::GetSafeScriptActor(UWorld* World)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafeScriptActor;

			return GetSafeScriptActor(Context, World, nullptr);
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(const FString& Context, UObject* WorldContext, void(*Log)(const FString& Context) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

			if (!World)
				return nullptr;

			return GetSafeScriptActor(Context, World, Log);
		}

		ALevelScriptActor* FLibrary::GetSafeScriptActor(UObject* WorldContext)
		{
			using namespace NCsLevel::NPersistent::NLibrary::NCached;

			const FString& Context = Str::GetSafeScriptActor;

			return GetSafeScriptActor(Context, WorldContext, nullptr);
		}

		#pragma endregion LevelScriptActor
	}
}