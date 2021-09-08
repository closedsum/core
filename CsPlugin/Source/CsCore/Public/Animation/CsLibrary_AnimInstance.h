// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

class UObject;
class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;

namespace NCsAnimInstance
{
	/**
	* Library of function related to UAnimInstance
	*/
	class CSCORE_API FLibrary final
	{
	// Load
	#pragma region
	public:

		/**
		* Load the AnimBlueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the AnimBlueprint to load.
		* @param Log
		* return			AnimBlueprintGeneratedClass.
		*/
		static UAnimBlueprint* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a AnimBlueprint at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the AnimBlueprint to load.
		* @param Log
		* return			AnimBlueprintGeneratedClass.
		*/
		static UAnimBlueprint* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		static UAnimBlueprintGeneratedClass* GetSafeClass(const FString& Context, UAnimBlueprint* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Get
	};
}