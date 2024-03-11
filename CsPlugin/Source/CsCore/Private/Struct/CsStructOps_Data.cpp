// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsStructOps_Data.h"

// Struct
#include "UObject/Class.h"

namespace NCsStruct
{
	namespace NOps
	{
		namespace NData
		{
			FTool::FTool() :
				UnloadFnByNameMap()
			{
			}

			FTool::~FTool()
			{
				UnloadFnByNameMap.Reset();
			}

			bool FTool::Unload(void* StructValue, const UStruct* Struct)
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
		}
	}
}