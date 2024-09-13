// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_WeaponModifier.h"
#include "CsWp.h"

// Library
#include "CsLibrary_Modifier.h"
#include "Library/CsLibrary_Valid.h"
// Modifier
#include "Modifier/Types/CsGetWeaponModifierType.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"
#include "CsModifier_Toggle.h"

namespace NCsWeapon
{
	namespace NModifier
	{
		#define ModifierType NCsWeapon::NModifier::IModifier
		#define AllocatedModifierType NCsWeapon::NModifier::FAllocated

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

		// Int
		#pragma region

		int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const int32& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			int32 Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier								  = AllocatedModifier.Get();
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					CsIntModifierType* IntModifier = GetInterfaceChecked<CsIntModifierType>(Context, Modifier);
					Result						   = IntModifier->Modify(Result);
				}
			}
			return Result;
		}

		int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const int32& Value)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			int32 Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

			for (ModifierType* Modifier : Modifiers)
			{
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					CsIntModifierType* IntModifier = GetInterfaceChecked<CsIntModifierType>(Context, Modifier);
					Result						   = IntModifier->Modify(Result);
				}
			}
			return Result;
		}

		int32 FLibrary::ModifyIntAndEmptyChecked(const FString& Context, TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const int32& Value)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			int32 Result = Value;

			typedef NCsWeapon::NModifier::FLibrary ModifierLibrary;

			const int32 Count = Modifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				ModifierType* Modifier = Modifiers[I];

				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					CsIntModifierType* IntModifier = GetInterfaceChecked<CsIntModifierType>(Context, Modifier);
					Result						   = IntModifier->Modify(Result);
				}
				Modifiers.RemoveAt(I, 1, false);
			}
			return Result;
		}

		#pragma endregion Int

		// Float
		#pragma region

		float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			if (AllocatedModifiers.Num() <= 64)
			{
				return ModifyFloatChecked_Size64(Context, AllocatedModifiers, Type, Value);
			}
			else
			{
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

				float Result = Value;

				static TArray<CsFloatModifierType*> FirstModifiers;
				static TArray<CsFloatModifierType*> Modifiers;
				static TArray<CsFloatModifierType*> LastModifiers;

				for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
				{
					ModifierType* Modifier								  = AllocatedModifier.Get();
					const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
					const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

					if (WeaponModifierType == Type)
					{
						CsFloatModifierType* FloatModifier = GetInterfaceChecked<CsFloatModifierType>(Context, Modifier);

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

				// PercentAddFirst || PercentSubtractFirst
				Result = CsModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, FirstModifiers, Result);
				// "The Rest"
				Result = CsModifierLibrary::ModifyFloatAndEmptyChecked(Context, Modifiers, Result);
				// PercentAddLast || PercentSubtractLast
				Result = CsModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, LastModifiers, Result);
				return Result;
			}
		}

		float FLibrary::ModifyFloatChecked_Size64(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(AllocatedModifiers, AllocatedModifierType, 64)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			float Result = Value;

			TArray<CsFloatModifierType*, TFixedAllocator<64>> FirstModifiers;
			TArray<CsFloatModifierType*, TFixedAllocator<64>> Modifiers;
			TArray<CsFloatModifierType*, TFixedAllocator<64>> LastModifiers;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier								  = AllocatedModifier.Get();
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					CsFloatModifierType* FloatModifier = GetInterfaceChecked<CsFloatModifierType>(Context, Modifier);

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

			// PercentAddFirst || PercentSubtractFirst
			Result = CsModifierLibrary::ModifyFloatPercentChecked(Context, FirstModifiers, Result);
			// "The Rest"
			Result = CsModifierLibrary::ModifyFloatChecked(Context, Modifiers, Result);
			// PercentAddLast || PercentSubtractLast
			Result = CsModifierLibrary::ModifyFloatPercentChecked(Context, LastModifiers, Result);
			return Result;
		}

		float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			if (Modifiers.Num() <= 64)
			{
				return ModifyFloatChecked_Size64(Context, Modifiers, Type, Value);
			}
			else
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

				float Result = Value;

				static TArray<CsFloatModifierType*> FirstModifiers;
				static TArray<CsFloatModifierType*> TempModifiers;
				static TArray<CsFloatModifierType*> LastModifiers;

				for (ModifierType* Modifier : Modifiers)
				{
					const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
					const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

					if (WeaponModifierType == Type)
					{
						CsFloatModifierType* FloatModifier = GetInterfaceChecked<CsFloatModifierType>(Context, Modifier);

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
							TempModifiers.Add(FloatModifier);
						}
					}
				}

				// NOTE: For now ignore order

				// PercentAddFirst || PercentSubtractFirst
				Result = CsModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, FirstModifiers, Result);
				// "The Rest"
				Result = CsModifierLibrary::ModifyFloatAndEmptyChecked(Context, TempModifiers, Result);
				// PercentAddLast || PercentSubtractLast
				Result = CsModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, LastModifiers, Result);
				return Result;
			}
		}

		float FLibrary::ModifyFloatChecked_Size64(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(Modifiers, ModifierType*, 64)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			float Result = Value;

			TArray<CsFloatModifierType*, TFixedAllocator<64>> FirstModifiers;
			TArray<CsFloatModifierType*, TFixedAllocator<64>> TempModifiers;
			TArray<CsFloatModifierType*, TFixedAllocator<64>> LastModifiers;

			for (ModifierType* Modifier : Modifiers)
			{
				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					CsFloatModifierType* FloatModifier = GetInterfaceChecked<CsFloatModifierType>(Context, Modifier);

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
						TempModifiers.Add(FloatModifier);
					}
				}
			}

			// NOTE: For now ignore order

			// PercentAddFirst || PercentSubtractFirst
			Result = CsModifierLibrary::ModifyFloatPercentChecked(Context, FirstModifiers, Result);
			// "The Rest"
			Result = CsModifierLibrary::ModifyFloatChecked(Context, TempModifiers, Result);
			// PercentAddLast || PercentSubtractLast
			Result = CsModifierLibrary::ModifyFloatPercentChecked(Context, LastModifiers, Result);
			return Result;
		}

		float FLibrary::ModifyFloatAndEmptyChecked(const FString& Context, TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			if (Modifiers.Num() <= 64)
			{
				return ModifyFloatAndEmptyChecked_Size64(Context, Modifiers, Type, Value);
			}
			else
			{
				CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
				CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

				float Result = Value;

				static TArray<CsFloatModifierType*> FirstModifiers;
				static TArray<CsFloatModifierType*> TempModifiers;
				static TArray<CsFloatModifierType*> LastModifiers;

				const int32 Count = Modifiers.Num();

				for (int32 I = Count - 1; I >= 0; --I)
				{
					ModifierType* Modifier = Modifiers[I];

					const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
					const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

					if (WeaponModifierType == Type)
					{
						CsFloatModifierType* FloatModifier = GetInterfaceChecked<CsFloatModifierType>(Context, Modifier);

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
							TempModifiers.Add(FloatModifier);
						}
					}
					Modifiers.RemoveAt(I, 1, false);
				}

				// NOTE: For now ignore order

				// PercentAddFirst || PercentSubtractFirst
				Result = CsModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, FirstModifiers, Result);
				// "The Rest"
				Result = CsModifierLibrary::ModifyFloatAndEmptyChecked(Context, TempModifiers, Result);
				// PercentAddLast || PercentSubtractLast
				Result = CsModifierLibrary::ModifyFloatPercentAndEmptyChecked(Context, LastModifiers, Result);
				return Result;
			}
		}

		float FLibrary::ModifyFloatAndEmptyChecked_Size64(const FString& Context, TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type, const float& Value)
		{
			CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, ModifierType)
			CS_IS_TARRAY_LESS_THAN_OR_EQUAL_SIZE_CHECKED(Modifiers, ModifierType*, 64)
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			float Result = Value;

			TArray<CsFloatModifierType*, TFixedAllocator<64>> FirstModifiers;
			TArray<CsFloatModifierType*, TFixedAllocator<64>> TempModifiers;
			TArray<CsFloatModifierType*, TFixedAllocator<64>> LastModifiers;

			const int32 Count = Modifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				ModifierType* Modifier = Modifiers[I];

				const ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType		  = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == Type)
				{
					CsFloatModifierType* FloatModifier = GetInterfaceChecked<CsFloatModifierType>(Context, Modifier);

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
						TempModifiers.Add(FloatModifier);
					}
				}
				Modifiers.RemoveAt(I, 1, false);
			}

			// NOTE: For now ignore order

			// PercentAddFirst || PercentSubtractFirst
			Result = CsModifierLibrary::ModifyFloatPercentChecked(Context, FirstModifiers, Result);
			// "The Rest"
			Result = CsModifierLibrary::ModifyFloatChecked(Context, TempModifiers, Result);
			// PercentAddLast || PercentSubtractLast
			Result = CsModifierLibrary::ModifyFloatPercentChecked(Context, LastModifiers, Result);
			return Result;
		}

		#pragma endregion Float

		bool FLibrary::ToggleChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsWeaponModifier& Type)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier							= AllocatedModifier.Get();
				ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType    = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == NCsWeaponModifier::PrjWp_UseSpreadParams)
				{
					CsToggleModifierType* ToggleModifier = GetInterfaceChecked<CsToggleModifierType>(Context, Modifier);

					if (ToggleModifier->IsEnabled())
						return true;
				}
			}
			return false;
		}

		bool FLibrary::ToggleChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const FECsWeaponModifier& Type)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsWeaponModifier, Type)

			for (ModifierType* Modifier : Modifiers)
			{
				ICsGetWeaponModifierType* GetWeaponModifierType = GetInterfaceChecked<ICsGetWeaponModifierType>(Context, Modifier);
				const FECsWeaponModifier& WeaponModifierType    = GetWeaponModifierType->GetWeaponModifierType();

				if (WeaponModifierType == NCsWeaponModifier::PrjWp_UseSpreadParams)
				{
					CsToggleModifierType* ToggleModifier = GetInterfaceChecked<CsToggleModifierType>(Context, Modifier);

					if (ToggleModifier->IsEnabled())
						return true;
				}
			}
			return false;
		}

		#undef ModifierType
		#undef AllocatedModifierType
	}
}