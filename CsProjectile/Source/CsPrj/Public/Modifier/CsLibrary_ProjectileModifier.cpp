// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_ProjectileModifier.h"
#include "CsPrj.h"

// Library
#include "Modifier/CsLibrary_Modifier.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Valid/CsIsValid.h"
// Modifier
#include "Modifier/Types/CsGetProjectileModifierType.h"
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Float.h"
// Damage
#include "Modifier/CsDamageModifier.h"

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

		#define AllocatedModifierType NCsProjectile::NModifier::FAllocated
		void FLibrary::AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)

			const int32 CountToAdd = Modifiers.Num();

			if (AllocatedModifiers.Num() + CountToAdd > AllocatedModifiers.Max())
			{
				const int32 Count = AllocatedModifiers.Num();

				static TArray<AllocatedModifierType> TempModifiers;
				TempModifiers.Reset(FMath::Max(TempModifiers.Max(), Count + CountToAdd));
				TempModifiers.AddDefaulted(Count + CountToAdd);

				for (int32 I = 0; I < Count; ++I)
				{
					AllocatedModifiers[I].Transfer(TempModifiers[I]);
				}
				AllocatedModifiers.Reset(Count + CountToAdd);
				AllocatedModifiers.AddDefaulted(Count);

				for (int32 I = 0; I < Count; ++I)
				{
					TempModifiers[I].Transfer(AllocatedModifiers[I]);
				}
			}

			for (ModifierType* Modifier : Modifiers)
			{
				AllocatedModifierType& AllocatedModifier = AllocatedModifiers.AddDefaulted_GetRef();
				AllocatedModifier.Copy(WorldContext, Modifier);
			}
		}
		#undef AllocatedModifierType

		// Int
		#pragma region

		#define AllocatedModifierType NCsProjectile::NModifier::FAllocated

		int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsProjectileModifier& Type, const int32& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, Type)

			int32 Result = Value;

			typedef NCsProjectile::NModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NInt::IInt IntModifierType;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier										  = AllocatedModifier.Get();
				const ICsGetProjectileModifierType* GetProjectileModifierType = GetInterfaceChecked<ICsGetProjectileModifierType>(Context, Modifier);
				const FECsProjectileModifier& PrjModifierType				  = GetProjectileModifierType->GetProjectileModifierType();

				if (PrjModifierType == Type)
				{
					IntModifierType* IntModifier = GetInterfaceChecked<IntModifierType>(Context, Modifier);
					Result						 = IntModifier->Modify(Value);
				}
			}
			return Result;
		}

		#undef AllocatedModifierType

		#pragma endregion Int

		// Float
		#pragma region 

		#define AllocatedModifierType NCsProjectile::NModifier::FAllocated

		float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsProjectileModifier& Type, const float& Value)
		{
			if (AllocatedModifiers.Num() <= 64)
			{
				return ModifyFloatChecked_Size64(Context, AllocatedModifiers, Type, Value);
			}
			else
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, Type)

				float Result = Value;

				typedef NCsModifier::NFloat::IFloat FloatModifierType;

				// TODO: FUTURE: Use a tiny / small array on the stack
				static TArray<FloatModifierType*> FirstModifiers;
				static TArray<FloatModifierType*> Modifiers;
				static TArray<FloatModifierType*> LastModifiers;

				for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
				{
					ModifierType* Modifier										  = AllocatedModifier.Get();
					const ICsGetProjectileModifierType* GetProjectileModifierType = GetInterfaceChecked<ICsGetProjectileModifierType>(Context, Modifier);
					const FECsProjectileModifier& PrjModifierType				  = GetProjectileModifierType->GetProjectileModifierType();

					if (PrjModifierType == Type)
					{
						FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

						typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

						const ApplicationType& Application = FloatModifier->GetApplication();

						// PercentAddFirst || PercentSubtractFirst
						if (Application == ApplicationType::PercentAddFirst ||
							Application == ApplicationType::PercentSubtractFirst)
						{
							FirstModifiers.Add(FloatModifier);
						}
						// PercentAddLast || PercentSubtractLast
						else
						if (Application == ApplicationType::PercentAddLast ||
							Application == ApplicationType::PercentSubtractLast)
						{
							LastModifiers.Add(FloatModifier);
						}
						// "The Rest"
						else
						{
							Modifiers.Add(FloatModifier);
						}
					}
				}

				// NOTE: For now ignore order

				typedef NCsModifier::FLibrary ModifierLibrary;

				// PercentAddFirst || PercentSubtractFirst
				Result = ModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, FirstModifiers, Result);
				// "The Rest"
				Result = ModifierLibrary::ModifyFloatAndEmptyChecked(Context, Modifiers, Result);
				// PercentAddLast || PercentSubtractLast
				Result = ModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, LastModifiers, Result);

				return Result;
			}
		}
		
		float FLibrary::ModifyFloatChecked_Size64(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsProjectileModifier& Type, const float& Value)
		{
			CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(AllocatedModifiers, AllocatedModifierType, 64)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsProjectileModifier, Type)

			float Result = Value;

			typedef NCsModifier::NFloat::IFloat FloatModifierType;

			TArray<FloatModifierType*, TFixedAllocator<64>> FirstModifiers;
			TArray<FloatModifierType*, TFixedAllocator<64>> Modifiers;
			TArray<FloatModifierType*, TFixedAllocator<64>> LastModifiers;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier										  = AllocatedModifier.Get();
				const ICsGetProjectileModifierType* GetProjectileModifierType = GetInterfaceChecked<ICsGetProjectileModifierType>(Context, Modifier);
				const FECsProjectileModifier& PrjModifierType				  = GetProjectileModifierType->GetProjectileModifierType();

				if (PrjModifierType == Type)
				{
					FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

					typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

					const ApplicationType& Application = FloatModifier->GetApplication();

					// PercentAddFirst || PercentSubtractFirst
					if (Application == ApplicationType::PercentAddFirst ||
						Application == ApplicationType::PercentSubtractFirst)
					{
						FirstModifiers.Add(FloatModifier);
					}
					// PercentAddLast || PercentSubtractLast
					else
					if (Application == ApplicationType::PercentAddLast ||
						Application == ApplicationType::PercentSubtractLast)
					{
						LastModifiers.Add(FloatModifier);
					}
					// "The Rest"
					else
					{
						Modifiers.Add(FloatModifier);
					}
				}
			}

			// NOTE: For now ignore order

			typedef NCsModifier::FLibrary ModifierLibrary;

			// PercentAddFirst || PercentSubtractFirst
			Result = ModifierLibrary::ModifyFloatPercentChecked(Context, FirstModifiers, Result);
			// "The Rest"
			Result = ModifierLibrary::ModifyFloatChecked(Context, Modifiers, Result);
			// PercentAddLast || PercentSubtractLast
			Result = ModifierLibrary::ModifyFloatPercentChecked(Context, LastModifiers, Result);

			return Result;
		}

		float FLibrary::ModifyFloatChecked(const FString& Context, const ModifierType* Modifier, const float& Value)
		{
			typedef NCsModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;

			const FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

			return ModifierLibrary::ModifyFloatChecked(Context, FloatModifier, Value);
		}

		#undef AllocatedModifierType

		#pragma endregion Float

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