// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Types/CsData_GetProjectileTypeImplSlice.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsData_GetProjectileTypeImplSlice)

using SliceType = NCsProjectile::NData::NType::FImplSlice;

void FCsData_GetProjectileTypeImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetProjectileType(Type);
}

void FCsData_GetProjectileTypeImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetProjectileType(Type);
}

bool FCsData_GetProjectileTypeImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_ENUM_STRUCT_VALID(EMCsProjectile, FECsProjectile, Type)
	return true;
}

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NData::NType::FImplSlice);

namespace NCsProjectile
{
	namespace NData
	{
		namespace NType
		{
			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectile, GetProjectileType());
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