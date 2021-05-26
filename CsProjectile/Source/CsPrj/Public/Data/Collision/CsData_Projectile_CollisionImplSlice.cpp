// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Collision/CsData_Projectile_CollisionImplSlice.h"

// Library
#include "Library/CsLibrary_Valid.h"

#define SliceType NCsProjectile::NData::NCollision::FImplSlice

void FCsData_Projectile_CollisionImplSlice::CopyToSlice(SliceType* Slice)
{
	Slice->SetCollisionPreset(&Preset);
	Slice->SetCollisionRadius(&Radius);
}

void FCsData_Projectile_CollisionImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Slice->SetCollisionPreset(Preset);
	Slice->SetCollisionRadius(Radius);
}

#undef SliceType

bool FCsData_Projectile_CollisionImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	// TODO: Add Check for Preset

	CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)
	return true;
}

const FName NCsProjectile::NData::NCollision::FImplSlice::Name = FName("NCsProjectile::NData::NCollision::FImplSlice");

namespace NCsProjectile
{
	namespace NData
	{
		namespace NCollision
		{
			bool FImplSlice::IsValidChecked(const FString& Context) const
			{
				// TODO: Add Check for Preset

				CS_IS_FLOAT_GREATER_THAN_CHECKED(CollisionRadius, 0.0f)
				return true;
			}

			bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&)/*=&NCsProjectile::FLog::Warning*/) const
			{
				// TODO: Add Check for Preset

				CS_IS_FLOAT_GREATER_THAN(CollisionRadius, 0.0f)
				return true;
			}
		}
	}
}