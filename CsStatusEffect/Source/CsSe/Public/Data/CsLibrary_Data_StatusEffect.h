// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_StatusEffect.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsStatusEffect
{
	namespace NData
	{
	#define DataType NCsStatusEffect::NData::IData

		/**
		* Library for interface: DataType (NCsStatusEffect::NData::IData)
		*/
		struct CSSE_API FLibrary : public TCsLibrary_InterfaceMap<DataType>
		{
		};

	#undef DataType
	}
}