// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Data/Damage/CsData_Projectile_DamagePointImplSlice.h"

#define SliceType NCsProjectile::NData::NDamage::NPoint::FImplSlice

void FCsData_Projectile_DamagePointImplSlice::CopyToSlice(SliceType* Slice)
{
	Damage.CopyToPoint(Slice->GetDamageDataImpl());
}

void FCsData_Projectile_DamagePointImplSlice::CopyToSliceAsValue(SliceType* Slice) const
{
	Damage.CopyToPointAsValue(Slice->GetDamageDataImpl());
}

#undef SliceType

bool FCsData_Projectile_DamagePointImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	if (!Damage.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsProjectile::NData::NDamage::NPoint::FImplSlice::Name = FName("NCsProjectile::NData::NDamage::NPoint::FImplSlice");

namespace NCsProjectile
{
	namespace NData
	{
		namespace NDamage
		{
			namespace NPoint
			{
				bool FImplSlice::IsValidChecked(const FString& Context) const
				{
					check(DamageData.IsValidChecked(Context));
					return true;
				}

				bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
				{
					if (!DamageData.IsValid(Context, Log))
						return false;
					return true;
				}
			}
		}
	}
}