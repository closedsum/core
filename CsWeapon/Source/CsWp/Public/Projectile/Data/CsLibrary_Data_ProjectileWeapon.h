// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Projectile/Data/CsData_ProjectileWeapon.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Log
#include "Utility/CsWpLog.h"

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{

		#define DataType NCsWeapon::NProjectile::NData::IData

			/**
			*/
			struct CSWP_API FLibrary : public TCsLibrary_InterfaceMap<DataType>
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