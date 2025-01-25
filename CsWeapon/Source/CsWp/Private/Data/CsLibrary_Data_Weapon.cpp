// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Weapon.h"

// Library
#include "Projectile/Data/CsLibrary_Data_ProjectileWeapon.h"
#include "Trace/Data/CsLibrary_Data_TraceWeapon.h"
#include "Point/Data/CsLibrary_Data_PointWeapon.h"

namespace NCsWeapon
{
	namespace NData
	{
		namespace NLibrary
		{
			bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
			{
				// Projectile
				if (const CsProjectileWeaponDataType* PrjData = GetSafeInterfaceChecked<CsProjectileWeaponDataType>(Context, Data))
					return CsProjectileWeaponDataLibrary::IsValidChecked(Context, PrjData);
				// Trace
				if (const CsTraceWeaponDataType* TraceData = GetSafeInterfaceChecked<CsTraceWeaponDataType>(Context, Data))
					return CsTraceWeaponDataLibrary::IsValidChecked(Context, TraceData);
				// Point
				if (const CsPointWeaponDataType* PointData = GetSafeInterfaceChecked<CsPointWeaponDataType>(Context, Data))
					return CsPointWeaponDataLibrary::IsValidChecked(Context, PointData);
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
			{
				// Projectile
				if (const CsProjectileWeaponDataType* PrjData = GetSafeInterfaceChecked<CsProjectileWeaponDataType>(Context, Data))
					return CsProjectileWeaponDataLibrary::IsValid(Context, PrjData, Log);
				// Trace
				if (const CsTraceWeaponDataType* TraceData = GetSafeInterfaceChecked<CsTraceWeaponDataType>(Context, Data))
					return CsTraceWeaponDataLibrary::IsValid(Context, TraceData, Log);
				// Point
				if (const CsPointWeaponDataType* PointData = GetSafeInterfaceChecked<CsPointWeaponDataType>(Context, Data))
					return CsPointWeaponDataLibrary::IsValid(Context, PointData, Log);
				return true;
			}
		}
	}
}