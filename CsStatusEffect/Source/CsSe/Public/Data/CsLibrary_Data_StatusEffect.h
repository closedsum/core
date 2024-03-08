// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

			static bool IsValidChecked(const FString& Context, const DataType* Data);

			static bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &NCsStatusEffect::FLog::Warning);
		};

	#undef DataType
	}
}