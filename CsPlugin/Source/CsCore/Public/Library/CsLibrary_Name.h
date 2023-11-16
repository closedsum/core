// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

namespace NCsName
{
	struct CSCORE_API FLibrary final
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

		static bool ContainsChecked(const FString& Context, const TArray<FName>& Names, const FName& Name);
	};
}