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

				TMap<FName, bool(*)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/)> IsValidCheckedFnByNameMap;
				TMap<FName, bool(*)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/, void(*)(const FString&) /*Log*/)> IsValidFnByNameMap;
				TMap<FName, bool(*)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/)> IsTopValidCheckedFnByNameMap;
				TMap<FName, bool(*)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/, void(*)(const FString&) /*Log*/)> IsTopValidFnByNameMap;

				~FTool();

				FORCEINLINE static FTool& Get()
				{
					static FTool Instance;
					return Instance;
				}

				static void RegisterIsValidCheckedFn(const FName& Name, bool(*IsValidCheckedFn)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/))
				{
					Get().IsValidCheckedFnByNameMap.Add(Name, IsValidCheckedFn);
				}

				static void RegisterIsValidFn(const FName& Name, bool(*IsValidFn)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/, void(*)(const FString&) /*Log*/))
				{
					Get().IsValidFnByNameMap.Add(Name, IsValidFn);
				}

				static void RegisterIsTopValidCheckedFn(const FName& Name, bool(*IsTopValidCheckedFn)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/))
				{
					Get().IsTopValidCheckedFnByNameMap.Add(Name, IsTopValidCheckedFn);
				}

				static void RegisterIsTopValidFn(const FName& Name, bool(*IsTopValidFn)(void* /*StructValue*/, const UStruct* /*Struct*/, const FString& /*Context*/, void(*)(const FString&) /*Log*/))
				{
					Get().IsTopValidFnByNameMap.Add(Name, IsTopValidFn);
				}

				static bool IsValidChecked(void* StructValue, const UStruct* Struct, const FString& Context)
				{
					if (!StructValue)
						return false;

					// TODO: Add better Assert Messages
					check(Struct);

					const FName Name = Struct->GetFName();

					// TODO: Setup getting pointer and dereferencing
					if (Get().IsValidCheckedFnByNameMap.Find(Name))
					{
						return (Get().IsValidCheckedFnByNameMap[Name])(StructValue, Struct, Context);
					}
					return false;
				}

				static bool IsValid(void* StructValue, const UStruct* Struct, const FString& Context, void(*Log)(const FString&))
				{
					if (!StructValue)
						return false;

					// TODO: Add better Assert Messages
					check(Struct);

					const FName Name = Struct->GetFName();

					// TODO: Setup getting pointer and dereferencing
					if (Get().IsValidFnByNameMap.Find(Name))
					{
						return (Get().IsValidFnByNameMap[Name])(StructValue, Struct, Context, Log);
					}
					return false;
				}

				static bool IsTopValidChecked(void* StructValue, const UStruct* Struct, const FString& Context)
				{
					if (!StructValue)
						return false;

					// TODO: Add better Assert Messages
					check(Struct);

					const FName Name = Struct->GetFName();

					// TODO: Setup getting pointer and dereferencing
					if (Get().IsTopValidCheckedFnByNameMap.Find(Name))
					{
						return (Get().IsTopValidCheckedFnByNameMap[Name])(StructValue, Struct, Context);
					}
					return false;
				}

				static bool IsTopValid(void* StructValue, const UStruct* Struct, const FString& Context, void(*Log)(const FString&))
				{
					if (!StructValue)
						return false;

					// TODO: Add better Assert Messages
					check(Struct);

					const FName Name = Struct->GetFName();

					// TODO: Setup getting pointer and dereferencing
					if (Get().IsTopValidFnByNameMap.Find(Name))
					{
						return (Get().IsTopValidFnByNameMap[Name])(StructValue, Struct, Context, Log);
					}
					return false;
				}
			};
		}
	}
}