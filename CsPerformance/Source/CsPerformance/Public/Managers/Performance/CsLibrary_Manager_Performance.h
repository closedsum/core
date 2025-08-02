// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Cached.h"
#include "CsMacro_Log.h"
#include "Managers/Performance/CsManager_Performance_Delegates.h"
// Log
#include "Utility/CsPerformanceLog.h"

class UObject;
class UCsManager_Performance;

CS_FWD_DECLARE_CACHED_FUNCTION_NAME_NESTED_2(NCsPerformance, NManager, Library)

namespace NCsPerformance
{
	namespace NManager
	{
		struct CSPERFORMANCE_API FLibrary
		{
		private:

			CS_USING_CACHED_FUNCTION_NAME_NESTED_2(NCsPerformance, NManager, Library);
			CS_DECLARE_STATIC_LOG_LEVEL

		// ContextRoot
		#pragma region
		public:
		
		#if WITH_EDITOR
			/**
			* Get the Context (Root) for UCsManager_Performance from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Performance
			*/
			static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject);
		#else
			FORCEINLINE static UObject* GetContextRootChecked(const FString& Context, const UObject* ContextObject) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Performance from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* @param Log
			* return				Context for UCsManager_Performance
			*/
			static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
		#else
			FORCEINLINE static UObject* GetSafeContextRoot(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL) { return nullptr; }
		#endif // #if WITH_EDITOR

		#if WITH_EDITOR
			/**
			* Safely get the Context (Root) for UCsManager_Performance from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			* return				Context for UCsManager_Performance
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
			* Get the reference to UCsManager_Performance from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Performance.
			*/
			static UCsManager_Performance* GetChecked(const FString& Context, const UObject* ContextObject);

			/**
			* Safely get the reference to UCsManager_Performance from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param Log			(optional)
			* return				UCsManager_Performance.
			*/
			static UCsManager_Performance* GetSafe(const FString& Context, const UObject* ContextObject, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Safely get the reference to UCsManager_Performance from a ContextObject.
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* @param OutSuccess		(out)
			* @param Log			(optional)
			* return				UCsManager_Performance.
			*/
			static UCsManager_Performance* GetSafe(const FString& Context, const UObject* ContextObject, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

			/**
			* Safely get the reference to UCsManager_Performance from a ContextObject.
			*
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid).
			*						or
			*						A reference to the GameInstance.
			* return				UCsManager_Performance.
			*/
			static UCsManager_Performance* GetSafe(const UObject* ContextObject);

		#pragma endregion Get

		// Class
		#pragma region
		public:

			static TSubclassOf<UCsManager_Performance> GetClassChecked(const FString& Context);

		#pragma endregion Class

			/**
			*
			*
			* @param Context		The calling context.
			* @param ContextObject	Object that contains a reference to a World (GetWorld() is Valid)
			*						or
			*						A reference to the GameInstance.
			*/
			static void CreatePerformanceWidgetChecked(const FString& Context, const UObject* ContextObject);

			static void ConditionalCreatePerformanceWidgetChecked(const FString& Context, const UObject* ContextObject);
		};
	}
}

using CsPerformanceManagerLibrary = NCsPerformance::NManager::FLibrary;