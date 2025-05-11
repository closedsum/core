// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsAILog.h"

class UBehaviorTree;

namespace NCsBehaviorTree
{
	/**
	* Library of functions related to a BehaviorTree
	*/
	struct CSAI_API FLibrary final
	{
	private:

		CS_DECLARE_STATIC_LOG_LEVEL

	// Load
	#pragma region
	public:

		/**
		* Safely load the Behavior Tree at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the Behavior Tree to load.
		* @param Log		(optional)
		* return			Behavior Tree.
		*/
		static UBehaviorTree* SafeLoad(const FString& Context, const FSoftObjectPath& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		/**
		* Safely load a Behavior Tree at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Behavior Tree to load.
		* @param Log		(optional)
		* return			Behavior Tree.
		*/
		static UBehaviorTree* SafeLoad(const FString& Context, const FString& Path, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static UBehaviorTree* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, TSoftObjectPtr<UBehaviorTree>& OutSoftObjectPtr, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, FSoftObjectPath& OutSoftObjectPath, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess, CS_FN_PARAM_DEFAULT_LOG_LEVEL);

	#pragma endregion Get
	};
}

using CsBehaviorTreeLibrary = NCsBehaviorTree::FLibrary;