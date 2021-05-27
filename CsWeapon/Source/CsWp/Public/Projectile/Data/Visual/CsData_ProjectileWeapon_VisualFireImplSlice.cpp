// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Data/Visual/CsData_ProjectileWeapon_VisualFireImplSlice.h"

#define SliceType NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice

void FCsData_ProjectileWeapon_VisualFireImplSlice::CopyToSlice(SliceType* Slice)
{
	Params.CopyParams(Slice->GetFireFXParamsPtr());
}

#undef SliceType

bool FCsData_ProjectileWeapon_VisualFireImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
{
	if (!Params.IsValid(Context, Log))
		return false;
	return true;
}

const FName NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice::Name = FName("NCsWeapon::NProjectile::NData::NVisual::NFire::FImplSlice");

namespace NCsWeapon
{
	namespace NProjectile
	{
		namespace NData
		{
			namespace NVisual
			{
				namespace NFire
				{
					bool FImplSlice::IsValidChecked(const FString& Context) const
					{
						check(Params.IsValidChecked(Context));
						return true;
					}

					bool FImplSlice::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/) const
					{
						if (!Params.IsValid(Context, Log))
							return false;
						return true;
					}
				}
			}
		}
	}
}