// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Interface
#include "Modifier/CsModifier.h"
// Types
#include "Types/CsTypes_Macro.h"

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
	struct CSCORE_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
	{
	public:

	#define IntModifierType NCsModifier::NInt::IInt

		static int32 ModifyIntChecked(const FString& Context, const IntModifierType* Modifier, const int32& Value);

		static int32 ModifyIntChecked(const FString& Context, const TArray<IntModifierType*> Modifiers, const int32& Value);

	#undef IntModifierType

	#define IntRangeModifierType NCsModifier::NInt::NRange::IRange

		static int32 ModifyIntMinChecked(const FString& Context, const IntRangeModifierType* Modifier, const int32& Value);

		static int32 ModifyIntMinChecked(const FString& Context, const TArray<IntRangeModifierType*> Modifiers, const int32& Value);

		static int32 ModifyIntMaxChecked(const FString& Context, const IntRangeModifierType* Modifier, const int32& Value);

		static int32 ModifyIntMaxChecked(const FString& Context, const TArray<IntRangeModifierType*> Modifiers, const int32& Value);

	#undef IntRangeModifierType

	#define FloatModifierType NCsModifier::NFloat::IFloat

		static float ModifyFloatChecked(const FString& Context, const FloatModifierType* Modifier, const float& Value);

		static float ModifyFloatChecked(const FString& Context, const TArray<FloatModifierType*> Modifiers, const float& Value);

	#undef FloatModifierType

	#define FloatRangeModifierType NCsModifier::NFloat::NRange::IRange

		static float ModifyFloatMinChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value);

		static float ModifyFloatMinChecked(const FString& Context, const TArray<FloatRangeModifierType*> Modifiers, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const FloatRangeModifierType* Modifier, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const TArray<FloatRangeModifierType*> Modifiers, const float& Value);

	#undef FloatRangeModifierType
	};

#undef ModifierType
}