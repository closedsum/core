// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
class UObject;

namespace NCsStartPlay
{
	struct CSCORE_API FLibrary
	{
	public:

		static void StartPlayChecked(const FString& Context, UObject* Object);
	};
}