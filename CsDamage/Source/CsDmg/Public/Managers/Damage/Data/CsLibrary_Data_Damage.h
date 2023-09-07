// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
		struct CSDMG_API FLibrary final : public NCsInterfaceMap::TLibrary<DataType>
		{
		public:

			static FString PrintDataAndClass(const DataType* Data);
			
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

			/**
			* Safely apply any Orientation related information from Data to Origin and Direction.
			*  Orientation Data requires Data implement the interface: NCsDamage::NData::NOrientation::IOrientation.
			* 
			* @param Context	The calling context.
			* @param Data
			* @param Vector		(out)
			* @param Direction	(out)
			* @param Log		(optional)
			* return
			*/
			static bool SafeApplyOrientation(const FString& Context, const DataType* Data, FVector3f& Origin, FVector3f& Direction, void(*Log)(const FString&) = &FCsLog::Warning);
		};

	#undef DataType
	}
}