// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsCached.h"

namespace NCsCached
{
	namespace Str
	{
		CSCORE_API const FString Empty = TEXT("");
		CSCORE_API const FString None = TEXT("None");
		CSCORE_API const FString INVALID = TEXT("INVALID");
		CSCORE_API const FString __INVALID__ = TEXT("__INVALID__");
		CSCORE_API const FString Dot = TEXT(".");
		CSCORE_API const FString True = TEXT("True");
		CSCORE_API const FString _true = TEXT("true");
		CSCORE_API const FString False = TEXT("False");
		CSCORE_API const FString _false = TEXT("false");
		CSCORE_API const FString Index = TEXT("Index");
		CSCORE_API const FString PREVIEW = TEXT("PREVIEW");
		CSCORE_API const FString Zero = TEXT("0");
		CSCORE_API const FString One = TEXT("1");

		CSCORE_API const FString Text = TEXT("Text");
		CSCORE_API const FString Button = TEXT("Button");
		CSCORE_API const FString Image = TEXT("Image");

		CSCORE_API const FString _C = TEXT("_C");

		// Vector to String
		CSCORE_API const FString XEquals = TEXT("X=");
		CSCORE_API const FString YEquals = TEXT("Y=");
		CSCORE_API const FString ZEquals = TEXT("Z=");
		// Rotator to String
		CSCORE_API const FString RollEquals = TEXT("R=");
		CSCORE_API const FString PitchEquals = TEXT("P=");
		CSCORE_API const FString YawEquals = TEXT("Y=");
	}

	namespace Ref
	{
		CSCORE_API const bool True = true;
		CSCORE_API const bool False = false;
		CSCORE_API const uint8 Byte = 0;
		CSCORE_API const int8 SByte = 0;
		CSCORE_API const uint16 Short = 0;
		CSCORE_API const int16 SShort = 0;
		CSCORE_API const uint32 Int = 0;
		CSCORE_API const int32 SInt = 0;
		CSCORE_API const uint64 Long = 0;
		CSCORE_API const uint64 Long_MAX = UINT64_MAX;
		CSCORE_API const int64 SLong = 0;
		CSCORE_API const float Float = 0.0f;
		CSCORE_API const int32 IndexNone = -1;
		CSCORE_API const FString String = TEXT("");
		CSCORE_API const FName Name = NAME_None;
	}

	namespace Name
	{
		CSCORE_API const FName None = NAME_None;
		CSCORE_API const FName Null = FName("NULL");
		CSCORE_API const FName __INVALID__ = FName("__INVALID__");
	}

	namespace Ext
	{
		CSCORE_API const FString json = TEXT(".json");
		CSCORE_API const FString txt = TEXT(".txt");
		CSCORE_API const FString js = TEXT(".js");
	}
}