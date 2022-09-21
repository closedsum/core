// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsLibrary_Modifier.h"

// Types
#include "Modifier/CsTypes_Modifier.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Modifier
#include "Modifier/CsModifier_Int.h"
#include "Modifier/CsModifier_Int_Range.h"
#include "Modifier/CsModifier_Float.h"
#include "Modifier/CsModifier_Float_Range.h"

namespace NCsModifier
{
	#define ModifierType NCsModifier::IModifier

	#define IntModifierType NCsModifier::NInt::IInt

	int32 FLibrary::ModifyIntChecked(const FString& Context, const IntModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		int32 Result = Modifier->Modify(Result);

		return Result;
	}

	int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<IntModifierType*> Modifiers, const int32& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, IntModifierType)

		int32 Result = Value;

		// NOTE: For now ignore order

		for (const IntModifierType* Modifier : Modifiers)
		{
			Result = Modifier->Modify(Result);
		}
		return Result;
	}

	#undef IntModifierType

	#define IntRangeModifierType NCsModifier::NInt::NRange::IRange

	int32 FLibrary::ModifyIntMinChecked(const FString& Context, const IntRangeModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		int32 Result = Modifier->ModifyMin(Result);

		return Result;
	}

	int32 FLibrary::ModifyIntMinChecked(const FString& Context, const TArray<IntRangeModifierType*> Modifiers, const int32& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, IntRangeModifierType)

		int32 Result = Value;

		// NOTE: For now ignore order

		for (const IntRangeModifierType* Modifier : Modifiers)
		{
			Result = Modifier->ModifyMin(Result);
		}
		return Result;
	}

	int32 FLibrary::ModifyIntMaxChecked(const FString& Context, const IntRangeModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		int32 Result = Modifier->ModifyMax(Result);

		return Result;
	}

	int32 FLibrary::ModifyIntMaxChecked(const FString& Context, const TArray<IntRangeModifierType*> Modifiers, const int32& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, IntRangeModifierType)

		int32 Result = Value;

		// NOTE: For now ignore order

		for (const IntRangeModifierType* Modifier : Modifiers)
		{
			Result = Modifier->ModifyMax(Result);
		}
		return Result;
	}

	#undef IntRangeModifierType

	#define FloatModifierType NCsModifier::NFloat::IFloat

	float FLibrary::ModifyFloatChecked(const FString& Context, const FloatModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

		const ApplicationType& Application = Modifier->GetApplication();

		float Result = Value;

		// PercentAddFirst
		if (Application == ApplicationType::PercentAddFirst)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->Modify(Percent);
			Result		 *= Percent;
		}
		// PercentAddLast
		else
		if (Application == ApplicationType::PercentAddLast)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->Modify(Percent);
			Result		 *= Percent;
		}
		// "The Rest"
		else
		{
			Result = Modifier->Modify(Result);
		}
		return Result;
	}

	float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<FloatModifierType*> Modifiers, const float& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;

		// TODO: FUTURE: Use a tiny / small array on the stack
		static TArray<FloatModifierType*> FirstModifiers;
		static TArray<FloatModifierType*> OtherModifiers;
		static TArray<FloatModifierType*> LastModifiers;

		for (FloatModifierType* Modifier : Modifiers)
		{
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			const ApplicationType& Application = Modifier->GetApplication();

			// PercentAddFirst
			if (Application == ApplicationType::PercentAddFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast
			else
			if (Application == ApplicationType::PercentAddLast)
			{
				LastModifiers.Add(Modifier);
			}
			// "The Rest"
			else
			{
				OtherModifiers.Add(Modifier);
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
			const int32 Count = OtherModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatModifierType* FloatModifier = OtherModifiers[I];

				Result = FloatModifier->Modify(Result);

				OtherModifiers.RemoveAt(I, 1, false);
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

	#undef FloatModifierType

	#define FloatRangeModifierType NCsModifier::NFloat::NRange::IRange

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

		const ApplicationType& Application = Modifier->GetMinApplication();

		float Result = Value;

		// PercentAddFirst
		if (Application == ApplicationType::PercentAddFirst)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMin(Percent);
			Result		 *= Percent;
		}
		// PercentAddLast
		else
		if (Application == ApplicationType::PercentAddLast)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMin(Percent);
			Result		 *= Percent;
		}
		// "The Rest"
		else
		{
			Result = Modifier->ModifyMin(Result);
		}
		return Result;
	}

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const TArray<FloatRangeModifierType*> Modifiers, const float& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatRangeModifierType)

		float Result = Value;

		// TODO: FUTURE: Use a tiny / small array on the stack
		static TArray<FloatRangeModifierType*> FirstModifiers;
		static TArray<FloatRangeModifierType*> OtherModifiers;
		static TArray<FloatRangeModifierType*> LastModifiers;

		for (FloatRangeModifierType* Modifier : Modifiers)
		{
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			const ApplicationType& Application = Modifier->GetMinApplication();

			// PercentAddFirst
			if (Application == ApplicationType::PercentAddFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast
			else
			if (Application == ApplicationType::PercentAddLast)
			{
				LastModifiers.Add(Modifier);
			}
			// "The Rest"
			else
			{
				OtherModifiers.Add(Modifier);
			}
		}

		// NOTE: For now ignore order

		// PercentAddFirst
		{
			float Percent = 1.0f;

			const int32 Count = FirstModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = FirstModifiers[I];
					
				Percent = FloatModifier->ModifyMin(Percent);
					
				FirstModifiers.RemoveAt(I, 1, false);
			}
			Result *= Percent;
		}
		// "The Rest"
		{
			const int32 Count = OtherModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = OtherModifiers[I];

				Result = FloatModifier->ModifyMin(Result);

				OtherModifiers.RemoveAt(I, 1, false);
			}
		}
		// PercentAddLast
		{
			float Percent = 1.0f;

			const int32 Count = LastModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = LastModifiers[I];

				Percent = FloatModifier->ModifyMin(Percent);

				LastModifiers.RemoveAt(I, 1, false);
			}
			Result *= Percent;
		}
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

		const ApplicationType& Application = Modifier->GetMaxApplication();

		float Result = Value;

		// PercentAddFirst
		if (Application == ApplicationType::PercentAddFirst)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMax(Percent);
			Result		 *= Percent;
		}
		// PercentAddLast
		else
		if (Application == ApplicationType::PercentAddLast)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMax(Percent);
			Result		 *= Percent;
		}
		// "The Rest"
		else
		{
			Result = Modifier->ModifyMax(Result);
		}
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const TArray<FloatRangeModifierType*> Modifiers, const float& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatRangeModifierType)

		float Result = Value;

		// TODO: FUTURE: Use a tiny / small array on the stack
		static TArray<FloatRangeModifierType*> FirstModifiers;
		static TArray<FloatRangeModifierType*> OtherModifiers;
		static TArray<FloatRangeModifierType*> LastModifiers;

		for (FloatRangeModifierType* Modifier : Modifiers)
		{
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			const ApplicationType& Application = Modifier->GetMaxApplication();

			// PercentAddFirst
			if (Application == ApplicationType::PercentAddFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast
			else
			if (Application == ApplicationType::PercentAddLast)
			{
				LastModifiers.Add(Modifier);
			}
			// "The Rest"
			else
			{
				OtherModifiers.Add(Modifier);
			}
		}

		// NOTE: For now ignore order

		// PercentAddFirst
		{
			float Percent = 1.0f;

			const int32 Count = FirstModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = FirstModifiers[I];
					
				Percent = FloatModifier->ModifyMax(Percent);
					
				FirstModifiers.RemoveAt(I, 1, false);
			}
			Result *= Percent;
		}
		// "The Rest"
		{
			const int32 Count = OtherModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = OtherModifiers[I];

				Result = FloatModifier->ModifyMax(Result);

				OtherModifiers.RemoveAt(I, 1, false);
			}
		}
		// PercentAddLast
		{
			float Percent = 1.0f;

			const int32 Count = LastModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = LastModifiers[I];

				Percent = FloatModifier->ModifyMax(Percent);

				LastModifiers.RemoveAt(I, 1, false);
			}
			Result *= Percent;
		}
		return Result;
	}

	#undef FloatRangeModifierType

	#undef ModifierType
}