// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once

class UStruct;

namespace NCsStruct
{
	namespace NOps
	{
		namespace NIsValid
		{
			struct CSCORE_API FLibrary final
			{
			public:

				static bool IsValidChecked(const FString& Context, void* StructValue, const UStruct* Struct);

				static bool IsValid(const FString& Context, void* StructValue, const UStruct* Struct, void(*Log)(const FString&));

				static bool IsTopValidChecked(const FString& Context, void* StructValue, const UStruct* Struct);

				static bool IsTopValid(const FString& Context, void* StructValue, const UStruct* Struct, void(*Log)(const FString&));
			};
		}
	}
}