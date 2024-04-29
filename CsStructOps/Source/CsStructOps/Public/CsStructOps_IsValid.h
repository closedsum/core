// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/Map.h"
#include "UObject/NameTypes.h"

class UStruct;

namespace NCsStruct
{
	namespace NOps
	{
		namespace NIsValid
		{
			struct CSSTRUCTOPS_API FTool final
			{
			private:

				FTool();

				FTool(const FTool&) = delete;
				FTool(FTool&&) = delete;

			public:

				TMap<FName, bool(*)(const FString& /*Context*/, void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/)> IsValidCheckedFnByNameMap;
				TMap<FName, bool(*)(const FString& /*Context*/,void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/, void(*)(const FString&) /*Log*/)> IsValidFnByNameMap;
				TMap<FName, bool(*)(const FString& /*Context*/,void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/)> IsTopValidCheckedFnByNameMap;
				TMap<FName, bool(*)(const FString& /*Context*/,void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/, void(*)(const FString&) /*Log*/)> IsTopValidFnByNameMap;

				~FTool();

				FORCEINLINE static FTool& Get()
				{
					static FTool Instance;
					return Instance;
				}

				static void RegisterIsValidCheckedFn(const FName& Name, bool(*IsValidCheckedFn)(const FString& /*Context*/, void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/))
				{
					Get().IsValidCheckedFnByNameMap.Add(Name, IsValidCheckedFn);
				}

				static void RegisterIsValidFn(const FName& Name, bool(*IsValidFn)(const FString& /*Context*/, void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/, void(*)(const FString&) /*Log*/))
				{
					Get().IsValidFnByNameMap.Add(Name, IsValidFn);
				}

				static void RegisterIsTopValidCheckedFn(const FName& Name, bool(*IsTopValidCheckedFn)(const FString& /*Context*/, void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/))
				{
					Get().IsTopValidCheckedFnByNameMap.Add(Name, IsTopValidCheckedFn);
				}

				static void RegisterIsTopValidFn(const FName& Name, bool(*IsTopValidFn)(const FString& /*Context*/, void* /*StructValue*/, const UStruct* /*Struct*/, bool& /*OutSuccess*/, void(*)(const FString&) /*Log*/))
				{
					Get().IsTopValidFnByNameMap.Add(Name, IsTopValidFn);
				}

				static bool IsValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess);

				static bool IsValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&));

				static bool IsTopValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess);

				static bool IsTopValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&));
			};
		}
	}
}