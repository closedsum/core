// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Engine/HitResult.h"
// Log
#include "Utility/CsCoreLibraryLog.h"

class AActor;

namespace NCsHitResult
{
	struct CSCORELIBRARY_API FLibrary
	{
	#define LogLevel void(*Log)(const FString&) = &NCsCore::NLibrary::FLog::Warning

	public:

		static AActor* GetActorChecked(const FString& Context, const FHitResult& Hit);

		static AActor* GetSafeActor(const FString& Context, const FHitResult& Hit, LogLevel);
		FORCEINLINE static AActor* GetSafeActor(const FString& Context, const FHitResult& Hit, bool& OutSuccess, LogLevel)
		{
			AActor* A  = GetSafeActor(Context, Hit, Log);
			OutSuccess = A != nullptr;
			return A;
		}

		static AActor* GetSafeActor(const FHitResult& Hit);

	#undef LogLevel
	};
}