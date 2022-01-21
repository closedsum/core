// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "CsPrj.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Valid/CsIsValid.h"
// Projectile
#include "Modifier/Types/CsGetProjectileModifierType.h"
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
			const ICsIsValid* Valid = GetInterfaceChecked<ICsIsValid>(Context, Modifier);

			return Valid->IsValidChecked(Context);
		}

		bool FLibrary::IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) /*=&NCsProjectile::FLog::Warning*/)
		{
			const ICsIsValid* Valid = GetInterfaceChecked<ICsIsValid>(Context, Modifier);

			return Valid->IsValid(Context, Log);
		}

		const FECsProjectileModifier& FLibrary::GetTypeChecked(const FString& Context, const ModifierType* Modifier)
		{
			const ICsGetProjectileModifierType* GetProjectileModifierType = GetInterfaceChecked<ICsGetProjectileModifierType>(Context, Modifier);

			return GetProjectileModifierType->GetProjectileModifierType();
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