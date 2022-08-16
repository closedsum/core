// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_WeaponModifier.h"
#include "CsWp.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Modifier
#include "Modifier/Types/CsGetWeaponModifierType.h"
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Float.h"
#include "Modifier/CsModifier_Toggle.h"

namespace NCsWeapon
{
	namespace NModifier
	{
		#define ModifierType NCsWeapon::NModifier::IModifier

		bool FLibrary::IsValidChecked(const FString& Context, const ModifierType* Modifier)
		{
			CS_IS_PTR_NULL_CHECKED(Modifier)

			return true;
		}

		bool FLibrary::IsValid(const FString& Context, const ModifierType* Modifier, void(*Log)(const FString&) /*=&NCsWeapon::FLog::Warning*/)
		{
			CS_IS_PTR_NULL(Modifier)

			return true;
		}

		#define AllocatedModifierType NCsWeapon::NModifier::FAllocated

		void FLibrary::AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers)
		{
			CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)

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

		int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const int32& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			int32 Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NInt::IInt IntModifierType;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier								  = AllocatedModifier.Get();
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					IntModifierType* IntModifier = GetInterfaceChecked<IntModifierType>(Context, Modifier);
					Result						 = IntModifier->Modify(Value);
				}
			}
			return Result;
		}

		int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const int32& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			int32 Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NInt::IInt IntModifierType;

			for (ModifierType* Modifier : Modifiers)
			{
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					IntModifierType* IntModifier = GetInterfaceChecked<IntModifierType>(Context, Modifier);
					Result						 = IntModifier->Modify(Value);
				}
			}
			return Result;
		}

		float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			float Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;

			// TODO: FUTURE: Use a tiny / small array on the stack
			static TArray<FloatModifierType*> FirstModifiers;
			static TArray<FloatModifierType*> Modifiers;
			static TArray<FloatModifierType*> LastModifiers;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier								  = AllocatedModifier.Get();
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

					typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

					const ApplicationType& Application = FloatModifier->GetApplication();

					// PercentAddFirst
					if (Application == ApplicationType::PercentAddFirst)
					{
						FirstModifiers.Add(FloatModifier);
					}
					// PercentAddLast
					else
					if (Application == ApplicationType::PercentAddLast)
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

			// PercentAddFirst
			{
				float Percent = 1.0f;

				const int32 Count = FirstModifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const FloatModifierType* FloatModifier = FirstModifiers[I];
					
					Percent = FloatModifier->Modify(Percent);
					
					FirstModifiers.RemoveAt(I, 1, false);
				}
				Result *= Percent;
			}
			// "The Rest"
			{
				const int32 Count = Modifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const FloatModifierType* FloatModifier = Modifiers[I];

					Result = FloatModifier->Modify(Value);

					Modifiers.RemoveAt(I, 1, false);
				}
			}
			// PercentAddLast
			{
				float Percent = 1.0f;

				const int32 Count = LastModifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const FloatModifierType* FloatModifier = LastModifiers[I];

					Percent = FloatModifier->Modify(Percent);

					LastModifiers.RemoveAt(I, 1, false);
				}
				Result *= Percent;
			}
			return Result;
		}

		float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			float Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NFloat::IFloat FloatModifierType;

			// TODO: FUTURE: Use a tiny / small array on the stack
			static TArray<FloatModifierType*> FirstModifiers;
			static TArray<FloatModifierType*> TempModifiers;
			static TArray<FloatModifierType*> LastModifiers;

			for (ModifierType* Modifier : Modifiers)
			{
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					FloatModifierType* FloatModifier = GetInterfaceChecked<FloatModifierType>(Context, Modifier);

					typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

					const ApplicationType& Application = FloatModifier->GetApplication();

					// PercentAddFirst
					if (Application == ApplicationType::PercentAddFirst)
					{
						FirstModifiers.Add(FloatModifier);
					}
					// PercentAddLast
					else
					if (Application == ApplicationType::PercentAddLast)
					{
						LastModifiers.Add(FloatModifier);
					}
					// "The Rest"
					else
					{
						TempModifiers.Add(FloatModifier);
					}
				}
			}

			// NOTE: For now ignore order

			// PercentAddFirst
			{
				float Percent = 1.0f;

				const int32 Count = FirstModifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const FloatModifierType* FloatModifier = FirstModifiers[I];
					
					Percent = FloatModifier->Modify(Percent);
					
					FirstModifiers.RemoveAt(I, 1, false);
				}
				Result *= Percent;
			}
			// "The Rest"
			{
				const int32 Count = TempModifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const FloatModifierType* FloatModifier = TempModifiers[I];

					Result = FloatModifier->Modify(Value);

					TempModifiers.RemoveAt(I, 1, false);
				}
			}
			// PercentAddLast
			{
				float Percent = 1.0f;

				const int32 Count = LastModifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					const FloatModifierType* FloatModifier = LastModifiers[I];

					Percent = FloatModifier->Modify(Percent);

					LastModifiers.RemoveAt(I, 1, false);
				}
				Result *= Percent;
			}
			return Result;
		}

		bool FLibrary::ToggleChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			typedef NCsModifier::NToggle::IToggle ToggleModifierType;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier							= AllocatedModifier.Get();
				ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType    = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == NCsWeaponModifier::PrjWp_UseSpreadParams)
				{
					ToggleModifierType* ToggleModifier = GetInterfaceChecked<ToggleModifierType>(Context, Modifier);

					if (ToggleModifier->IsEnabled())
						return true;
				}
			}
			return false;
		}

		bool FLibrary::ToggleChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			typedef NCsModifier::NToggle::IToggle ToggleModifierType;

			for (ModifierType* Modifier : Modifiers)
			{
				ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType    = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == NCsWeaponModifier::PrjWp_UseSpreadParams)
				{
					ToggleModifierType* ToggleModifier = GetInterfaceChecked<ToggleModifierType>(Context, Modifier);

					if (ToggleModifier->IsEnabled())
						return true;
				}
			}
			return false;
		}

		#undef AllocatedModifierType

		#undef ModifierType
	}
}