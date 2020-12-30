// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class ULevel;
class UWorld;
class UObject;
class ALevelScriptActor;

namespace NCsLevel
{
	/**
	*/
	struct CSCORE_API FLibrary
	{
	// Persistent
	#pragma region
	public:

		/**
		* Get the current Persistent Level.
		*
		* @param World	
		* return		Level
		*/
		static ULevel* GetPersistentLevel(UWorld* World);

		/**
		* Get the current Persistent Level.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Level
		*/
		static ULevel* GetPersistentLevel(UObject* WorldContext);

		/**
		* Get the current Persistent Level.
		*
		* @param Context	The calling context
		* @param World
		* return			Level
		*/
		static ULevel* GetPersistentLevelChecked(const FString& Context, UWorld* World);

		/**
		* Get the current Persistent Level.
		*
		* @param Context		The calling context
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Level
		*/
		static ULevel* GetPersistentLevelChecked(const FString& Context, UObject* WorldContext);

		/**
		* Get the current Persistent Level's name as a FString.
		*
		* @param World
		* return		Level name
		*/
		static FString GetPersistentLevelName(UWorld* World);

		/**
		* Get the current Persistent Level's name as a FString.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Level name
		*/
		static FString GetPersistentLevelName(UObject* WorldContext);

		/**
		* Get the current Persistent Level's name as a FString.
		*
		* @param Context	The calling context.
		* @param World
		* return			Level name
		*/
		static FString GetPersistentLevelNameChecked(const FString& Context, UWorld* World);

		/**
		* Get the current Persistent Level's name as a FString.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Level name
		*/
		static FString GetPersistentLevelNameChecked(const FString& Context, UObject* WorldContext);

		/**
		* Get the current Persistent Level's name as a FName.
		*
		* @param World
		* return		Level name
		*/
		static FName GetPersistentLevelFName(UWorld* World);

		/**
		* Get the current Persistent Level's name as a FName.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Level name
		*/
		static FName GetPersistentLevelFName(UObject* WorldContext);

		/**
		* Get the current Persistent Level's name as a FName.
		*
		* @param Context	The calling context.
		* @param World
		* return			Level name
		*/
		static FName GetPersistentLevelFNameChecked(const FString& Context, UWorld* World);

		/**
		* Get the current Persistent Level's name as a FName.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				Level name
		*/
		static FName GetPersistentLevelFNameChecked(const FString& Context, UObject* WorldContext);

		/**
		*/
		static bool IsPersistentLevelName(UWorld* World, const FString& MapPackageName);

		/**
		*/
		static bool IsPersistentLevelName(UObject* WorldContext, const FString& MapPackageName);

		/**
		* Get the LevelScriptActor from the current Persistent Level.
		* 
		* @param World
		* return		LevelScriptActor
		*/
		static ALevelScriptActor* GetPersistentLevelScriptActor(UWorld* World);

		/**
		* Get the LevelScriptActor of type: T from current Persistent Level.
		* 
		* @param World
		* return		LevelScriptActor of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetPersistentLevelScriptActor(UWorld* World)
		{
			return Cast<T>(GetPersistentLevelScriptActor(World));
		}

		/**
		* Get the LevelScriptActor from the current Persistent Level.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				LevelScriptActor
		*/
		static ALevelScriptActor* GetPersistentLevelScriptActor(UObject* WorldContext);

		/**
		* Get the LevelScriptActor of type: T from current Persistent Level.
		*
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				LevelScriptActor of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetPersistentLevelScriptActor(UObject* WorldContext)
		{
			return Cast<T>(GetPersistentLevelScriptActor(WorldContext));
		}

		/**
		* Get the LevelScriptActor from the current Persistent Level.
		* 
		* @param Context	The calling context.
		* @param World
		* return			LevelScriptActor
		*/
		static ALevelScriptActor* GetPersistentLevelScriptActorChecked(const FString& Context, UWorld* World);

		/**
		* Get the LevelScriptActor of type: T from current Persistent Level.
		* 
		* @param Context	The calling context.
		* @param World
		* return			LevelScriptActor of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetPersistentLevelScriptActorChecked(const FString& Context, UWorld* World)
		{
			T* Slice = Cast<T>(GetPersistentLevelScriptActorChecked(Context, World));

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
		static ALevelScriptActor* GetPersistentLevelScriptActorChecked(const FString& Context, UObject* WorldContext);

		/**
		* Get the LevelScriptActor of type: T from current Persistent Level.
		*
		* @param Context		The calling context.
		* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
		* return				LevelScriptActor of type: T.
		*/
		template<typename T>
		FORCEINLINE static T* GetPersistentLevelScriptActorChecked(const FString& Context, UObject* WorldContext)
		{
			T* Slice = Cast<T>(GetPersistentLevelScriptActorChecked(Context, WorldContext));

			checkf(Slice, TEXT("%s: Failed to cast LevelScriptActor to type: T."), *Context);

			return Slice;
		}

	#pragma endregion Persistent
	};
}