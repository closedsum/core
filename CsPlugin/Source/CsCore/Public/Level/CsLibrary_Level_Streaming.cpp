// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Level/CsLibrary_Level_Streaming.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_World.h"
#include "Library/CsLibrary_Valid.h"
// Level
#include "Engine/Level.h"
#include "Engine/LevelStreaming.h"
#include "Engine/LevelStreamingDynamic.h"
#include "Engine/LevelScriptActor.h"
#include "Level/CsLevel_Delegates.h"
// Player
#include "GameFramework/PlayerController.h"
// World
#include "Engine/World.h"

namespace NCsLevel
{
	namespace NStreaming
	{
		namespace NLocal
		{
			#define WorldLibrary NCsWorld::FLibrary

			// Is
			#pragma region
			
			bool FLibrary::SafeIs(const FString& Context, const UObject* WorldContext, const TSoftObjectPtr<UWorld>& Level, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				const FName LevelName = GetSafeName(Context, Level, Log);

				if (LevelName == NAME_None)
					return false;

				ULevelStreaming* LevelStreamingObject = SafeFindAndCacheObject(Context, WorldContext, LevelName, Log);

				if (!LevelStreamingObject)
					return false;
				return true;
			}

			#pragma endregion Is

			FName FLibrary::GetNameChecked(const FString& Context, const TSoftObjectPtr<UWorld>& Level)
			{
				CS_IS_SOFT_OBJECT_PTR_VALID_CHECKED(Level, UWorld)

				const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));

				CS_IS_NAME_NONE_CHECKED(LevelName)
				return LevelName;
			}

			FName FLibrary::GetSafeName(const FString& Context, const TSoftObjectPtr<UWorld>& Level, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				OutSuccess = false;

				CS_IS_SOFT_OBJECT_PTR_VALID_RET_VALUE(Level, UWorld, NAME_None)

				const FName LevelName = FName(*FPackageName::ObjectPathToPackageName(Level.ToString()));

				CS_IS_NAME_NONE_RET_VALUE(LevelName, NAME_None)

				OutSuccess = true;
				return LevelName;
			}

