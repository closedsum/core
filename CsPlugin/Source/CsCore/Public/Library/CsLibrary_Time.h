// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once

class UWorld;

namespace NCsTime
{
	struct CSCORE_API FLibrary
	{
	public:

		static uint64 GetWorldTimeMilliseconds(const UWorld* InWorld);

		static float GetCurrentDateTimeSeconds();

		static uint64 GetCurrentFrame(const UWorld* InWorld);
	};
}