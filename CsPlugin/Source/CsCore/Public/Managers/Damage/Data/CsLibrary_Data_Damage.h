// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Data/CsData_Damage.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsDamage::NRange::IRange
namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

#define DataType NCsDamage::NData::IData

/**
* Library for interface: ICsData_Damage
*/
struct CSCORE_API FCsLibrary_Data_Damage : public TCsLibrary_InterfaceMap<DataType>
{

#define RangeType NCsDamage::NRange::IRange

public:

	/**
	*
	*
	* @param Context	The calling context.
	* @param Data
	* return			
	*/
	static const RangeType* GetRangeChecked(const FString& Context, const DataType* Data);

#undef RangeType
};

#undef DataType