			FString FLibrary::MakeSafeLevelNameChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName)
			{
				CS_IS_NAME_NONE_CHECKED(LevelName)

				UWorld* World = WorldLibrary::GetChecked(Context, WorldContext);
				
				// Special case for PIE, the PackageName gets mangled.
				if (!World->StreamingLevelsPrefix.IsEmpty())
				{
					FString PackageName = FPackageName::GetShortName(LevelName);
					if (!PackageName.StartsWith(World->StreamingLevelsPrefix))
					{
						PackageName = World->StreamingLevelsPrefix + PackageName;
					}

					if (!FPackageName::IsShortPackageName(LevelName))
					{
						PackageName = FPackageName::GetLongPackagePath(LevelName.ToString()) + TEXT("/") + PackageName;
					}
					return PackageName;
				}
				return LevelName.ToString();
			}

			FString FLibrary::SafeMakeSafeLevelName(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				OutSuccess = false;

				CS_IS_NAME_NONE_RET_VALUE(LevelName, FString())

				UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);

				if (!World)
					return FString();

				// Special case for PIE, the PackageName gets mangled.
				if (!World->StreamingLevelsPrefix.IsEmpty())
				{
					FString PackageName = FPackageName::GetShortName(LevelName);
					if (!PackageName.StartsWith(World->StreamingLevelsPrefix))
					{
						PackageName = World->StreamingLevelsPrefix + PackageName;
					}

					if (!FPackageName::IsShortPackageName(LevelName))
					{
						PackageName = FPackageName::GetLongPackagePath(LevelName.ToString()) + TEXT("/") + PackageName;
					}

					OutSuccess = true;
					return PackageName;
				}

				OutSuccess = true;
				return LevelName.ToString();
			}

			FString FLibrary::GetSearchPackageNameChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName)
			{
				// Search for the level object by name.
				FString SearchPackageName = MakeSafeLevelNameChecked(Context, WorldContext, LevelName);
	
				if (FPackageName::IsShortPackageName(SearchPackageName))
				{
					// Make sure MyMap1 and Map1 names do not resolve to a same streaming level
					SearchPackageName = TEXT("/") + SearchPackageName;
				}
				return SearchPackageName;
			}

			FString FLibrary::GetSafeSearchPackageName(const FString& Context, const UObject* WorldContext, const FName& LevelName, bool& OutSuccess, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				// Search for the level object by name.
				FString SearchPackageName = SafeMakeSafeLevelName(Context, WorldContext, LevelName, OutSuccess, Log);
	
				if (!OutSuccess)
					return FString();

				if (FPackageName::IsShortPackageName(SearchPackageName))
				{
					// Make sure MyMap1 and Map1 names do not resolve to a same streaming level
					SearchPackageName = TEXT("/") + SearchPackageName;
				}
				return SearchPackageName;
			}

			ULevelStreaming* FLibrary::FindAndCacheObjectChecked(const FString& Context, const UObject* WorldContext, const FName& LevelName)
			{
				CS_IS_NAME_NONE_CHECKED(LevelName)

				// Search for the level object by name.
				FString SearchPackageName = GetSearchPackageNameChecked(Context, WorldContext, LevelName);
				UWorld* World			  = WorldLibrary::GetChecked(Context, WorldContext);

				for (ULevelStreaming* LevelStreaming : World->GetStreamingLevels())
				{
					// We check only suffix of package name, to handle situations when packages were saved for play into a temporary folder
					// Like Saved/Autosaves/PackageName
					if (IsValid(LevelStreaming) && 
						LevelStreaming->GetWorldAssetPackageName().EndsWith(SearchPackageName, ESearchCase::IgnoreCase))
					{
						return LevelStreaming;
					}
				}
				checkf(0, TEXT("%s: Failed to find Streaming Level with LevelName: %s in World: %s."), *Context, *(LevelName.ToString()), *(World->GetMapName()));
				return nullptr;
			}

			ULevelStreaming* FLibrary::SafeFindAndCacheObject(const FString& Context, const UObject* WorldContext, const FName& LevelName, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				// Search for the level object by name.
				FString SearchPackageName = GetSafeSearchPackageName(Context, WorldContext, LevelName, Log);

				if (SearchPackageName.IsEmpty())
					return nullptr;

				UWorld* World = WorldLibrary::GetSafe(Context, WorldContext, Log);
					
				if (!World)
					return nullptr;

				for (ULevelStreaming* LevelStreaming : World->GetStreamingLevels())
				{
					// We check only suffix of package name, to handle situations when packages were saved for play into a temporary folder
					// Like Saved/Autosaves/PackageName
					if (IsValid(LevelStreaming) && 
						LevelStreaming->GetWorldAssetPackageName().EndsWith(SearchPackageName, ESearchCase::IgnoreCase))
					{
						return LevelStreaming;
					}
				}
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to find Streaming Level with LevelName: %s in World: %s."), *Context, *(LevelName.ToString()), *(World->GetMapName())));
				return nullptr;
			}

			// Load
			#pragma region

			#define LoadParamsType NCsLevel::NStreaming::NLocal::NLoad::FParams

			void FLibrary::LoadChecked(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params)
			{
				CS_IS_VALID_CHECKED(Params);

				const FName LevelName				  = GetNameChecked(Context, Params.Level);
				ULevelStreaming* LevelStreamingObject = FindAndCacheObjectChecked(Context, WorldContext, LevelName);

				const bool& bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
				const bool& bShouldBlock		  = Params.bShouldBlock;

				UE_LOG(LogStreaming, Log, TEXT("Streaming in level %s (%s)..."),*LevelStreamingObject->GetName(),*LevelStreamingObject->GetWorldAssetPackageName());
				
				LevelStreamingObject->SetShouldBeLoaded(true);
				LevelStreamingObject->SetShouldBeVisible(LevelStreamingObject->GetShouldBeVisibleFlag()	|| bMakeVisibleAfterLoad);
				LevelStreamingObject->bShouldBlockOnLoad = bShouldBlock;

				UWorld* LevelWorld = LevelStreamingObject->GetWorld();

				checkf(LevelWorld, TEXT("%s: No world associated with LevelStreamingObject: %s."), *Context, *(LevelStreamingObject->GetWorldAssetPackageName()));

				const bool bShouldBeLoaded  = LevelStreamingObject->ShouldBeLoaded();
				const bool bShouldBeVisible = LevelStreamingObject->ShouldBeVisible();

				UE_LOG(LogLevel, Log, TEXT("ActivateLevel %s %i %i %i"),
					*LevelStreamingObject->GetWorldAssetPackageName(),
					bShouldBeLoaded,
					bShouldBeVisible,
					bShouldBlock);

				// Notify players of the change
				for (FConstPlayerControllerIterator Iterator = LevelWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					if (APlayerController* PlayerController = Iterator->Get())
					{
						PlayerController->LevelStreamingStatusChanged(
							LevelStreamingObject,
							bShouldBeLoaded,
							bShouldBeVisible,
							bShouldBlock,
							INDEX_NONE);
					}
				}
			}

			bool FLibrary::SafeLoad(const FString& Context, const UObject* WorldContext, const LoadParamsType& Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_VALID(Params)

				const FName LevelName = GetSafeName(Context, Params.Level, Log);

				if (LevelName == NAME_None)
					return false;

				ULevelStreaming* LevelStreamingObject = SafeFindAndCacheObject(Context, WorldContext, LevelName, Log);

				if (!LevelStreamingObject)
					return false;

				const bool& bMakeVisibleAfterLoad = Params.bMakeVisibleAfterLoad;
				const bool& bShouldBlock		  = Params.bShouldBlock;

				UE_LOG(LogStreaming, Log, TEXT("Streaming in level %s (%s)..."),*LevelStreamingObject->GetName(),*LevelStreamingObject->GetWorldAssetPackageName());
				
				LevelStreamingObject->SetShouldBeLoaded(true);
				LevelStreamingObject->SetShouldBeVisible(LevelStreamingObject->GetShouldBeVisibleFlag()	|| bMakeVisibleAfterLoad);
				LevelStreamingObject->bShouldBlockOnLoad = bShouldBlock;

				UWorld* LevelWorld = LevelStreamingObject->GetWorld();

				if (!LevelWorld)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No world associated with LevelStreamingObject: %s."), *Context, *(LevelStreamingObject->GetWorldAssetPackageName())));
					return false;
				}

				const bool bShouldBeLoaded  = LevelStreamingObject->ShouldBeLoaded();
				const bool bShouldBeVisible = LevelStreamingObject->ShouldBeVisible();

				UE_LOG(LogLevel, Log, TEXT("ActivateLevel %s %i %i %i"),
					*LevelStreamingObject->GetWorldAssetPackageName(),
					bShouldBeLoaded,
					bShouldBeVisible,
					bShouldBlock);

				// Notify players of the change
				for (FConstPlayerControllerIterator Iterator = LevelWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					if (APlayerController* PlayerController = Iterator->Get())
					{
						PlayerController->LevelStreamingStatusChanged(
							LevelStreamingObject,
							bShouldBeLoaded,
							bShouldBeVisible,
							bShouldBlock,
							INDEX_NONE);
					}
				}
				return true;
			}

			#undef LoadParamsType

			#pragma endregion Load

			// Unload
			#pragma region

			#define UnloadParamsType NCsLevel::NStreaming::NLocal::NUnload::FParams

			void FLibrary::UnloadChecked(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params)
			{
				CS_IS_VALID_CHECKED(Params);

				const FName LevelName				  = GetNameChecked(Context, Params.Level);
				ULevelStreaming* LevelStreamingObject = FindAndCacheObjectChecked(Context, WorldContext, LevelName);

				const bool& bShouldBlock = Params.bShouldBlock;

				UE_LOG(LogStreaming, Log, TEXT("Streaming out level %s (%s)..."),*LevelStreamingObject->GetName(),*LevelStreamingObject->GetWorldAssetPackageName());
				
				LevelStreamingObject->SetShouldBeLoaded(false);
				LevelStreamingObject->SetShouldBeVisible(false);
				LevelStreamingObject->bShouldBlockOnUnload = bShouldBlock;

				UWorld* LevelWorld = LevelStreamingObject->GetWorld();

				checkf(LevelWorld, TEXT("%s: No world associated with LevelStreamingObject: %s."), *Context, *(LevelStreamingObject->GetWorldAssetPackageName()));

				const bool bShouldBeLoaded  = LevelStreamingObject->ShouldBeLoaded();
				const bool bShouldBeVisible = LevelStreamingObject->ShouldBeVisible();

				UE_LOG(LogLevel, Log, TEXT("ActivateLevel %s %i %i %i"),
					*LevelStreamingObject->GetWorldAssetPackageName(),
					bShouldBeLoaded,
					bShouldBeVisible,
					bShouldBlock);

				// Notify players of the change
				for (FConstPlayerControllerIterator Iterator = LevelWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					if (APlayerController* PlayerController = Iterator->Get())
					{
						PlayerController->LevelStreamingStatusChanged(
							LevelStreamingObject,
							bShouldBeLoaded,
							bShouldBeVisible,
							bShouldBlock,
							INDEX_NONE);
					}
				}
			}

			bool FLibrary::SafeUnload(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
			{
				CS_IS_VALID(Params)

				const FName LevelName = GetSafeName(Context, Params.Level, Log);

				if (LevelName == NAME_None)
					return false;

				ULevelStreaming* LevelStreamingObject = SafeFindAndCacheObject(Context, WorldContext, LevelName, Log);

				if (!LevelStreamingObject)
					return false;

				const bool& bShouldBlock = Params.bShouldBlock;

				UE_LOG(LogStreaming, Log, TEXT("Streaming out level %s (%s)..."),*LevelStreamingObject->GetName(),*LevelStreamingObject->GetWorldAssetPackageName());
				
				LevelStreamingObject->SetShouldBeLoaded(false);
				LevelStreamingObject->SetShouldBeVisible(false);
				LevelStreamingObject->bShouldBlockOnUnload = bShouldBlock;

				UWorld* LevelWorld = LevelStreamingObject->GetWorld();

				if (!LevelWorld)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: No world associated with LevelStreamingObject: %s."), *Context, *(LevelStreamingObject->GetWorldAssetPackageName())));
					return false;
				}

				const bool bShouldBeLoaded  = LevelStreamingObject->ShouldBeLoaded();
				const bool bShouldBeVisible = LevelStreamingObject->ShouldBeVisible();

				UE_LOG(LogLevel, Log, TEXT("ActivateLevel %s %i %i %i"),
					*LevelStreamingObject->GetWorldAssetPackageName(),
					bShouldBeLoaded,
					bShouldBeVisible,
					bShouldBlock);

				// Notify players of the change
				for (FConstPlayerControllerIterator Iterator = LevelWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					if (APlayerController* PlayerController = Iterator->Get())
					{
						PlayerController->LevelStreamingStatusChanged(
							LevelStreamingObject,
							bShouldBeLoaded,
							bShouldBeVisible,
							bShouldBlock,
							INDEX_NONE);
					}
				}
				return true;
			}

			#undef UnloadParamsType

			#pragma endregion Unload

			#undef WorldLibrary
		}		
	}

	namespace NStreaming
	{
		namespace NDynamic
		{
			#define WorldLibrary NCsWorld::FLibrary

			// Load
			#pragma region

			#define LoadParamsType NCsLevel::NStreaming::NDynamic::NLoad::FParams

			void FLibrary::LoadChecked(const FString& Context, UObject* WorldContext, const LoadParamsType& Params)
			{
				CS_IS_VALID_CHECKED(Params);

				bool OutSuccess = false;
				ULevelStreamingDynamic* LevelStreaming = ULevelStreamingDynamic::LoadLevelInstanceBySoftObjectPtr(WorldContext, Params.Level, FTransform::Identity, OutSuccess);

				checkf(OutSuccess, TEXT("%s: Failed to Load Streaming Level: %s."), *Context, *(Params.Level.ToString()));

				NCsLevel::NStreaming::NDynamic::FDelegates::OnAdded_Event.Broadcast(WorldLibrary::GetChecked(Context, WorldContext), LevelStreaming);
			}

			#undef LoadParamsType

			#pragma endregion Load

			// Unload
			#pragma region

			#define LocalLibrary NCsLevel::NStreaming::NLocal::FLibrary
			#define UnloadParamsType NCsLevel::NStreaming::NDynamic::NUnload::FParams

			void FLibrary::UnloadChecked(const FString& Context, const UObject* WorldContext, const UnloadParamsType& Params)
			{
				CS_IS_VALID_CHECKED(Params);

				const FName LevelName				  = LocalLibrary::GetNameChecked(Context, Params.Level);
				ULevelStreaming* LevelStreamingObject = LocalLibrary::FindAndCacheObjectChecked(Context, WorldContext, LevelName);

				const bool& bShouldBlock = Params.bShouldBlock;

				UE_LOG(LogStreaming, Log, TEXT("Streaming out level %s (%s)..."),*LevelStreamingObject->GetName(),*LevelStreamingObject->GetWorldAssetPackageName());
				
				LevelStreamingObject->SetShouldBeLoaded(false);
				LevelStreamingObject->SetShouldBeVisible(false);
				LevelStreamingObject->bShouldBlockOnUnload = bShouldBlock;
				LevelStreamingObject->SetIsRequestingUnloadAndRemoval(true);

				UWorld* LevelWorld = LevelStreamingObject->GetWorld();

				checkf(LevelWorld, TEXT("%s: No world associated with LevelStreamingObject: %s."), *Context, *(LevelStreamingObject->GetWorldAssetPackageName()));

				const bool bShouldBeLoaded  = LevelStreamingObject->ShouldBeLoaded();
				const bool bShouldBeVisible = LevelStreamingObject->ShouldBeVisible();

				UE_LOG(LogLevel, Log, TEXT("ActivateLevel %s %i %i %i"),
					*LevelStreamingObject->GetWorldAssetPackageName(),
					bShouldBeLoaded,
					bShouldBeVisible,
					bShouldBlock);

				// Notify players of the change
				for (FConstPlayerControllerIterator Iterator = LevelWorld->GetPlayerControllerIterator(); Iterator; ++Iterator)
				{
					if (APlayerController* PlayerController = Iterator->Get())
					{
						PlayerController->LevelStreamingStatusChanged(
							LevelStreamingObject,
							bShouldBeLoaded,
							bShouldBeVisible,
							bShouldBlock,
							INDEX_NONE);
					}
				}
			}

			#undef LocalLibrary
			#undef UnloadParamsType

			#pragma endregion Unload

			#undef WorldLibrary
		}
	}

	namespace NStreaming
	{
		// LevelScriptActor
		#pragma region

		ALevelScriptActor* FLibrary::GetLevelScriptActorChecked(const FString& Context, ULevelStreaming* LevelStreaming)
		{
			CS_IS_PENDING_KILL_CHECKED(LevelStreaming)

			ALevelScriptActor* LSA = LevelStreaming->GetLevelScriptActor();

			CS_IS_PENDING_KILL_CHECKED(LSA);
			return LSA;
		}

		#pragma endregion LevelScriptActor

		const FName& FLibrary::GetPackageNameToLoadChecked(const FString& Context, ULevelStreaming* LevelStreaming)
		{
			CS_IS_PENDING_KILL_CHECKED(LevelStreaming)

			return LevelStreaming->PackageNameToLoad;
		}

		const TArray<AActor*>& FLibrary::GetActorsChecked(const FString& Context, ULevelStreaming* LevelStreaming)
		{
			CS_IS_PENDING_KILL_CHECKED(LevelStreaming)

			ULevel* Level = LevelStreaming->GetLoadedLevel();

			CS_IS_PENDING_KILL_CHECKED(Level)

			return Level->Actors;
		}
	}
}