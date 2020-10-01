// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

class ICsData_Damage;

namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

/**
* Library for interface: ICsData_Damage
*/
struct CSCORE_API FCsLibrary_Data_Damage : public TCsLibrary_InterfaceMap<ICsData_Damage>
{
	/**
	*
	*
	* @param Context	The calling context.
	* @param Data
	* return			
	*/
	static const NCsDamage::NRange::IRange* GetRangeChecked(const FString& Context, const ICsData_Damage* Data);
};