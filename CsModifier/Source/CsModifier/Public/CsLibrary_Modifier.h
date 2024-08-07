// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Interface
#include "ICsModifier.h"
// Types
#include "CsMacro_Namespace.h"

// NCsModifier::NInt::IInt
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsModifier, NInt, IInt)
// NCsModifier::NInt::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsModifier, NInt, NRange, IRange)
// NCsModifier::NFloat::IFloat
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsModifier, NFloat, IFloat)
// NCsModifier::NFloat::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsModifier, NFloat, NRange, IRange)

namespace NCsModifier
{
#define ModifierType NCsModifier::IModifier

	/**
	* Library for interface: ModifierType (NCsModifier::IModifier)
	*/
	struct CSMODIFIER_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
	{
	public:

		static void CopyChecked(const FString& Context, const TArray<ModifierType*>& From, TArray<ModifierType*>& To);

	#define IntModifierType NCsModifier::NInt::IInt

		static int32 ModifyIntChecked(const FString& Context, const IntModifierType* Modifier, const int32& Value);

		static int32 ModifyIntChecked(const FString& Context, const TArray<IntModifierType*>& Modifiers, const int32& Value);

	#undef IntModifierType

	#define IntRangeModifierType NCsModifier::NInt::NRange::IRange

		static int32 ModifyIntMinChecked(const FString& Context, const IntRangeModifierType* Modifier, const int32& Value);

		static int32 ModifyIntMinChecked(const FString& Context, const TArray<IntRangeModifierType*>& Modifiers, const int32& Value);

		static int32 ModifyIntMaxChecked(const FString& Context, const IntRangeModifierType* Modifier, const int32& Value);

		static int32 ModifyIntMaxChecked(const FString& Context, const TArray<IntRangeModifierType*>& Modifiers, const int32& Value);

	#undef IntRangeModifierType

	#define FloatModifierType NCsModifier::NFloat::IFloat

		static float ModifyFloatChecked(const FString& Context, const FloatModifierType* Modifier, const float& Value);

		static float ModifyFloatChecked(const FString& Context, const TArray<FloatModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatChecked(const FString& Context, const TArray<FloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatAndEmptyChecked(const FString& Context, TArray<FloatModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatPercentChecked(const FString& Context, const TArray<FloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatPercentAndEmptyChecked(const FString& Context, TArray<FloatModifierType*>& Modifiers, const float& Value);

	#undef FloatModifierType

	#define FloatRangeModifierType NCsModifier::NFloat::NRange::IRange

		static float ModifyFloatMinChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value);

		static float ModifyFloatMinChecked(const FString& Context, const TArray<FloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMinChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMinAndEmptyChecked(const FString& Context, TArray<FloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMinPercentChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMinPercentAndEmptyChecked(const FString& Context, TArray<FloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const TArray<FloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMaxAndEmptyChecked(const FString& Context, TArray<FloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMaxPercentChecked(const FString& Context, const TArray<FloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMaxPercentAndEmptyChecked(const FString& Context, TArray<FloatRangeModifierType*>& Modifiers, const float& Value);

	#undef FloatRangeModifierType
	};

#undef ModifierType
}