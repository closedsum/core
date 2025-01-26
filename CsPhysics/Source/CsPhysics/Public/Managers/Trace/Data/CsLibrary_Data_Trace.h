// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsLibrary_InterfaceMap.h"
#include "Managers/Trace/Data/CsData_Trace.h"

namespace NCsTrace
{
	namespace NData
	{
		namespace NLibrary
		{
			using DataType = NCsTrace::NData::IData;

			/**
			*/
			struct CSPHYSICS_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
			{
				/**
				*/
				static bool IsValidChecked(const FString& Context, DataType* Data);
			};
		}
	}
}

using CsTraceDataLibrary = NCsTrace::NData::NLibrary::FLibrary;