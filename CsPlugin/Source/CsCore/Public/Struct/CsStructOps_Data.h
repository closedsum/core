// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
class UStruct;

namespace NCsStruct
{
	namespace NOps
	{
		namespace NData
		{
			struct CSCORE_API FTool final
			{
			private:

				FTool();

				FTool(const FTool&) = delete;
				FTool(FTool&&) = delete;

			public:

				TMap<FName, bool(*)(void* /*StructValue*/, const UStruct* /*Struct*/)> UnloadFnByNameMap;

				~FTool();

				FORCEINLINE static FTool& Get()
				{
					static FTool Instance;
					return Instance;
				}

				static void RegisterUnloadFn(const FName& Name, bool(*UnloadFn)(void* /*StructValue*/, const UStruct* /*Struct*/))
				{
					Get().UnloadFnByNameMap.Add(Name, UnloadFn);
				}

				static bool Unload(void* StructValue, const UStruct* Struct)
				{
					if (!StructValue)
						return false;

					// TODO: Add better Assert Messages
					check(Struct);

					const FName Name = Struct->GetFName();

					// TODO: Setup getting pointer and dereferencing
					if (Get().UnloadFnByNameMap.Find(Name))
					{
						return (Get().UnloadFnByNameMap[Name])(StructValue, Struct);
					}
					return false;
				}
			};
		}
	}
}