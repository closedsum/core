// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Name.h"

// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsName
{
	bool FLibrary::ContainsChecked(const FString& Context, const TArray<FName>& Names, const FName& Name)
	{
		CS_IS_TARRAY_ANY_NONE_CHECKED(Names)
		CS_IS_NAME_NONE_CHECKED(Name)

		for (const FName& N : Names)
		{
			if (N == Name)
				return true;
		}
		checkf(0, TEXT("%s: Names: %s does NOT contain Name: %s."), *Context, *ToString(Names), *(Name.ToString()));
		return false;
	}
}