// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "CoreMinimal.h"

namespace NCsName
{
	struct CSCORELIBRARY_API FLibrary final
	{
	public:

		static FString ToString(const TArray<FName>& Names)
		{
			FString Str;

			const int32 Count = Names.Num();

			for (int32 I = 0; I < Count; ++I)
			{
				Str += Names[I].ToString();
				
				if (I < Count - 1)
					Str += TEXT(", ");
			}
			return Str;
		}

		/**
		* Does A contains all the elements of B
		* 
		* @param A
		* @param B
		* return
		*/
		static bool Contains(const TArray<FName>& A, const TArray<FName>& B);

		static bool ContainsChecked(const FString& Context, const TArray<FName>& Names, const FName& Name);
	};
}