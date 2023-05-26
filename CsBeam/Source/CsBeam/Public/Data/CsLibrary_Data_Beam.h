// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Beam.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsBeamLog.h"
#pragma once

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