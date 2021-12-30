// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "CsCore.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/Damage/CsProjectileModifier_DamageValuePointImpl.h"
#include "Modifier/Speed/CsProjectileModifier_SpeedImpl.h"

namespace NCsProjectile
{
	namespace NModifier
	{
		#define ModifierType NCsProjectile::NModifier::IModifier

		const FECsProjectileModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			// DamageValuePoint
			typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgValuePointModiferType;

			if (SafeStaticCastChecked<PrjDmgValuePointModiferType>(Context, Modifier))
				return NCsProjectileModifier::DamageValuePoint;
			// Speed
			typedef NCsProjectile::NModifier::NSpeed::FImpl PrjSpeedModifierType;

			if (SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
				return NCsProjectileModifier::Speed;

			checkf(0, TEXT("%s: Failed to determine type (FECsProjectileModifier) for Value."), *Context);
			return EMCsProjectileModifier::Get().GetMAX();
		}

		bool FLibrary::CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To)
		{
			CS_IS_PTR_NULL_CHECKED(From)

			CS_IS_PTR_NULL_CHECKED(To)

			// DamageValuePoint
			{
				typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgValuePointModiferType;

				if (const PrjDmgValuePointModiferType* FromImpl = SafeStaticCastChecked<PrjDmgValuePointModiferType>(Context, From))
				{
					PrjDmgValuePointModiferType* ToImpl = StaticCastChecked<PrjDmgValuePointModiferType>(Context, To);

					FromImpl->CopyTo(ToImpl);
					return true;
				}
			}
			// Speed
			{
				typedef NCsProjectile::NModifier::NSpeed::FImpl PrjSpeedModifierType;

				if (const PrjSpeedModifierType* FromImpl = SafeStaticCastChecked<PrjSpeedModifierType>(Context, From))
				{
					PrjSpeedModifierType* ToImpl = StaticCastChecked<PrjSpeedModifierType>(Context, To);

					FromImpl->CopyTo(ToImpl);
					return true;
				}
			}
			return false;
		}

		#undef ModifierType

		// Damage
		#pragma region

		#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
		#define DmgModifierType NCsDamage::NModifier::IModifier

		void FLibrary::GetDamageModifiersChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, TArray<DmgModifierType*>& OutModifiers)
		{
			OutModifiers.Reset(FMath::Max(OutModifiers.Max(), Modifiers.Num()));

			for (const AllocatedModifierType& Modifier : Modifiers)
			{
				if (DmgModifierType* DmgModifier = GetSafeInterfaceChecked<DmgModifierType>(Context, Modifier.Modifier))
				{
					OutModifiers.Add(DmgModifier);
				}
			}
		}

		#undef AllocatedModifierType
		#undef DmgModifierType

		#pragma endregion Damage
	}
}