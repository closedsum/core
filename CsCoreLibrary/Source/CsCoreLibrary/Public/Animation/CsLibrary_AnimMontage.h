// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Animation/CsTypes_AnimMontage.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class UObject;
class UAnimMontage;
class UPrimitiveComponent;

namespace NCsAnimMontage
{
	/**
	* Library of function related to UAnimMontage
	*/
	class CSCORELIBRARY_API FLibrary final
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

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
		static UAnimMontage* SafeLoad(const FString& Context, const FSoftObjectPath& Path, LogLevel);

		/**
		* Load a AnimMontage at the given Path.
		*
		* @param Context	The calling context.
		* @param Path		FString path to the AnimMontage to load.
		* @param Log
		* return			AnimMontage.
		*/
		static UAnimMontage* SafeLoad(const FString& Context, const FString& Path, LogLevel);

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
		static UAnimMontage* GetSafe(const FString& Context, UObject* Object, const FString& Path, bool& OutSuccess, LogLevel);

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
		* Check if Anim on the AnimInstance associated with Component is playing.
		* NOTE:
		*  Component MUST be of type: USkeletalMeshComponent.
		* 
		* @param Context	The calling context.
		* @param Component
		* @param Anim
		* @param OutSuccess	(out)
		* @param Log		(optional)
		* return			Whether the Anim is playing or not.
		*/
		static bool SafeIsPlaying(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, bool& OutSuccess, LogLevel);
		FORCEINLINE static bool SafeIsPlaying(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, LogLevel) 
		{
			bool Success = false;
			return SafeIsPlaying(Context, Component, Anim, Success, Log);
		}

	#define ParamsType NCsAnimMontage::NPlay::FParams

		static float PlayChecked(const FString& Context, UPrimitiveComponent* Component, UAnimMontage* Anim, const float& PlayRate = 1.0f, const float& TimeToStartMontageAt = 0.0f);

		/**
		* Play Anim on the AnimInstance associated with Component.
		* NOTE: 
		*  Component MUST be of type: USkeletalMeshComponent.
		*  Anim must NOT already be playing.
		* 
		* @param Context				The calling context.
		* @param Component
		* @param Params
		* return
		*/
		static float PlayChecked(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params);
		FORCEINLINE static float PlayChecked(const FString& Context, UPrimitiveComponent* Component, const FCsAnimMontage_PlayParams& Params)
		{
			return PlayChecked(Context, Component, ParamsType::Make(Params));
		}

		/**
		* Safely Play Anim on the AnimInstance associated with Component.
		* NOTE: 
		*  Component MUST be of type: USkeletalMeshComponent.
		*  Anim must NOT already be playing.
		* 
		* @param Context				The calling context.
		* @param Component
		* @param Params
		* @param OutSuccess				(out)
		* return
 		*/
		static float SafePlay(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params, bool& OutSuccess, LogLevel);
		FORCEINLINE static float SafePlay(const FString& Context, UPrimitiveComponent* Component, const FCsAnimMontage_PlayParams& Params, bool& OutSuccess, LogLevel)
		{
			return SafePlay(Context, Component, ParamsType::Make(Params), OutSuccess, Log);
		}
		FORCEINLINE static float SafePlay(const FString& Context, UPrimitiveComponent* Component, const ParamsType& Params, LogLevel)
		{
			bool Success = false;
			return SafePlay(Context, Component, Params, Success, Log);
		}
		FORCEINLINE static float SafePlay(const FString& Context, UPrimitiveComponent* Component, const FCsAnimMontage_PlayParams& Params, LogLevel)
		{
			return SafePlay(Context, Component, ParamsType::Make(Params), Log);
		}

		static float SafePlay(const FString& Context, UPrimitiveComponent* Component, const FCsAnimMontage_PlayByPathParams& Params, bool& OutSuccess, LogLevel);

	#undef ParamsType

	#pragma endregion Play

	#undef LogLevel
	};
}