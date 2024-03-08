// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UAnimBlueprint;
class UAnimBlueprintGeneratedClass;
class UAnimInstance;
class UPrimitiveComponent;

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

		static UAnimBlueprintGeneratedClass* GetSafeClass(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		static UAnimBlueprintGeneratedClass* GetSafeClass(const FString& Context, UAnimBlueprint* Blueprint, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get AnimBlueprintGeneratedClass value associated with member at Path for Object.
		* 
		* @param Context	The calling context.
		* @param Object
		* @param Path
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			AnimBlueprintGeneratedClass.
		*/
		static UAnimBlueprintGeneratedClass* GetSafeClass(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Get the AnimInstance associated with Component.
		* NOTE: Component MUST be of type: USkeletalMeshComponent.
		* 
		* @param Context	The calling context.
		* @param Component
		* return			Anim Instance.
		*/
		static UAnimInstance* GetChecked(const FString& Context, UPrimitiveComponent* Component);

	#pragma endregion Get
	};
}