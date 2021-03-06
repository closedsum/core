// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsData_Projectile.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsPrjLog.h"
#pragma once

namespace NCsProjectile
{
	namespace NData
	{
	#define DataType NCsProjectile::NData::IData

		struct CSPRJ_API FLibrary final : public TCsLibrary_InterfaceMap<DataType>
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
			static bool IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) = &NCsProjectile::FLog::Warning);
		};

	#undef DataType
	}
}