// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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