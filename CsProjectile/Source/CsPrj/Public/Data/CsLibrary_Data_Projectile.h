// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Projectile.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsPrjLog.h"

namespace NCsProjectile
{
	namespace NData
	{
	#define DataType NCsProjectile::NData::IData

		struct CSPRJ_API FLibrary final : public NCsInterfaceMap::TLibrary<DataType>
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