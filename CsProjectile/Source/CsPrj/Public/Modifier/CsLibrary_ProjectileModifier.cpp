// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/Damage/CsProjectileModifier_DamageValuePointImpl.h"

namespace NCsProjectile
{
	namespace NModifier
	{
		#define ModifierType NCsProjectile::NModifier::IModifier

		const FECsProjectileModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			// DamageValuePoint
			typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgModiferValuePointType;

			if (SafeStaticCastChecked<PrjDmgModiferValuePointType>(Context, Modifier))
				return NCsProjectileModifier::DamageValuePoint;

			checkf(0, TEXT("%s: Failed to determine type (FECsProjectileModifier) for Value."), *Context);
			return EMCsProjectileModifier::Get().GetMAX();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			CS_IS_PTR_NULL_CHECKED(To)

			// DamageValuePoint
			{
				typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgModiferValuePointType;

				if (const PrjDmgModiferValuePointType* FromImpl = SafeStaticCastChecked<PrjDmgModiferValuePointType>(Context, From))
				{
					PrjDmgModiferValuePointType* ToImpl = StaticCastChecked<PrjDmgModiferValuePointType>(Context, To);

					FromImpl->CopyTo(ToImpl);
					return true;
				}
			}
			return false;
		}

		#undef ModifierType
	}
}