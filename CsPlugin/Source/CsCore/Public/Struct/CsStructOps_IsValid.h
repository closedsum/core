// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
			struct CSCORE_API FTool final
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

				static bool IsValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess)
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

				static bool IsValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&))
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

				static bool IsTopValidChecked(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess)
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

				static bool IsTopValid(const FString& Context, void* StructValue, const UStruct* Struct, bool& OutSuccess, void(*Log)(const FString&))
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
			};
		}
	}
}