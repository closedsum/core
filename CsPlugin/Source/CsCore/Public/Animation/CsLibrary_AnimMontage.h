// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Log
#include "Utility/CsLog.h"

class UObject;
class UAnimMontage;

namespace NCsAnimMontage
{
	/**
	* Library of function related to UAnimMontage
	*/
	class CSCORE_API FLibrary final
	{
	// Load
	#pragma region
	public:

		/**
		* Load the AnimMontage at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		SoftObjectPath to the AnimMontage to load.
		* @param Log
		* return			AnimMontage.
		*/
		static UAnimMontage* SafeLoad(const FString& Context, const FSoftObjectPath& Path, void(*Log)(const FString&) = &FCsLog::Warning);

		/**
		* Load a AnimMontage at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the AnimMontage to load.
		* @param Log
		* return			AnimMontage.
		*/
		static UAnimMontage* SafeLoad(const FString& Context, const FString& Path, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Load

	// Get
	#pragma region
	public:

		/**
		* Get Anim Montage value associated with member at Path for Object.
		* 
		* @param Context	The calling context.
		* @param Object
		* @param Path
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			Anim Montage.
		*/
		static UAnimMontage* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, void(*Log)(const FString&) = &FCsLog::Warning);

	#pragma endregion Get

	// Play
	#pragma region
	public:

		/**
		* Check if Anim on the AnimInstance associated with Component is playing.
		* NOTE:
		*  Component MUST be of type: USkeletalMeshComponent.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param Anim
		* return			Whether the Anim is playing or not.
		*/
		static bool IsPlayingChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim);

		/**
		* Play Anim on the AnimInstance associated with Component.
		* NOTE: 
		*  Component MUST be of type: USkeletalMeshComponent.
		*  Anim must NOT already be playing.
		* 
		* @param Context				The calling context.
		* @param Component
		* @param Anim
		* @param PlayRate				(optional)
		* @param InTimeToStartMontageAt (optional)
		* @param bStopAllMontages		(optional)
		*/
		static void PlayChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, const float& PlayRate = 1.0f, const float& InTimeToStartMontageAt = 0.0f, const bool& bStopAllMontages = true);

	#pragma endregion Play
	};
}