// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
// Log
#include "Utility/CsLog.h"
#pragma once

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

	namespace NNotify
	{
		class CSCORE_API FLibrary final
		{
		public:

			static float GetTimeChecked(const FString& Context, const UAnimMontage* Anim, const FName& NotifyName);

			static float GetRemainingTimeAfterChecked(const FString& Context, UAnimMontage* Anim, const FName& NotifyName);

			static void GetNamesChecked(const FString& Context, UAnimMontage* Anim, const float& Time, TArray<FName>& OutNames);

			static void GetNamesChecked(const FString& Context, UAnimMontage* Anim, const float& MinTime, const float& MaxTime, TArray<FName>& OutNames);
		};
	}
}