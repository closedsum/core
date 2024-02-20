// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Types/CsTypes_Macro.h"
// Log
#include "Utility/CsLog.h"

class ULevel;
class UWorld;
class UObject;
class ALevelScriptActor;
struct FCsPayload;

namespace NCsLevel
{
	namespace NPersistent
	{
		struct CSCORE_API FLibrary final
		{
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

			/**
			* Safely get the Long Package Name for the Persistent Level. This is usually in the form:
			* LevelPath.LevelName
			* 
			* @param Context		The calling context.
			* @param WorldContext	Object that contains a reference to a World (GetWorld() is Valid).
			* @param Log			(optional)
			* return				LevelPath.LevelName
			*/
			static FString GetSafeLongPackageName(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning);

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
			static bool SafeIsPath(const FString& Context, const UObject* WorldContext, const FSoftObjectPath& Path, void(*Log)(const FString& Context) = &FCsLog::Warning);

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

		// SetupData
		#pragma region
		public:

			/**
			* Get the Level Setup Data as a UObject from the current Persistent Level.
			*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
			* 
			* @param Context		The calling context.
			* @param WorldContext
			* return				UObject.
			*/
			static UObject* GetSetupDataAsObjectChecked(const FString& Context, const UObject* WorldContext);

			/**
			* Safely get the Level Setup Data as a UObject from the current Persistent Level.
			*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
			*
			* @param Context		The calling context.
			* @param WorldContext
			* @param Log			(optional)
			* return				UObject.
			*/
			static UObject* GetSafeSetupDataAsObject(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning);

			/**
			* Safely get the Level Setup Data as a UObject from the current Persistent Level.
			*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
			*
			* @param WorldContext
			* return				UObject.
			*/
			static UObject* GetSafeSetupDataAsObject(const UObject* WorldContext);

			/**
			* Get the Level Setup Data of type: T from current Persistent Level.
			*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
			*
			* @param Context		The calling context.
			* @param WorldContext
			* return				Level Setup Data of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSetupDataChecked(const FString& Context, const UObject* WorldContext)
			{
				T* Slice = Cast<T>(GetSetupDataAsObjectChecked(Context, WorldContext));

				checkf(Slice, TEXT("%s: Failed to cast Level Setup Data to type: T."), *Context);

				return Slice;
			}

			/**
			* Safely get the Level Setup Data of type: T from current Persistent Level.
			*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
			*
			* @param Context		The calling context.
			* @param WorldContext
			* @param Log			(optional)
			* return				Level Setup Data of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeSetupData(const FString& Context, const UObject* WorldContext, void(*Log)(const FString& Context) = &FCsLog::Warning)
			{
				T* Slice = Cast<T>(GetSafeSetupDataAsObject(Context, WorldContext, Log));

				if (!Slice)
				{
					if (Log)
					{
						Log(FString::Printf(TEXT("%s: Failed to cast Level Setup Data to type: T."), *Context));
					}
					return nullptr;
				}
				return Slice;
			}

			/**
			* Safely get the Level Setup Data of type: T from current Persistent Level.
			*  Level Setup Data is an object that implements the interface: ICsData_Level_Setup.
			*
			* @param WorldContext
			* return				Level Setup Data of type: T.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafeSetupData(const UObject* WorldContext)
			{
				return Cast<T>(GetSafeSetupDataAsObject(WorldContext));
			}

		#pragma endregion SetupData

		// ICsGetLevelPayload
		#pragma region
		public:

			static void GetPayloadAndLevelNameChecked(const FString& Context, const UObject* WorldContext, FCsPayload*& OutPayload, FName& OutLevelName);

			static bool GetSafePayloadAndLevelName(const FString& Context, const UObject* WorldContext, FCsPayload*& OutPayload, FName& OutLevelName, void(*Log)(const FString&) = &FCsLog::Warning);

		#pragma endregion ICsGetLevelPayload
		};
	}
}