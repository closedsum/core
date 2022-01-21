// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

class ULevel;
class UWorld;
class UObject;
class ALevelScriptActor;

namespace NCsLevel
{
	namespace NPersistent
	{
		struct CSCORE_API FLibrary final
		{
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
			static ULevel* GetSafe(const FString& Context, const UWorld* World, void(*Log)(const FString& Context) = &FCsLog::Warning);

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
			static ULevel* GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			* Get the current Persistent Level.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return		Level
			*/
			static ULevel* GetSafe(const UObject* WorldContext);

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
			static FString GetSafeName(const FString& Context, const UWorld* World, void(*Log)(const FString& Context) = &FCsLog::Warning);

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
			static FString GetSafeName(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning);

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
			static FName GetSafeFName(const FString& Context, const UWorld* World, void(*Log)(const FString& Context) = &FCsLog::Warning);

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
			static FName GetSafeFName(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			* Get the current Persistent Level's name as a FName.
			*
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* return				Level name
			*/
			static FName GetSafeFName(const UObject* WorldContext);

		#pragma endregion FName

		public:

			/**
			*/
			static bool IsNameChecked(const FString& Context, const UWorld* World, const FString& MapPackageName);

			/**
			*/
			static bool IsNameChecked(const FString& Context, const UObject* WorldContext, const FString& MapPackageName);

			/**
			*/
			static bool SafeIsName(const FString& Context, const UWorld* World, const FString& MapPackageName, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			*/
			static bool SafeIsName(const UWorld* World, const FString& MapPackageName);

			/**
			*/
			static bool SafeIsName(const FString& Context, const UObject* WorldContext, const FString& MapPackageName, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			*/
			static bool SafeIsName(const UObject* WorldContext, const FString& MapPackageName);

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
			static ALevelScriptActor* GetSafeScriptActor(const FString& Context, const UWorld* World, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param Context	The calling context.
			* @param World
			* @param Log
			* return			LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeScriptActor(const FString& Context, const UWorld* World, void(*Log)(const FString& Context) = &FCsLog::Warning)
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
			static ALevelScriptActor* GetSafeScriptActor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			* Get the LevelScriptActor of type: T from current Persistent Level.
			*
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log
			* return				LevelScriptActor of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeScriptActor(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning)
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
		};
	}
}