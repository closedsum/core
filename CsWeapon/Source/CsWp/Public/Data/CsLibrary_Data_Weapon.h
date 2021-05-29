// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Weapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsWpLog.h"
#pragma once

namespace NCsWeapon
{
	namespace NData
	{
	#define DataType NCsWeapon::NData::IData

		struct CSWP_API FLibrary : TCsLibrary_InterfaceMap<DataType>
		{
		public:

			/**
			*
			*
			* @param Context	The calling context.
			* @param Data
			* return
			*/
			static bool IsValidChecked(const FString& Context, const DataType* Data);

			/**
			*
			*
			* @param Context	The calling context.
			* @param Data
			* @param Log		(optional)
			* return
			*/
			static bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &NCsWeapon::FLog::Warning);
		};

	#undef DataType
	}
}