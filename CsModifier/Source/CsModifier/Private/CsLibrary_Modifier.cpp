// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "CsLibrary_Modifier.h"

// Types
#include "CsTypes_Modifier.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Modifier
#include "CsModifier_Int.h"
#include "CsModifier_Int_Range.h"
#include "CsModifier_Float.h"
#include "CsModifier_Float_Range.h"

namespace NCsModifier
{
	#define ApplicationType NCsModifier::NValue::NNumeric::EApplication

	void FLibrary::CopyChecked(const FString& Context, const TArray<CsModifierType*>& From, TArray<CsModifierType*>& To)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(From, CsModifierType)

		To.Reset(FMath::Max(To.Max(), From.Num()));

		for (CsModifierType* Modifier : From)
		{
			To.Add(Modifier);
		}
	}

	// Int
	#pragma region

	int32 FLibrary::ModifyIntChecked(const FString& Context, const CsIntModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)
		return Modifier->Modify(Value);
	}

	int32 FLibrary::ModifyIntChecked(const FString& Context, const TArray<CsIntModifierType*>& Modifiers, const int32& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsIntModifierType)

		int32 Result = Value;

		// NOTE: For now ignore order

		for (const CsIntModifierType* Modifier : Modifiers)
		{
			Result = Modifier->Modify(Result);
		}
		return Result;
	}

	#pragma endregion Int

	// Int Range
	#pragma region

	int32 FLibrary::ModifyIntMinChecked(const FString& Context, const CsIntRangeModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)
		return Modifier->ModifyMin(Value);
	}

	int32 FLibrary::ModifyIntMinChecked(const FString& Context, const TArray<CsIntRangeModifierType*>& Modifiers, const int32& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsIntRangeModifierType)

		int32 Result = Value;

		// NOTE: For now ignore order

		for (const CsIntRangeModifierType* Modifier : Modifiers)
		{
			Result = Modifier->ModifyMin(Result);
		}
		return Result;
	}

	int32 FLibrary::ModifyIntMaxChecked(const FString& Context, const CsIntRangeModifierType* Modifier, const int32& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)
		return Modifier->ModifyMax(Value);
	}

	int32 FLibrary::ModifyIntMaxChecked(const FString& Context, const TArray<CsIntRangeModifierType*>& Modifiers, const int32& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsIntRangeModifierType)

		int32 Result = Value;

		// NOTE: For now ignore order

		for (const CsIntRangeModifierType* Modifier : Modifiers)
		{
			Result = Modifier->ModifyMax(Result);
		}
		return Result;
	}

	#pragma endregion Int Rnage

	// Float
	#pragma region

	float FLibrary::ModifyFloatChecked(const FString& Context, const CsFloatModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

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

	float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<CsFloatModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatModifierType)

		float Result = Value;

		// TODO: FUTURE: Use a tiny / small array on the stack
		static TArray<CsFloatModifierType*> FirstModifiers;
		static TArray<CsFloatModifierType*> OtherModifiers;
		static TArray<CsFloatModifierType*> LastModifiers;

		for (CsFloatModifierType* Modifier : Modifiers)
		{
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

	float FLibrary::ModifyFloatChecked(const FString& Context, const TArray<CsFloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		//CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;

		TArray<CsFloatModifierType*, TFixedAllocator<64>> FirstModifiers;
		TArray<CsFloatModifierType*, TFixedAllocator<64>> OtherModifiers;
		TArray<CsFloatModifierType*, TFixedAllocator<64>> LastModifiers;

		for (CsFloatModifierType* Modifier : Modifiers)
		{
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
		for (const CsFloatModifierType* FloatModifier : OtherModifiers)
		{
			Result = FloatModifier->Modify(Value);
		}
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatPercentChecked(Context, LastModifiers, Result);
		return Result;
	}

	float FLibrary::ModifyFloatAndEmptyChecked(const FString& Context, TArray<CsFloatModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatModifierType)

		float Result = Value;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const CsFloatModifierType* FloatModifier = Modifiers[I];

			Result = FloatModifier->Modify(Value);

			Modifiers.RemoveAt(I, 1, false);
		}
		return Result;
	}

	float FLibrary::ModifyFloatPercentChecked(const FString& Context, const TArray<CsFloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		// TODO:
		// CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, FloatModifierType)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (const CsFloatModifierType* Modifier : Modifiers)
		{
			Percent = Modifier->Modify(Percent);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	float FLibrary::ModifyFloatPercentAndEmptyChecked(const FString& Context, TArray<CsFloatModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatModifierType)

		float Result  = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const CsFloatModifierType* Modifier = Modifiers[I];

			Percent = Modifier->Modify(Percent);

			Modifiers.RemoveAt(I, 1, false);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	#pragma endregion Float

	// Float Range
	#pragma region

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const CsFloatRangeModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

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

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType)

		float Result = Value;

		// TODO: FUTURE: Use a tiny / small array on the stack
		static TArray<CsFloatRangeModifierType*> FirstModifiers;
		static TArray<CsFloatRangeModifierType*> OtherModifiers;
		static TArray<CsFloatRangeModifierType*> LastModifiers;

		for (CsFloatRangeModifierType* Modifier : Modifiers)
		{
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
				const CsFloatRangeModifierType* FloatModifier = FirstModifiers[I];
					
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
				const CsFloatRangeModifierType* FloatModifier = OtherModifiers[I];

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
				const CsFloatRangeModifierType* FloatModifier = LastModifiers[I];

				Percent = FloatModifier->ModifyMin(Percent);

				LastModifiers.RemoveAt(I, 1, false);
			}
			Percent = FMath::Max(0.0f, Percent);
			Result *= Percent;
		}
		return Result;
	}

	float FLibrary::ModifyFloatMinChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_FIXED_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType, 64)

		float Result = Value;

		TArray<CsFloatRangeModifierType*, TFixedAllocator<64>> FirstModifiers;
		TArray<CsFloatRangeModifierType*, TFixedAllocator<64>> OtherModifiers;
		TArray<CsFloatRangeModifierType*, TFixedAllocator<64>> LastModifiers;

		for (CsFloatRangeModifierType* Modifier : Modifiers)
		{
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
		for (const CsFloatRangeModifierType* FloatModifier : OtherModifiers)
		{
			Result = FloatModifier->ModifyMin(Result);
		}
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatMinPercentChecked(Context, LastModifiers, Result);
		return Result;
	}

	float FLibrary::ModifyFloatMinAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType)

		float Result = Value;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const CsFloatRangeModifierType* FloatModifier = Modifiers[I];

			Result = FloatModifier->ModifyMin(Value);

			Modifiers.RemoveAt(I, 1, false);
		}
		return Result;
	}

	float FLibrary::ModifyFloatMinPercentChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_FIXED_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType, 64)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (const CsFloatRangeModifierType* Modifier : Modifiers)
		{
			Percent = Modifier->ModifyMin(Percent);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	float FLibrary::ModifyFloatMinPercentAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const CsFloatRangeModifierType* FloatModifier = Modifiers[I];

			Percent = FloatModifier->ModifyMin(Percent);

			Modifiers.RemoveAt(I, 1, false);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const CsFloatRangeModifierType* Modifier, const float& Value)
	{
		CS_IS_PTR_NULL_CHECKED(Modifier)

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

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType)

		float Result = Value;

		// TODO: FUTURE: Use a tiny / small array on the stack
		static TArray<CsFloatRangeModifierType*> FirstModifiers;
		static TArray<CsFloatRangeModifierType*> OtherModifiers;
		static TArray<CsFloatRangeModifierType*> LastModifiers;

		for (CsFloatRangeModifierType* Modifier : Modifiers)
		{
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
				const CsFloatRangeModifierType* FloatModifier = FirstModifiers[I];
					
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
				const CsFloatRangeModifierType* FloatModifier = OtherModifiers[I];

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
				const CsFloatRangeModifierType* FloatModifier = LastModifiers[I];

				Percent = FloatModifier->ModifyMax(Percent);

				LastModifiers.RemoveAt(I, 1, false);
			}
			Percent = FMath::Max(0.0f, Percent);
			Result *= Percent;
		}
		return Result;
	}

	float FLibrary::ModifyFloatMaxChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_FIXED_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType, 64)

		float Result = Value;

		TArray<CsFloatRangeModifierType*, TFixedAllocator<64>> FirstModifiers;
		TArray<CsFloatRangeModifierType*, TFixedAllocator<64>> OtherModifiers;
		TArray<CsFloatRangeModifierType*, TFixedAllocator<64>> LastModifiers;

		for (CsFloatRangeModifierType* Modifier : Modifiers)
		{
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
		for (const CsFloatRangeModifierType* FloatModifier : OtherModifiers)
		{
			Result = FloatModifier->ModifyMax(Result);
		}
		// PercentAddLast || PercentSubtractLast
		Result = ModifyFloatMaxPercentChecked(Context, LastModifiers, Result);
		return Result;
	}

	float FLibrary::ModifyFloatMaxAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType)

		float Result = Value;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const CsFloatRangeModifierType* FloatModifier = Modifiers[I];

			Result = FloatModifier->ModifyMax(Value);

			Modifiers.RemoveAt(I, 1, false);
		}
		return Result;
	}

	float FLibrary::ModifyFloatMaxPercentChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_FIXED_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType, 64)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (const CsFloatRangeModifierType* Modifier : Modifiers)
		{
			Percent = Modifier->ModifyMax(Percent);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	float FLibrary::ModifyFloatMaxPercentAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value)
	{
		CS_IS_TARRAY_ANY_NULL_CHECKED(Modifiers, CsFloatRangeModifierType)

		float Result = Value;
		float Percent = 1.0f;

		const int32 Count = Modifiers.Num();

		for (int32 I = Count - 1; I >= 0; --I)
		{
			const CsFloatRangeModifierType* FloatModifier = Modifiers[I];

			Percent = FloatModifier->ModifyMax(Percent);

			Modifiers.RemoveAt(I, 1, false);
		}
		Percent = FMath::Max(0.0f, Percent);
		Result *= Percent;
		return Result;
	}

	#pragma endregion Float Rnage

	#undef ApplicationType
}