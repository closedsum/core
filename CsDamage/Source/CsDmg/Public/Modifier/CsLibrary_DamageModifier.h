// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
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
	#define BaseModifierType NCsModifier::IModifier

	public:

		static const FECsDamageModifier& GetTypeChecked(const FString& Context, const ModifierType* Modifier);

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
		static void CopyChecked(const FString& Context, const TArray<BaseModifierType*>& From, TArray<ModifierType*>& To);

		static void AddChecked(const FString& Context, UObject* WorldContext, const TArray<ModifierType*>& Modifiers, TArray<AllocatedModifierType>& AllocatedModifiers);

		static void AddChecked(const FString& Context, const TArray<ModifierType*>& From, TArray<BaseModifierType*>& To);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Modifier
		* @param Data
		* @param Value
		*/
		static void ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Modifier
		* @param Data
		* @param Range
		* return			Whether the Modify was "attempted" (a Modify method was called) successfully.
		*/
		static bool ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value);

		static void ModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, ValueType* Value);

		static void ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value);

	#undef DataType
	#undef ValueType
	#undef RangeType
	#undef ModifierResourceType
	#undef AllocatedModifierType
	#undef BaseModifierType
	};

	#undef ModifierType
	}
}