// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Engine/EngineBaseTypes.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UWorld;
class UObject;

namespace NCsWorld
{
	struct CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static FString PrintActorAndClass(const AActor* Object);

	// Get
	#pragma region
	public:

		/**
		* Get World from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				World
		*/
		static UWorld* GetChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get World from WorldContext.
		* 
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				World
		*/
		static UWorld* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

		/**
		* Safely get World from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				World
		*/
		static UWorld* GetSafe(const UObject* WorldContext);

		/**
		* Get World as UObject from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				World
		*/
		static UObject* GetAsObjectChecked(const FString& Context, const UObject* WorldContext);

		/**
		* Safely get World as UObject from WorldContext.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* @param Log			(optional)
		* return				World as UObject
		*/
		static UObject* GetSafeAsObject(const FString& Context, const UObject* WorldContext, LogLevel);

		/**
		* Safely get World as UObject from WorldContext.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				World as UObject
		*/
		static UObject* GetSafeAsObject(const UObject* WorldContext);

	#pragma endregion Get

	// WorldType
	#pragma region
	public:

		static bool IsGameWorld(UWorld* World);

		static bool IsPlayInGame(UWorld* World);

		static bool IsPlayInEditor(UWorld* World);

		static bool IsPlayInEditor(const UObject* WorldContext);

		static bool IsPlayInPIE(UWorld* World);

		static bool IsPlayInPIE(const UObject* WorldContext);

		static bool IsPlayInEditorPreview(UWorld* World);

		static bool IsPlayInEditorPreview(const UObject* WorldContext);

		static bool IsPlayInGameOrPIE(UWorld* World);

		static bool IsPlayInGameOrPIE(const UObject* WorldContext);

		static bool IsPlayInEditorOrEditorPreview(UWorld* World);

		static bool IsPlayInEditorOrEditorPreview(const UObject* WorldContext);

		static bool IsAnyWorldContextEditorOrEditorPreview();

		static bool IsEditorPreviewOrphaned(UObject* WorldContext);

	#pragma endregion WorldType

	public:

		static const FString& GetStreamingLevelsPrefixChecked(const FString& Context, const UObject* WorldContext);

	// Spawn
	#pragma region
	public:

		static AActor* SpawnChecked(const FString& Context, const UObject* WorldContext, UClass* Class);

		template<typename T>
		static T* SpawnChecked(const FString& Context, const UObject* WorldContext)
		{
			AActor* A = SpawnChecked(Context, WorldContext, T::StaticClass());
			T* Other  = Cast<T>(A);

			checkf(Other, TEXT("%s: %s is NOT a Child of: %s."), *Context, *PrintActorAndClass(A), *(T::StaticClass()->GetName()));
			return Other;
		}

	#pragma endregion Spawn

	#undef LogLevel
	};

	namespace NSeamlessTravelHandler
	{
		struct CSCORELIBRARY_API FLibrary final
		{
		public:

			static void SetHandlerLoadedData(UWorld* World, UObject* InLevelPackage, UWorld* InLoadedWorld);

			static void SeamlessTravelLoadCallback(UWorld* World, const FString& PackageName);

			static bool IsInTransition(const UWorld* World);

		// PendingTravelURL
			static FURL GetPendingTravelURL(UWorld* World);
		// LoadedPackage
			static bool HasLoadedPackage(UWorld* World);
		// bTransitionInProgress
			static bool* GetbTransitionInProgress(UWorld* World);
			static void EnableTransitionInProgress(UWorld* World);
			static void DisableTransitionInProgress(UWorld* World);
		};
	}

	namespace NPIE
	{
		class CSCORELIBRARY_API FLibrary final
		{
		public:

			static void EnableSeamlessTravelChecked(const FString& Context);
		};
	}
}

using CsWorldLibrary = NCsWorld::FLibrary;
using CsSeamlessTravelHandlerLibrary = NCsWorld::NSeamlessTravelHandler::FLibrary;