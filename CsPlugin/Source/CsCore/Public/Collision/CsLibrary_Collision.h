// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Engine/EngineTypes.h"
// Log
#include "Utility/CsLog.h"

namespace NCsCollision
{
	class CSCORE_API FLibrary final
	{
	public:

		/**
		* Find the UV for a collision impact. 
		* NOTE: this ONLY works if 'Support UV From Hit Results' is enabled in Physics Settings.
		* 
		* @param Context	The calling context.
		* @param Hit
		* @param UVChannel
		* @param OutUV		(out)
		* return			Whether a valid UV has been found.
		*/
		static bool FindUVChecked(const FString& Context, const FHitResult& Hit, const int32& UVChannel, FVector2f& OutUV);

	// HitResult
	#pragma region
	public:

		static FVector3f GetLocation(const FHitResult& Hit);
		static FRotator3f GetImpactRotation(const FHitResult& Hit);
		static FQuat4f GetImpactQuat(const FHitResult& Hit);

	#pragma endregion HitResult
	};

	namespace NProfile
	{
		struct CSCORE_API FLibrary final
		{
		public:

			/**
			* Check whether Name is the name of a Collision Profile.
			* 
			* @param Context	The calling context.
			* @param Name		Collision Profile name.
			* return			Whether Name is the name of Collision Profile or not.
			*/
			static bool IsValidChecked(const FString& Context, const FName& Name);

			/**
			* Check whether Name is the name of a Collision Profile.
			* 
			* @param Context	The calling context.
			* @param Name		Collision Profile name.
			* @param Log		(optional)
			* return			Whether Name is the name of Collision Profile or not.
			*/
			static bool IsValid(const FString& Context, const FName& Name, void(*Log)(const FString&) = &FCsLog::Warning);
		};
	}
}