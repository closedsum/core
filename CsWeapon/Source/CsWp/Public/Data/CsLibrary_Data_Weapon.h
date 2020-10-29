// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsWeapon
{
	namespace NData
	{
#define DataType NCsWeapon::NData::IData

		struct CSWP_API FLibrary : TCsLibrary_InterfaceMap<DataType>
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