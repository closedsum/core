// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsStructOps_Data.h"

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
		}
	}
}