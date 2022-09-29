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

	void FLibrary::CopyChecked(const FString& Context, const TArray<ModifierType*>& From, TArray<ModifierType*>& To)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(From, ModifierType)

		To.Reset(FMath::Max(To.Max(), From.Num()));

		for (ModifierType* Modifier : From)
		{
			To.Add(Modifier);
		}
	}

	#define IntModifierType NCsModifier::NInt::IInt

	int32 FLibrary::ModifyIntChecked(const FString& Context, const IntModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		int32 Result = Modifier->Modify(Result);

		return Result;
	}

	int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<IntModifierType*>& Modifiers, const int32& Value)
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

	int32 FLibrary::ModifyIntMinChecked(const FString& Context, const TArray<IntRangeModifierType*>& Modifiers, const int32& Value)
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

	int32 FLibrary::ModifyIntMaxChecked(const FString& Context, const TArray<IntRangeModifierType*>& Modifiers, const int32& Value)
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

		// PercentAddFirst || PercentSubtractFirst
		if (Application == ApplicationType::PercentAddFirst ||
			Application == ApplicationType::PercentSubtractFirst)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->Modify(Percent);
			Percent		  = FMath::Max(0.0f, Percent);
			Result		 *= Percent;
		}
		// PercentAddLast || PercentSubtractLast
		else
		if (Application == ApplicationType::PercentAddLast ||
			Application == ApplicationType::PercentSubtractLast)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->Modify(Percent);
			Percent		  = FMath::Max(0.0f, Percent);
			Result		 *= Percent;
		}
		// "The Rest"
		else
		{
			Result = Modifier->Modify(Result);
		}
		return Result;
	}

	float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<FloatModifierType*>& Modifiers, const float& Value)
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

			// PercentAddFirst || PercentSubtractFirst
			if (Application == ApplicationType::PercentAddFirst ||
				Application == ApplicationType::PercentSubtractFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast || PercentSubtractLast
			else
			if (Application == ApplicationType::PercentAddLast ||
				Application == ApplicationType::PercentSubtractLast)
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

		// PercentAddFirst || PercentSubtractFirst
		Result = ModifyFloatPercentAndEmptyChecked(Context, FirstModifiers, Result);
		// "The Rest"
		Result = ModifyFloatAndEmptyChecked(Context, OtherModifiers, Result);
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatPercentAndEmptyChecked(Context, LastModifiers, Result);

		return Result;
	}

	float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<FloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		//CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;

		TArray<FloatModifierType*, TFixedAllocator<64>> FirstModifiers;
		TArray<FloatModifierType*, TFixedAllocator<64>> OtherModifiers;
		TArray<FloatModifierType*, TFixedAllocator<64>> LastModifiers;

		for (FloatModifierType* Modifier : Modifiers)
		{
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			const ApplicationType& Application = Modifier->GetApplication();

			// PercentAddFirst || PercentSubtractFirst
			if (Application == ApplicationType::PercentAddFirst ||
				Application == ApplicationType::PercentSubtractFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast || PercentSubtractLast
			else
			if (Application == ApplicationType::PercentAddLast ||
				Application == ApplicationType::PercentSubtractLast)
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

		// PercentAddFirst || PercentSubtractFirst
		Result = ModifyFloatPercentChecked(Context, FirstModifiers, Result);
		// "The Rest"
		for (const FloatModifierType* FloatModifier : OtherModifiers)
		{
			Result = FloatModifier->Modify(Value);
		}
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatPercentChecked(Context, LastModifiers, Result);
		return Result;
	}

	float FLibrary::ModifyFloatAndEmptyChecked(const FString& Context, TArray<FloatModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const FloatModifierType* FloatModifier = Modifiers[I];

			Result = FloatModifier->Modify(Value);

			Modifiers.RemoveAt(I, 1, false);
		}
		return Result;
	}

	float FLibrary::ModifyFloatPercentChecked(const FString& Context, const TArray<FloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		// CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (const FloatModifierType* Modifier : Modifiers)
		{
			Percent = Modifier->Modify(Percent);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	float FLibrary::ModifyFloatPercentAndEmptyChecked(const FString& Context, TArray<FloatModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result  = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const FloatModifierType* Modifier = Modifiers[I];

			Percent = Modifier->Modify(Percent);

			Modifiers.RemoveAt(I, 1, false);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
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

		// PercentAddFirst || PercentSubtractFirst
		if (Application == ApplicationType::PercentAddFirst ||
			Application == ApplicationType::PercentSubtractFirst)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMin(Percent);
			Percent		  = FMath::Max(0.0f, Percent);
			Result		 *= Percent;
		}
		// PercentAddLast || PercentSubtractLast
		else
		if (Application == ApplicationType::PercentAddLast ||
			Application == ApplicationType::PercentSubtractLast)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMin(Percent);
			Percent		  = FMath::Max(0.0f, Percent);
			Result		 *= Percent;
		}
		// "The Rest"
		else
		{
			Result = Modifier->ModifyMin(Result);
		}
		return Result;
	}

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const TArray<FloatRangeModifierType*>& Modifiers, const float& Value)
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

			// PercentAddFirst || PercentSubtractFirst
			if (Application == ApplicationType::PercentAddFirst ||
				Application == ApplicationType::PercentSubtractFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast || PercentSubtractLast
			else
			if (Application == ApplicationType::PercentAddLast ||
				Application == ApplicationType::PercentSubtractLast)
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

		// PercentAddFirst || PercentSubtractFirst
		{
			float Percent = 1.0f;

			const int32 Count = FirstModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = FirstModifiers[I];
					
				Percent = FloatModifier->ModifyMin(Percent);
					
				FirstModifiers.RemoveAt(I, 1, false);
			}
			Percent = FMath::Max(0.0f, Percent);
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
		// PercentAddLast || PercentSubtractLast
		{
			float Percent = 1.0f;

			const int32 Count = LastModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = LastModifiers[I];

				Percent = FloatModifier->ModifyMin(Percent);

				LastModifiers.RemoveAt(I, 1, false);
			}
			Percent = FMath::Max(0.0f, Percent);
			Result *= Percent;
		}
		return Result;
	}

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		//CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatRangeModifierType)

		float Result = Value;

		TArray<FloatRangeModifierType*, TFixedAllocator<64>> FirstModifiers;
		TArray<FloatRangeModifierType*, TFixedAllocator<64>> OtherModifiers;
		TArray<FloatRangeModifierType*, TFixedAllocator<64>> LastModifiers;

		for (FloatRangeModifierType* Modifier : Modifiers)
		{
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			const ApplicationType& Application = Modifier->GetMinApplication();

			// PercentAddFirst || PercentSubtractFirst
			if (Application == ApplicationType::PercentAddFirst ||
				Application == ApplicationType::PercentSubtractFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast || PercentSubtractLast
			else
			if (Application == ApplicationType::PercentAddLast ||
				Application == ApplicationType::PercentSubtractLast)
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

		// PercentAddFirst || PercentSubtractFirst
		Result = ModifyFloatMinPercentChecked(Context, FirstModifiers, Result);
		// "The Rest"
		for (const FloatRangeModifierType* FloatModifier : OtherModifiers)
		{
			Result = FloatModifier->ModifyMin(Result);
		}
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatMinPercentChecked(Context, LastModifiers, Result);
		return Result;
	}

	float FLibrary::ModifyFloatMinPercentChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		// CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (const FloatRangeModifierType* Modifier : Modifiers)
		{
			Percent = Modifier->ModifyMin(Percent);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

		typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

		const ApplicationType& Application = Modifier->GetMaxApplication();

		float Result = Value;

		// PercentAddFirst || PercentSubtractFirst
		if (Application == ApplicationType::PercentAddFirst ||
			Application == ApplicationType::PercentSubtractFirst)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMax(Percent);
			Percent		  = FMath::Max(0.0f, Percent);
			Result		 *= Percent;
		}
		// PercentAddLast || PercentSubtractLast
		else
		if (Application == ApplicationType::PercentAddLast ||
			Application == ApplicationType::PercentSubtractLast)
		{
			float Percent = 1.0f;
			Percent		  = Modifier->ModifyMax(Percent);
			Percent		  = FMath::Max(0.0f, Percent);
			Result		 *= Percent;
		}
		// "The Rest"
		else
		{
			Result = Modifier->ModifyMax(Result);
		}
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const TArray<FloatRangeModifierType*>& Modifiers, const float& Value)
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

			// PercentAddFirst || PercentSubtractFirst
			if (Application == ApplicationType::PercentAddFirst ||
				Application == ApplicationType::PercentSubtractFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast || PercentSubtractLast
			else
			if (Application == ApplicationType::PercentAddLast ||
				Application == ApplicationType::PercentSubtractLast)
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

		// PercentAddFirst || PercentSubtractFirst
		{
			float Percent = 1.0f;

			const int32 Count = FirstModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = FirstModifiers[I];
					
				Percent = FloatModifier->ModifyMax(Percent);
					
				FirstModifiers.RemoveAt(I, 1, false);
			}
			Percent = FMath::Max(0.0f, Percent);
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
		// PercentAddLast || PercentSubtractLast
		{
			float Percent = 1.0f;

			const int32 Count = LastModifiers.Num();

			for (int32 I = Count - 1; I >= 0; --I)
			{
				const FloatRangeModifierType* FloatModifier = LastModifiers[I];

				Percent = FloatModifier->ModifyMax(Percent);

				LastModifiers.RemoveAt(I, 1, false);
			}
			Percent = FMath::Max(0.0f, Percent);
			Result *= Percent;
		}
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		//CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatRangeModifierType)

		float Result = Value;

		TArray<FloatRangeModifierType*, TFixedAllocator<64>> FirstModifiers;
		TArray<FloatRangeModifierType*, TFixedAllocator<64>> OtherModifiers;
		TArray<FloatRangeModifierType*, TFixedAllocator<64>> LastModifiers;

		for (FloatRangeModifierType* Modifier : Modifiers)
		{
			typedef NCsModifier::NValue::NNumeric::EApplication ApplicationType;

			const ApplicationType& Application = Modifier->GetMaxApplication();

			// PercentAddFirst || PercentSubtractFirst
			if (Application == ApplicationType::PercentAddFirst ||
				Application == ApplicationType::PercentSubtractFirst)
			{
				FirstModifiers.Add(Modifier);
			}
			// PercentAddLast || PercentSubtractLast
			else
			if (Application == ApplicationType::PercentAddLast ||
				Application == ApplicationType::PercentSubtractLast)
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

		// PercentAddFirst || PercentSubtractFirst
		Result = ModifyFloatMaxPercentChecked(Context, FirstModifiers, Result);
		// "The Rest"
		for (const FloatRangeModifierType* FloatModifier : OtherModifiers)
		{
			Result = FloatModifier->ModifyMax(Result);
		}
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatMaxPercentChecked(Context, LastModifiers, Result);
		return Result;
	}

	float FLibrary::ModifyFloatMaxPercentChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		// CS_IS_ARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (const FloatRangeModifierType* Modifier : Modifiers)
		{
			Percent = Modifier->ModifyMax(Percent);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	#undef FloatRangeModifierType

	#undef ModifierType
}