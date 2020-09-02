// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Library/CsLibrary_String.h"
#include "CsCore.h"

UCsLibrary_String::UCsLibrary_String(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

FString UCsLibrary_String::Stream_GetString(const TCHAR*& Str, bool IsLowerCase)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return IsLowerCase ? Arg.ToLower() : Arg;
}

FName UCsLibrary_String::Stream_GetName(const TCHAR*& Str)
{
	return FName(*Stream_GetString(Str, false));
}

bool UCsLibrary_String::Stream_GetBool(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	const FString Bool = Arg.ToLower();

	if (Bool == TEXT("true") || Bool == TEXT("1"))
		return true;
	if (Bool == TEXT("false") || Bool == TEXT("0"))
		return false;
	return false;
}

int32 UCsLibrary_String::Stream_GetBoolAsInt(const TCHAR*& Str)
{
	FString Arg = Stream_GetString(Str, true);

	if (Arg == TEXT("true") || Arg == TEXT("1"))
		return 1;
	if (Arg == TEXT("false") || Arg == TEXT("0"))
		return 0;
	return INDEX_NONE;
}

int32 UCsLibrary_String::Stream_GetInt(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return FCString::Atoi(*Arg);
}

float UCsLibrary_String::Stream_GetFloat(const TCHAR*& Str)
{
	FString Arg;
	FParse::Token(Str, Arg, false);

	return FCString::Atof(*Arg);
}