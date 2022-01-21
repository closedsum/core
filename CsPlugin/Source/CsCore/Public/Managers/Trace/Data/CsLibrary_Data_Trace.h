// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsLibrary_InterfaceMap.h"
#include "Managers/Trace/Data/CsData_Trace.h"
#pragma once

namespace NCsTrace
{
	namespace NData
	{
	#define DataType NCsTrace::NData::IData

		/**
		*/
		struct CSCORE_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
		{
			/**
			*/
			static bool IsValidChecked(const FString& Context, DataType* Data);
		};

	#undef DataType
	}
}