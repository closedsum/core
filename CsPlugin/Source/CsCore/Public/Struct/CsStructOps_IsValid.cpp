// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Struct/CsStructOps_IsValid.h"

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
		}
	}
}