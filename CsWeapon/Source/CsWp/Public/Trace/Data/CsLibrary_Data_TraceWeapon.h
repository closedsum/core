// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Trace/Data/CsData_TraceWeapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"

#define DataType NCsWeapon::NTrace::NData::IData

struct CSWP_API FCsLibrary_Data_TraceWeapon : public TCsLibrary_InterfaceMap<DataType>
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