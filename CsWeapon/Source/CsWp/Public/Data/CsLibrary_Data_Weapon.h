// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

struct CSWP_API FCsLibrary_Data_Weapon : TCsLibrary_InterfaceMap<ICsData_Weapon>
{
	/**
	*
	*
	* @param Context
	* @param Data
	* return
	*/
	static bool IsValidChecked(const FString& Context, ICsData_Weapon* Data);
};