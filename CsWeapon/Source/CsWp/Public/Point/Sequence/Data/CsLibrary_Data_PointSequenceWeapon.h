// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Interface
#include "Point/Sequence/Data/CsData_PointSequenceWeapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsWpLog.h"

namespace NCsWeapon
{
	namespace NPoint
	{
		namespace NSequence
		{
			namespace NData
			{

			#define DataType NCsWeapon::NPoint::NSequence::NData::IData

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
}