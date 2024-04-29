// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

class UWorld;

namespace NCsTime
{
	struct CSCORELIBRARY_API FLibrary
	{
	public:

		static uint64 GetWorldTimeMilliseconds(const UWorld* InWorld);

		static float GetCurrentDateTimeSeconds();

		static uint64 GetCurrentFrame(const UWorld* InWorld);
	};
}