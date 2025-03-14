// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Data/CsData_Projectile.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "CsMacro_Log.h"
// Log
#include "Utility/CsPrjLog.h"

namespace NCsProjectile
{
	namespace NData
	{
		namespace NLibrary
		{
			using DataType = NCsProjectile::NData::IData;

			struct CSPRJ_API FLibrary final : public NCsInterfaceMap::TLibrary<DataType>
			{
			private:

				CS_DECLARE_STATIC_LOG_LEVEL

			public:

				/**
				*
				*
				* @param Data	Object that implements the interface: DataType (NCsProjectile::NData::IData).
				* return
				*/
				static FString PrintObjectAndClass(const DataType* Data);

				/**
				*
				*
				* @param Data	Object that implements the interface: DataType (NCsProjectile::NData::IData).
				* return
				*/
				static FString PrintDataAndClass(const DataType* Data);

				static FString Print(const DataType* Data);

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
				static bool IsValid(const FString& Context, const DataType* Data, CS_FN_PARAM_DEFAULT_LOG_LEVEL);
			};
		}
	}
}

using CsProjectileDataLibrary = NCsProjectile::NData::NLibrary::FLibrary;
using CsPrjDataLibrary = NCsProjectile::NData::NLibrary::FLibrary;