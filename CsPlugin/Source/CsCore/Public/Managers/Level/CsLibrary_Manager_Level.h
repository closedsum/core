// Copyright 2017-2021 Closed Sum Games, Inc. All rights reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Level/CsTypes_Manager_Level.h"

class UObject;
class UCsManager_Level;

namespace NCsLevel
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					extern CSCORE_API const FString GetSafe;
				}
			}
		}

		struct CSCORE_API FLibrary final
		{
		// ContextRoot
		#pragma region
		public:

		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Level
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Level
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Level from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Level
			*/
			static UObject* GetSafeContextRoot(const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region
		public:

			/**
			* Get the reference to UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Level.
			*/
			static UCsManager_Level* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Get the reference to UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Level.
			*/
			template<typename T>
			static T* GetChecked(const FString& Context, const UObject* ContextObject)
			{
				UCsManager_Level* O = GetChecked(Context, ContextObject);
				T* Other		    = Cast<T>(O);

				checkf(Other, TEXT("%s: Manager_Level is NOT of type: %s."), *Context, *(T::StaticClass()->GetName()));
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				UCsManager_Level.
			*/
			static UCsManager_Level* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				UCsManager_Level.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				UCsManager_Level* O = GetSafe(Context, ContextObject, Log);

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Manager_Level is NOT of type: %s."), *Context, *(T::StaticClass()->GetName())));
				}
				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				UCsManager_Level.
			*/
			static UCsManager_Level* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

			/**
			* Safely get the reference to UCsManager_Level from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				UCsManager_Level.
			*/
			template<typename T>
			static T* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				UCsManager_Level* O = GetSafe(Context, ContextObject, OutSuccess, Log);

				OutSuccess = false;

				if (!O)
					return nullptr;

				T* Other = Cast<T>(O);

				if (!Other)
				{
					if (Log)
						Log(FString::Printf(TEXT("%s: Manager_Level is NOT of type: %s."), *Context, *(T::StaticClass()->GetName())));
				}

				OutSuccess = true;

				return Other;
			}

			/**
			* Safely get the reference to UCsManager_Level from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Level.
			*/
			static UCsManager_Level* GetSafe(const UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Level from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Level.
			*/
			template<typename T>
			FORCEINLINE static T* GetSafe(const UObject* ContextObject)
			{
				using namespace NCsLevel::NManager::NLibrary::NCached;

				const FString& Context = Str::GetSafe;

				return GetSafe<T>(Context, ContextObject, nullptr);
			}

		#pragma endregion Get
		
		// Class
		#pragma region
		public:

			static TSubclassOf<UCsManager_Level> GetClassChecked(const FString& Context);

		#pragma endregion Class

		// Persistent Level
		#pragma region
		public:

			static bool HasFinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextRoot);

			static void Check_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextRoot);

			static void Check_FinishedLoadingPersistentLevelChecked(const FString& Context, const UObject* ContextRoot, const FString& MapPackageName);

		#pragma endregion Persistent Level

		// Change Map
		#pragma region
		public:

			static bool HasChangeMapCompletedChecked(const FString& Context, const UObject* ContextRoot);

			static bool SafeHasChangeMapCompleted(const FString& Context, const UObject* ContextRoot, void(*Log)(const FString&) = &FCsLog::Warning);

			static bool SafeHasChangeMapCompleted(const FString& Context, const UObject* ContextRoot, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

		#define ParamsType NCsLevel::NManager::NChangeMap::FParams

			static void ChangeMapChecked(const FString& Context, const UObject* ContextRoot, const ParamsType& Params);

			static bool SafeChangeMap(const FString& Context, const UObject* ContextRoot, const ParamsType& Params, void(*Log)(const FString&) = &FCsLog::Warning);

			FORCEINLINE static bool SafeChangeMap(const FString& Context, const UObject* ContextRoot, const ParamsType& Params, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning)
			{
				OutSuccess = SafeChangeMap(Context, ContextRoot, Params, Log);
				return OutSuccess;
			}

		#undef ParamsType

		#pragma endregion Change Map

		#if WITH_EDITOR

		public:

			static bool HasFinishedDestroyingOtherPIEWorld(const FString& Context, UObject* ContextObject);

			static void DestroyOtherPIEWorldChecked(const FString& Context, UObject* ContextObject, const FString& URL);

		#endif // #if WITH_EDITOR
		};
	}
}