// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Trace/Data/CsData_TraceWeapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsWeapon
{
	namespace NTrace
	{
		namespace NData
		{
#define DataType NCsWeapon::NTrace::NData::IData

			/**
			*/
			struct CSWP_API FLibrary : public TCsLibrary_InterfaceMap<DataType>
			{
				/**
				*
				*
				* @param Context
				* @param Data
				* return
				*/
				static bool IsValidChecked(const FString& Context, DataType* Data);
			};

#undef DataType
		}
	}
}