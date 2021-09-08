// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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
		struct CSCORE_API FLibrary : public TCsLibrary_InterfaceMap<DataType>
		{
			/**
			*/
			static bool IsValidChecked(const FString& Context, DataType* Data);
		};

	#undef DataType
	}
}