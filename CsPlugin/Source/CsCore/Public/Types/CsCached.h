// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsCached
{
	namespace Str
	{
		extern CSCORE_API const FString Empty;// = TEXT("");
		extern CSCORE_API const FString None;// = TEXT("None");
		extern CSCORE_API const FString INVALID;// = TEXT("INVALID");
		extern CSCORE_API const FString __INVALID__;// = TEXT("__INVALID__");
		extern CSCORE_API const FString Dot;// = TEXT(".");
		extern CSCORE_API const FString True;// = TEXT("True");
		extern CSCORE_API const FString _true;// = TEXT("true");
		extern CSCORE_API const FString False;// = TEXT("False");
		extern CSCORE_API const FString _false;// = TEXT("false");
		extern CSCORE_API const FString Index;// = TEXT("Index");
		extern CSCORE_API const FString PREVIEW;// = TEXT("PREVIEW");
		extern CSCORE_API const FString Zero;// = TEXT("0");
		extern CSCORE_API const FString One;// = TEXT("1");

		extern CSCORE_API const FString Text;// = TEXT("Text");
		extern CSCORE_API const FString Button;// = TEXT("Button");
		extern CSCORE_API const FString Image;// = TEXT("Image");

		extern CSCORE_API const FString _C;// = TEXT("_C");

		// Vector to String
		extern CSCORE_API const FString XEquals;// = TEXT("X=");
		extern CSCORE_API const FString YEquals;// = TEXT("Y=");
		extern CSCORE_API const FString ZEquals;// = TEXT("Z=");
		// Rotator to String
		extern CSCORE_API const FString RollEquals;// = TEXT("R=");
		extern CSCORE_API const FString PitchEquals;// = TEXT("P=");
		extern CSCORE_API const FString YawEquals;// = TEXT("Y=");
	}

	CSCORE_API FORCEINLINE const TCHAR* ToChar(bool Value)
	{
		return Value ? *(Str::True) : *(Str::False);
	}

	namespace Ref
	{
		extern CSCORE_API const bool True;		// = true;
		extern CSCORE_API const bool False;		// = false;
		extern CSCORE_API const uint8 Byte;		// = 0;
		extern CSCORE_API const int8 SByte;		// = 0;
		extern CSCORE_API const uint16 Short;	// = 0;
		extern CSCORE_API const int16 SShort;	// = 0;
		extern CSCORE_API const uint32 Int;		// = 0;
		extern CSCORE_API const int32 SInt;		// = 0;
		extern CSCORE_API const uint64 Long;	// = 0;
		extern CSCORE_API const uint64 Long_MAX;// = UINT64_MAX;
		extern CSCORE_API const int64 SLong;	// = 0;
		extern CSCORE_API const float Float;	// = 0.0f;
		extern CSCORE_API const int32 IndexNone;// = -1;
		extern CSCORE_API const FString String;	// = TEXT("");
		extern CSCORE_API const FName Name;		// = NAME_None;
	}

	namespace Name
	{
		extern CSCORE_API const FName None;// = NAME_None;
		extern CSCORE_API const FName Null;// = FName("NULL");
		extern CSCORE_API const FName __INVALID__;// = FName("__INVALID__");
	}

	namespace Ext
	{
		extern CSCORE_API const FString json;// = TEXT(".json");
		extern CSCORE_API const FString txt;// = TEXT(".txt");
		extern CSCORE_API const FString js;// = TEXT(".js");
	}
}

#define CS_INVALID_SHORT_CODE NCsCached::Name::Null