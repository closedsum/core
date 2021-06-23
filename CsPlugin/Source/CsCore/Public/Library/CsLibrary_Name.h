// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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
	};
}