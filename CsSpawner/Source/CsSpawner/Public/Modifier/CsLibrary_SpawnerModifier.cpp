// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Modifier/CsLibrary_SpawnerModifier.h"

// Library
#include "CsLibrary_Modifier.h"
#include "Library/CsLibrary_Valid.h"
// Interface
#include "Valid/CsIsValid.h"
// Modifier
#include "Modifier/Types/CsGetSpawnerModifierType.h"
#include "CsModifier_Int.h"
#include "CsModifier_Float.h"

namespace NCsSpawner
{
	namespace NModifier
	{
		#define LogLevel void(*Log)(const FString&) /*=&NCsSpawner::FLog::Warning*/
		#define ModifierType NCsSpawner::NModifier::IModifier

		bool FLibrary::IsValidChecked(const FString& Context, const ModifierType* Modifier)
		{
			const ICsIsValid* Valid = GetInterfaceChecked<ICsIsValid>(Context, Modifier);

			return Valid->IsValidChecked(Context);
		}

		bool FLibrary::IsValid(const FString& Context, const ModifierType* Modifier, LogLevel)
		{
			const ICsIsValid* Valid = GetInterfaceChecked<ICsIsValid>(Context, Modifier);

			return Valid->IsValid(Context, Log);
		}

		#define AllocatedModifierType NCsSpawner::NModifier::FAllocated

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

		int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsSpawnerModifier& Type, const int32& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, Type)

			int32 Result = Value;

			typedef NCsSpawner::NModifier::FLibrary ModifierLibrary;
			typedef NCsModifier::NInt::IInt IntModifierType;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier									   = AllocatedModifier.Get();
				const ICsGetSpawnerModifierType* GetSpawnerModifierType = GetInterfaceChecked<ICsGetSpawnerModifierType>(Context, Modifier);
				const FECsSpawnerModifier& SpawnerModifierType		   = GetSpawnerModifierType->GetSpawnerModifierType();

				if (SpawnerModifierType == Type)
				{
					IntModifierType* IntModifier = GetInterfaceChecked<IntModifierType>(Context, Modifier);
					Result						 = IntModifier->Modify(Value);
				}
			}
			return Result;
		}

		float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<AllocatedModifierType>& AllocatedModifiers, const FECsSpawnerModifier& Type, const float& Value)
		{
			CS_IS_ENUM_STRUCT_VALID_CHECKED(EMCsSpawnerModifier, Type)

			float Result = Value;

			typedef NCsModifier::NFloat::IFloat FloatModifierType;

			// TODO: FUTURE: Use a tiny / small array on the stack
			static TArray<FloatModifierType*> FirstModifiers;
			static TArray<FloatModifierType*> Modifiers;
			static TArray<FloatModifierType*> LastModifiers;

			for (const AllocatedModifierType& AllocatedModifier : AllocatedModifiers)
			{
				ModifierType* Modifier									   = AllocatedModifier.Get();
				const ICsGetSpawnerModifierType* GetSpawnerModifierType = GetInterfaceChecked<ICsGetSpawnerModifierType>(Context, Modifier);
				const FECsSpawnerModifier& SpawnerModifierType		   = GetSpawnerModifierType->GetSpawnerModifierType();

				if (SpawnerModifierType == Type)
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

		#undef AllocatedModifierType
		#undef ModifierType
		#undef LogLevel
	}
}