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
	/**
	* Library for interface: CsModifierType (NCsModifier::IModifier)
	*/
	struct CSMODIFIER_API FLibrary final : public NCsInterfaceMap::TLibrary<CsModifierType>
	{
	public:

		static void CopyChecked(const FString& Context, const TArray<CsModifierType*>& From, TArray<CsModifierType*>& To);

	// Int
	#pragma region
	public:

	#define CsIntModifierType NCsModifier::NInt::IInt

		static int32 ModifyIntChecked(const FString& Context, const CsIntModifierType* Modifier, const int32& Value);

		static int32 ModifyIntChecked(const FString& Context, const TArray<CsIntModifierType*>& Modifiers, const int32& Value);

	#undef CsIntModifierType

	#pragma endregion Int

	// Int Range
	#pragma region
	public:

	#define CsIntRangeModifierType NCsModifier::NInt::NRange::IRange

		static int32 ModifyIntMinChecked(const FString& Context, const CsIntRangeModifierType* Modifier, const int32& Value);

		static int32 ModifyIntMinChecked(const FString& Context, const TArray<CsIntRangeModifierType*>& Modifiers, const int32& Value);

		static int32 ModifyIntMaxChecked(const FString& Context, const CsIntRangeModifierType* Modifier, const int32& Value);

		static int32 ModifyIntMaxChecked(const FString& Context, const TArray<CsIntRangeModifierType*>& Modifiers, const int32& Value);

	#undef CsIntRangeModifierType

	#pragma endregion Int Range

	// Float
	#pragma region
	public:

	#define CsFloatModifierType NCsModifier::NFloat::IFloat

		static float ModifyFloatChecked(const FString& Context, const CsFloatModifierType* Modifier, const float& Value);

		static float ModifyFloatChecked(const FString& Context, const TArray<CsFloatModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatChecked(const FString& Context, const TArray<CsFloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatAndEmptyChecked(const FString& Context, TArray<CsFloatModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatPercentChecked(const FString& Context, const TArray<CsFloatModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatPercentAndEmptyChecked(const FString& Context, TArray<CsFloatModifierType*>& Modifiers, const float& Value);

	#undef CsFloatModifierType

	#pragma endregion Float

	// Float Range
	#pragma region
	public:

	#define CsFloatRangeModifierType NCsModifier::NFloat::NRange::IRange

		static float ModifyFloatMinChecked(const FString& Context, const CsFloatRangeModifierType* Modifier, const float& Value);

		static float ModifyFloatMinChecked(const FString& Context, const TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMinChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMinAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMinPercentChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMinPercentAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const CsFloatRangeModifierType* Modifier, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMaxChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMaxAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value);

		static float ModifyFloatMaxPercentChecked(const FString& Context, const TArray<CsFloatRangeModifierType*, TFixedAllocator<64>>& Modifiers, const float& Value);

		static float ModifyFloatMaxPercentAndEmptyChecked(const FString& Context, TArray<CsFloatRangeModifierType*>& Modifiers, const float& Value);

	#undef CsFloatRangeModifierType

	#pragma endregion Float Range
	};
}