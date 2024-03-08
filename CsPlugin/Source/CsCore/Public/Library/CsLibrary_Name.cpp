// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Library/CsLibrary_Name.h"

// Types
#include "Types/CsTypes_Macro.h"
// Library
#include "Library/CsLibrary_Valid.h"

namespace NCsName
{
	bool FLibrary::Contains(const TArray<FName>& A, const TArray<FName>& B)
	{
		if (B.Num() == CS_EMPTY)
			return false;

		if (B.Num() > A.Num())
			return false;

		const int32 CountA = A.Num();
		const int32 CountB = B.Num();
		int32 Count		   = 0;

		for (const FName& Name : B)
		{
			for (int32 I = 0; I < CountA; ++I)
			{
				if (Name == A[I])
					++Count;

				if (Count >= CountB)
					return true;
			}
		}
		return Count >= CountB;
	}

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