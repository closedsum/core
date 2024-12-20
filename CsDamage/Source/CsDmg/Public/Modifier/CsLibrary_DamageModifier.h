// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Damage
#include "Modifier/CsDamageModifier.h"
#include "Modifier/CsAllocated_DamageModifier.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
// NCsDamage::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FResource)

// NCsModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_1(NCsModifier, IModifier)

namespace NCsDamage
{
	namespace NModifier
	{
	#define ModifierType NCsDamage::NModifier::IModifier

	/**
	* Library for interface: ModifierType (NCsDamage::NModifier::IModifier)
	*/
	struct CSDMG_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
	{
	#define DataType NCsDamage::NData::IData
	#define ValueType NCsDamage::NValue::IValue
	#define RangeType NCsDamage::NRange::IRange
	#define ModifierResourceType NCsDamage::NModifier::FResource
	#define AllocatedModifierType NCsDamage::NModifier::FAllocated
	#define CsModifierType NCsModifier::IModifier

	public:

		static const FECsDamageModifier& GetTypeChecked(const FString& Context, const ModifierType* Modifier);

	// Copy
	#pragma region
	public:

		/**
		* Copy the values from From to To with checks.
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		* return			Whether the copy was performed successfully.
		*/
		static bool CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To);

		/**
		* Copy the values from From to To with checks.
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		*/
		static void CopyChecked(const FString& Context, const TArray<ModifierType*>& From, TArray<ModifierType*>& To);

		/**
		* Copy the values from From to To with checks.
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		*/
		static void CopyChecked(const FString& Context, const TArray<AllocatedModifierType>& From, TArray<ModifierResourceType*>& To);

		/**
		* Copy the values from From to To with checks.
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		*/
		static void CopyChecked(const FString& Context, const TArray<AllocatedModifierType>& From, TArray<ModifierType*>& To);

		/**
		* Copy the values from From to To with checks.
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		*/
		static void CopyChecked(const FString& Context, const TArray<CsModifierType*>& From, TArray<ModifierType*>& To);

	#pragma endregion Copy

	// Add
	#pragma region
	public:

		static void AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& From, TArray<AllocatedModifierType>& To);

		static void AddChecked(const FString& Context, const TArray<ModifierType*>& From, TArray<CsModifierType*>& To);

	#pragma endregion Add

	// Modify
	#pragma region
	public:

		/**
		*
		*
		* @param Context	The calling context.
		* @param Modifier
		* @param Data
		* @param Type
		* @param Value
		*/
		static void ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, const FECsDamageData& Type, ValueType* Value);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Modifier
		* @param Data
		* @param Type
		* @param Range
		* return			Whether the Modify was "attempted" (a Modify method was called) successfully.
		*/
		static bool ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, const FECsDamageData& Type, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value);

		static void ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value, uint32& OutMask);

		static void ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value);

		static void ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value);

		static void ModifyChecked_Size64(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value);

		static void ModifyChecked_Size64(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, const FECsDamageData& Type, ValueType* Value, uint32& OutMask);

	#pragma endregion Modify

	// Range
	#pragma region
	public:

		static float GetMaxRangeChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const RangeType* Range);

		static float GetMaxRangeChecked_Size64(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const RangeType* Range);

	#pragma endregion Range

	#undef DataType
	#undef ValueType
	#undef RangeType
	#undef ModifierResourceType
	#undef AllocatedModifierType
	#undef CsModifierType
	};

	#undef ModifierType
	}
}

using CsDamageModifierLibrary = NCsDamage::NModifier::FLibrary;
using CsDmgModifierLibrary = NCsDamage::NModifier::FLibrary;