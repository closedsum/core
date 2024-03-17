// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/UnrealString.h"
#include "UObject/NameTypes.h"

namespace NCsEnum
{
	namespace Str
	{
		extern CSCORE_API const FString Empty;// = TEXT("");
		extern CSCORE_API const FString None;// = TEXT("None");
		extern CSCORE_API const FString INVALID;// = TEXT("INVALID");
		extern CSCORE_API const FString __INVALID__;// = TEXT("__INVALID__");
	}

	namespace Name
	{
		extern CSCORE_API const FName __INVALID__;// = FName("__INVALID__");
	}
}

#define CS_INVALID_ENUM_TO_STRING NCsEnum::Str::__INVALID__
#define CS_INVALID_ENUM_TO_NAME NCsEnum::Name::__INVALID__