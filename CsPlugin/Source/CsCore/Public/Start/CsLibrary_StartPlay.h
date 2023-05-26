// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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