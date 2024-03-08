// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UObject;
class ICsPooledObject;

namespace NCsPooledObject
{
	struct CSCORE_API FLibrary
	{
		/**
		*/
		static bool IsAllocated(const FString& Context, ICsPooledObject* Object);

		/**
		*/
		static bool IsAllocated(const FString& Context, UObject* Object);
	};
}