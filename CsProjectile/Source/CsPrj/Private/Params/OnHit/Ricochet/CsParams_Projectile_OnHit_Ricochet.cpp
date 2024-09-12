// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Params/OnHit/Ricochet/CsParams_Projectile_OnHit_Ricochet.h"

// Library
#include "Library/CsLibrary_Valid.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsParams_Projectile_OnHit_Ricochet)

// FCsProjectile_OnHit_RicochetParams
#pragma region

#define ParamsType NCsProjectile::NOnHit::NRicochet::FParams

void FCsProjectile_OnHit_RicochetParams::CopyToParams(ParamsType* Params)
{
	Params->SetRadius(&Radius);
	Params->SetbInheritModifiers(&bInheritModifiers);
	Modifiers.CopyToInfo(Params->GetModifiersPtr());
}

void FCsProjectile_OnHit_RicochetParams::CopyToParamsAsValue(ParamsType* Params) const
{
	Params->SetRadius(Radius);
	Params->SetbInheritModifiers(bInheritModifiers);
	Modifiers.CopyToInfoAsValue(Params->GetModifiersPtr());
}

#undef ParamsType

bool FCsProjectile_OnHit_RicochetParams::IsValidChecked(const FString& Context) const
{
	CS_IS_FLOAT_GREATER_THAN_CHECKED(Radius, 0.0f)
	CS_IS_VALID_CHECKED(Modifiers);
	return true;
}

bool FCsProjectile_OnHit_RicochetParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
{
	CS_IS_FLOAT_GREATER_THAN(Radius, 0.0f)
	CS_IS_VALID(Modifiers)
	return true;
}

namespace NCsProjectile
{
	namespace NOnHit
	{
		namespace NRicochet
		{
			bool FParams::IsValidChecked(const FString& Context) const
			{
				CS_IS_FLOAT_GREATER_THAN_CHECKED(GetRadius(), 0.0f)
				CS_IS_VALID_CHECKED(Modifiers);
				return true;
			}

			bool FParams::IsValid(const FString& Context, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/) const
			{
				CS_IS_FLOAT_GREATER_THAN(GetRadius(), 0.0f)
				CS_IS_VALID(Modifiers)
				return true;
			}
		}
	}
}

#pragma endregion FCsProjectile_OnHit_RicochetParams