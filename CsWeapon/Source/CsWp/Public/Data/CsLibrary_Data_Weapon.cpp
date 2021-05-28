// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/CsLibrary_Data_Weapon.h"

// Library
#include "Projectile/Data/CsLibrary_Data_ProjectileWeapon.h"
#include "Trace/Data/CsLibrary_Data_TraceWeapon.h"

namespace NCsWeapon
{
	namespace NData
	{
		#define DataType NCsWeapon::NData::IData

		bool FLibrary::IsValidChecked(const FString& Context, const DataType* Data)
		{
			typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;
			typedef NCsWeapon::NProjectile::NData::FLibrary ProjectileDataLibrary;

			if (const ProjectileDataType* PrjData = GetSafeInterfaceChecked<ProjectileDataType>(Context, Data))
				return ProjectileDataLibrary::IsValidChecked(Context, PrjData);

			typedef NCsWeapon::NTrace::NData::IData TraceDataType;
			typedef NCsWeapon::NTrace::NData::FLibrary TraceDataLibrary;

			if (const TraceDataType* TraceData = GetSafeInterfaceChecked<TraceDataType>(Context, Data))
				return TraceDataLibrary::IsValidChecked(Context, TraceData);

			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const DataType* Data, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			typedef NCsWeapon::NProjectile::NData::IData ProjectileDataType;
			typedef NCsWeapon::NProjectile::NData::FLibrary ProjectileDataLibrary;

			if (const ProjectileDataType* PrjData = GetSafeInterfaceChecked<ProjectileDataType>(Context, Data))
				return ProjectileDataLibrary::IsValid(Context, PrjData, Log);

			typedef NCsWeapon::NTrace::NData::IData TraceDataType;
			typedef NCsWeapon::NTrace::NData::FLibrary TraceDataLibrary;

			if (const TraceDataType* TraceData = GetSafeInterfaceChecked<TraceDataType>(Context, Data))
				return TraceDataLibrary::IsValid(Context, TraceData, Log);

			return true;
		}

		#undef DataType
	}
}