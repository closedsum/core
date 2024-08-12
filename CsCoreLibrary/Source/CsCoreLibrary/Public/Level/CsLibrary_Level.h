// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Misc.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class ULevel;
class UWorld;
class UObject;
class ALevelScriptActor;

namespace NCsLevel
{
	namespace NPersistent
	{
		struct CSCORELIBRARY_API FLibrary final
		{
		#define LogLevel void(*Log)(const FString& Context) = &NCsCore::NLibrary::FLog::Warning

		// Get
		#pragma region
		public:

			/**
			* Get the current Persistent Level.
			*
			* @param Context	The calling context
			* @param World
			* return			Level
			*/
			static ULevel* GetChecked(const FString& Context, const UWorld* World);

			/**
			* Get the current Persistent Level.
			*
			* @param Context		The calling context
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level
			*/
			static ULevel* GetChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the current Persistent Level.
			*
			* @param World
			* return		Level
			*/
			static ULevel* GetSafe(const FString& Context, const UWorld* World, LogLevel);

			/**
			* Get the current Persistent Level.
			*
			* @param World
			* return		Level
			*/
			static ULevel* GetSafe(const UWorld* World);

			/**
			* Get the current Persistent Level.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level
			*/
			static ULevel* GetSafe(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			* Get the current Persistent Level.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return		Level
			*/
			static ULevel* GetSafe(const UObject* WorldContext);

		#pragma endregion Get

		// Name
		#pragma region
		public:

			/**
			* Get the current Persistent Level's name as a FString.
			*
			* @param Context	The calling context.
			* @param World
			* return			Level name
			*/
			static FString GetNameChecked(const FString& Context, const UWorld* World);

			/**
			* Get the current Persistent Level's name as a FString.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level name
			*/
			static FString GetNameChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the current Persistent Level's name as a FString.
			*
			* @param Context	The calling context.
			* @param World
			* @param Log
			* return			Level name
			*/
			static FString GetSafeName(const FString& Context, const UWorld* World, LogLevel);

			/**
			* Get the current Persistent Level's name as a FString.
			*
			* @param World
			* return			Level name
			*/
			static FString GetSafeName(const UWorld* World);

			/**
			* Get the current Persistent Level's name as a FString.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Level name
			*/
			static FString GetSafeName(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			* Get the current Persistent Level's name as a FString.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level name
			*/
			static FString GetSafeName(const UObject* WorldContext);

			/**
			* Get the Long Package Name for the Persistent Level. This is usually in the form:
			* LevelPath.LevelName
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				LevelPath.LevelName
			*/
			static FString GetLongPackageNameChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the Long Package Name for the Persistent Level. This is usually in the form:
			* LevelPath.LevelName
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				LevelPath.LevelName
			*/
			static FString GetSafeLongPackageName(const FString& Context, const UObject* WorldContext, LogLevel);

		#pragma endregion Name

		// FName
		#pragma region
		public:

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param Context	The calling context.
			* @param World
			* return			Level name
			*/
			static FName GetFNameChecked(const FString& Context, const UWorld* World);

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level name
			*/
			static FName GetFNameChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param Context	The calling context.
			* @param World
			* @param Log
			* return			Level name
			*/
			static FName GetSafeFName(const FString& Context, const UWorld* World, LogLevel);

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param World
			* return			Level name
			*/
			static FName GetSafeFName(const UWorld* World);

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				Level name
			*/
			static FName GetSafeFName(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level name
			*/
			static FName GetSafeFName(const UObject* WorldContext);

			/**
			*/
			static bool IsNameChecked(const FString& Context, const UWorld* World, const FString& MapPackageName);

			/**
			*/
			static bool IsNameChecked(const FString& Context, const UObject* WorldContext, const FString& MapPackageName);

			/**
			*/
			static bool SafeIsName(const FString& Context, const UWorld* World, const FString& MapPackageName, LogLevel);

			/**
			*/
			static bool SafeIsName(const UWorld* World, const FString& MapPackageName);

			/**
			*/
			static bool SafeIsName(const FString& Context, const UObject* WorldContext, const FString& MapPackageName, LogLevel);

			/**
			*/
			static bool SafeIsName(const UObject* WorldContext, const FString& MapPackageName);

		#pragma endregion FName

		// Path
		#pragma region
		public:

			/**
			* Check if Path is Current Persistent Level.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Path
			* return				Whether Path is the Current Persistent Level or not.
			*/
			static bool IsPathChecked(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path);

			/**
			* Safely check if Path is Current Persistent Level.
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Path
			* @param Log			(optional)
			* return				Whether Path is the Current Persistent Level or not.
			*/
			static bool SafeIsPath(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, LogLevel);

		#pragma endregion Path

		// LevelScriptActor
		#pragma region
		public:

			static FString PrintObjectAndClass(ALevelScriptActor* Actor);

			/**
			* Get the LevelScriptActor from the current Persistent Level.
			*
			* @param Context	The calling context.
			* @param World
			* return			LevelScriptActor
			*/
			static ALevelScriptActor* GetScriptActorChecked(const FString& Context, const UWorld* World);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param Context	The calling context.
			* @param World
			* return			LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetScriptActorChecked(const FString& Context, const UWorld* World)
			{
				T* Slice = Cast<T>(GetScriptActorChecked(Context, World));

				checkf(Slice, TEXT("%s: Failed to cast LevelScriptActor to type: T."), *Context);

				return Slice;
			}

			/**
			* Get the LevelScriptActor from the current Persistent Level.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				LevelScriptActor
			*/
			static ALevelScriptActor* GetScriptActorChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetScriptActorChecked(const FString& Context, const UObject* WorldContext)
			{
				T* Slice = Cast<T>(GetScriptActorChecked(Context, WorldContext));

				checkf(Slice, TEXT("%s: Failed to cast LevelScriptActor to type: T."), *Context);

				return Slice;
			}

			/**
			* Get the LevelScriptActor from the current Persistent Level.
			*
			* @param Context	The calling context.
			* @param World
			* @param Log
			* return			LevelScriptActor
			*/
			static ALevelScriptActor* GetSafeScriptActor(const FString& Context, const UWorld* World, LogLevel);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param Context	The calling context.
			* @param World
			* @param Log
			* return			LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeScriptActor(const FString& Context, const UWorld* World, LogLevel)
			{
				ALevelScriptActor* Actor = GetSafeScriptActor(Context, World, Log);

				if (!Actor)
					return nullptr;

				T* Other = Cast<T>(Actor);

				if (!Other)
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to cast %s is NOT of type: %s."), *Context, *PrintObjectAndClass(Actor), *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Get the LevelScriptActor from the current Persistent Level.
			*
			* @param World
			* return			LevelScriptActor
			*/
			static ALevelScriptActor* GetSafeScriptActor(const UWorld* World);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param World
			* return			LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeScriptActor(const UWorld* World)
			{
				return Cast<T>(GetSafeScriptActor(World));
			}

			/**
			* Get the LevelScriptActor from the current Persistent Level.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				LevelScriptActor
			*/
			static ALevelScriptActor* GetSafeScriptActor(const FString& Context, const UObject* WorldContext, LogLevel);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeScriptActor(const FString& Context, const UObject* WorldContext, LogLevel)
			{
				return Cast<T>(GetSafeScriptActor(Context, WorldContext, Log));
			}

			/**
			* Get the LevelScriptActor from the current Persistent Level.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				LevelScriptActor
			*/
			static ALevelScriptActor* GetSafeScriptActor(const UObject* WorldContext);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeScriptActor(const UObject* WorldContext)
			{
				return Cast<T>(GetSafeScriptActor(WorldContext));
			}

		#pragma endregion LevelScriptActor

		#undef LogLevel
		};
	}
}

using CsPersistentLevelLibrary = NCsLevel::NPersistent::FLibrary;