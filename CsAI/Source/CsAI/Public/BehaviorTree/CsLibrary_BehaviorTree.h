// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
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
		static UBehaviorTree* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		/**
		* Safely load a Behavior Tree at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the Behavior Tree to load.
		* @param Log		(optional)
		* return			Behavior Tree.
		*/
		static UBehaviorTree* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static UBehaviorTree* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, TSoftObjectPtr<UBehaviorTree>& OutSoftObjectPtr, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, FSoftObjectPath& OutSoftObjectPath, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

		static bool GetSafe(const FString& Context, UObject* Object, const FString& Path, FString& OutPathAsString, bool& OutSuccess, void(*Log)(const FString&) = &NCsAI::FLog::Warning);

	#pragma endregion Get
	};
}