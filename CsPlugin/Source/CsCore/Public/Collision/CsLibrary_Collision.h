// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Engine/EngineTypes.h"

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
}