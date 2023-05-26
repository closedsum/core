// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Types/CsData_GetProjectileTypeImplSlice.h"

// Library
#include "Library/CsLibrary_Valid.h"

#define SliceType NCsProjectile::NData::NType::FImplSlice

void FCsData_GetProjectileTypeImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetProjectileType(Type);
}

void FCsData_GetProjectileTypeImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetProjectileType(Type);
}

#undef SliceType

bool FCsData_GetProjectileTypeImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Type)
	return true;
}

const FName NCsProjectile::NData::NType::FImplSlice::Name = FName("NCsProjectile::NData::NType::FImplSlice");

namespace NCsProjectile
{
	namespace NData
	{
		namespace NType
		{
			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				EMCsProjectile::Get().IsValidEnumChecked(Context, GetProjectileType());
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, GetProjectileType())
				return true;
			}
		}
	}
}