// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Container
#include "Containers/CsLibrary_InterfaceMap.h"
// Data
#include "Data/CsData_StatusEffect.h"
// Log
#include "Utility/CsSeLog.h"

namespace NCsStatusEffect
{
	namespace NData
	{
	#define DataType NCsStatusEffect::NData::IData

		/**
		* Library for interface: DataType (NCsStatusEffect::NData::IData)
		*/
		struct CSSE_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
		{
		public:
		
			static FString PrintDataAndClass(DataType* Data);

			static bool IsValidChecked(const FString& Context, DataType* Data) { return true; }

			static bool IsValid(const FString& Context, DataType* Data, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning) { return true; }
		};

	#undef DataType
	}
}