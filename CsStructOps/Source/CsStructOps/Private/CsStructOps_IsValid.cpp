// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsStructOps_IsValid.h"

// Struct
#include "UObject/Class.h"

namespace NCsStruct
{
	namespace NOps
	{
		namespace NIsValid
		{
			FTool::FTool() :
				IsValidCheckedFnByNameMap(),
				IsValidFnByNameMap(),
				IsTopValidCheckedFnByNameMap(),
				IsTopValidFnByNameMap()
			{
			}

			FTool::~FTool()
			{
				IsValidCheckedFnByNameMap.Reset();
				IsValidFnByNameMap.Reset();
				IsTopValidCheckedFnByNameMap.Reset();
				IsTopValidFnByNameMap.Reset();
			}

			bool FTool::IsValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess)
			{
				OutSuccess = false;

				if (!StructValue)
					return false;

				// TODO: Add better Assert Messages
				check(Struct);

				const FName Name = Struct->GetFName();

				// TODO: Setup getting pointer and dereferencing
				if (Get().IsValidCheckedFnByNameMap.Find(Name))
				{
					return (Get().IsValidCheckedFnByNameMap[Name])(Context, StructValue, Struct, OutSuccess);
				}
				return false;
			}

			bool FTool::IsValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&))
			{
				OutSuccess = false;

				if (!StructValue)
					return false;

				// TODO: Add better Assert Messages
				check(Struct);

				const FName Name = Struct->GetFName();

				// TODO: Setup getting pointer and dereferencing
				if (Get().IsValidFnByNameMap.Find(Name))
				{
					return (Get().IsValidFnByNameMap[Name])(Context, StructValue, Struct, OutSuccess, Log);
				}
				return false;
			}

			bool FTool::IsTopValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess)
			{
				OutSuccess = false;

				if (!StructValue)
					return false;

				// TODO: Add better Assert Messages
				check(Struct);

				const FName Name = Struct->GetFName();

				// TODO: Setup getting pointer and dereferencing
				if (Get().IsTopValidCheckedFnByNameMap.Find(Name))
				{
					return (Get().IsTopValidCheckedFnByNameMap[Name])(Context, StructValue, Struct, OutSuccess);
				}
				return false;
			}

			bool FTool::IsTopValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&))
			{
				OutSuccess = false;

				if (!StructValue)
					return false;

				// TODO: Add better Assert Messages
				check(Struct);

				const FName Name = Struct->GetFName();

				// TODO: Setup getting pointer and dereferencing
				if (Get().IsTopValidFnByNameMap.Find(Name))
				{
					return (Get().IsTopValidFnByNameMap[Name])(Context, StructValue, Struct, OutSuccess, Log);
				}
				return false;
			}
		}
	}
}