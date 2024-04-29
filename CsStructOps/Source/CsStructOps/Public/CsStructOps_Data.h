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
		namespace NData
		{
			struct CSSTRUCTOPS_API FTool final
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

				static bool Unload(void* StructValue, const UStruct* Struct);
			};
		}
	}
}