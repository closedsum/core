// Copyright 2017-2018 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Primitive.h"

// Cached
#pragma region

namespace ECsCached
{
	namespace Str
	{
		CSCORE_API const FString Empty = TEXT("");
		CSCORE_API const FString None = TEXT("None");
		CSCORE_API const FString INVALID = TEXT("INVALID");
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
		CSCORE_API const int32 SLong = 0;
		CSCORE_API const float Float = 0.0f;
		CSCORE_API const FString String = TEXT("");
		CSCORE_API const FName Name = NAME_None;
	}

	namespace Name
	{
		CSCORE_API const FName None = NAME_None;
		CSCORE_API const FName Null = FName("NULL");
	}

	namespace Ext
	{
		CSCORE_API const FString json = TEXT(".json");
		CSCORE_API const FString txt = TEXT(".txt");
		CSCORE_API const FString js = TEXT(".js");
	}
}

#pragma endregion Cached