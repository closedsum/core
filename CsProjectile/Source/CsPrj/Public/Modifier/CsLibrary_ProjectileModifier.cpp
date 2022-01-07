// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "CsPrj.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Projectile
#include "Modifier/Damage/CsProjectileModifier_DamageValuePointImpl.h"
#include "Modifier/Speed/CsProjectileModifier_InitialSpeedImpl.h"
#include "Modifier/Speed/CsProjectileModifier_MaxSpeedImpl.h"

namespace NCsProjectile
{
	namespace NModifier
	{
		#define ModifierType NCsProjectile::NModifier::IModifier

		bool FLibrary::IsValidChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			// Speed

				// Initial
			{
				typedef NCsProjectile::NModifier::NSpeed::NInitial::FImpl PrjSpeedModifierType;

				if (const PrjSpeedModifierType* Impl = SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
					return Impl->IsValidChecked(Context);
			}
				// Max
			{
				typedef NCsProjectile::NModifier::NSpeed::NMax::FImpl PrjSpeedModifierType;

				if (const PrjSpeedModifierType* Impl = SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
					return Impl->IsValidChecked(Context);
			}
			// DamageValuePoint
			typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgValuePointModiferType;

			if (const PrjDmgValuePointModiferType* Impl = SafeStaticCastChecked<PrjDmgValuePointModiferType>(Context, Modifier))
				return Impl->IsValidChecked(Context);
			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			CS_IS_PTR_NULL(Modifier)

			// Speed

				// Initial
			{
				typedef NCsProjectile::NModifier::NSpeed::NInitial::FImpl PrjSpeedModifierType;

				if (const PrjSpeedModifierType* Impl = SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
					return Impl->IsValid(Context, Log);
			}
				// Max
			{
				typedef NCsProjectile::NModifier::NSpeed::NMax::FImpl PrjSpeedModifierType;

				if (const PrjSpeedModifierType* Impl = SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
					return Impl->IsValid(Context, Log);
			}
			// DamageValuePoint
			typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgValuePointModiferType;

			if (const PrjDmgValuePointModiferType* Impl = SafeStaticCastChecked<PrjDmgValuePointModiferType>(Context, Modifier))
				return Impl->IsValid(Context, Log);
			return true;
		}

		const FECsProjectileModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			// Speed

				// Initial
			{
				typedef NCsProjectile::NModifier::NSpeed::NInitial::FImpl PrjSpeedModifierType;

				if (SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
					return NCsProjectileModifier::InitialSpeed;
			}
				// Max
			{
				typedef NCsProjectile::NModifier::NSpeed::NMax::FImpl PrjSpeedModifierType;

				if (SafeStaticCastChecked<PrjSpeedModifierType>(Context, Modifier))
					return NCsProjectileModifier::MaxSpeed;
			}
			// DamageValuePoint
			typedef NCsProjectile::NModifier::NDamage::NValue::NPoint::FImpl PrjDmgValuePointModiferType;

			if (SafeStaticCastChecked<PrjDmgValuePointModiferType>(Context, Modifier))
				return NCsProjectileModifier::DamageValuePoint;
			checkf(0, TEXT("%s: Failed to determine type (FECsProjectileModifier) for Value."), *Context);
			return EMCsProjectileModifier::Get().GetMAX();
		}

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

		#undef ModifierType
	}
}