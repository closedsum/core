// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Data/CsData_Beam.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsBeamLog.h"

namespace NCsBeam
{
	namespace NData
	{
	#define DataType NCsBeam::NData::IData

		struct CSBEAM_API FLibrary final : public NCsInterfaceMap::TLibrary<DataType>
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
			static bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &NCsBeam::FLog::Warning);
		};

	#undef DataType
	}
}