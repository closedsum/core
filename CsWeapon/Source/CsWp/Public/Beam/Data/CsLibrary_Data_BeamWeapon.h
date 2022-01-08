// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Beam/Data/CsData_BeamWeapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsWpLog.h"

namespace NCsWeapon
{
	namespace NBeam
	{
		namespace NData
		{
		#define DataType NCsWeapon::NBeam::NData::IData

			/**
			*/
			struct CSWP_API FLibrary : public NCsInterfaceMap::TLibrary<DataType>
			{
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
}