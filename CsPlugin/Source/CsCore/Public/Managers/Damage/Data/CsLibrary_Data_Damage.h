// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Damage
#include "Managers/Damage/Data/CsData_Damage.h"
// Log
#include "Utility/CsLog.h"

// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

namespace NCsDamage
{
	namespace NData
	{
	#define DataType NCsDamage::NData::IData

		/**
		* Library for interface: DataType (NCsDamage::NData::IData)
		*/
		struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<DataType>
		{
		public:

			static bool IsValidChecked(const FString& Context, const DataType* Data);

			static bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &FCsLog::Warning);

		#define RangeType NCsDamage::NRange::IRange

			/**
			*
			*
			* @param Context	The calling context.
			* @param Data
			* return			
			*/
			static const RangeType* GetRangeChecked(const FString& Context, const DataType* Data);

			static const RangeType* GetSafeRange(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &FCsLog::Warning);

		#undef RangeType
		};

	#undef DataType
	}
}