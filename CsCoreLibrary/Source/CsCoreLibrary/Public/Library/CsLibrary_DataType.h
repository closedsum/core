// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

namespace NCsDataType
{
	namespace NStr
	{
		extern CSCORELIBRARY_API const FString True;	// = TEXT("True");
		extern CSCORELIBRARY_API const FString False;	// = TEXT("False");
	}

	struct CSCORELIBRARY_API FLibrary final
	{
	public:

		FORCEINLINE static const TCHAR* ToChar(const bool& Value)
		{
			return Value ? *(NCsDataType::NStr::True) : *(NCsDataType::NStr::False);
		}
	};
}

using CsDataTypeLibrary = NCsDataType::FLibrary;