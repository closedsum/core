// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Damage
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Managers/Damage/Modifier/CsAllocated_DamageModifier.h"

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)
// NCsDamage::NModifier::FResource
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, FResource)

namespace NCsDamage
{
	namespace NModifier
	{
	#define ModifierType NCsDamage::NModifier::IModifier

	/**
	* Library for interface: ModifierType (NCsDamage::NModifier::IModifier)
	*/
	struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<ModifierType>
	{
	#define DataType NCsDamage::NData::IData
	#define ValueType NCsDamage::NValue::IValue
	#define RangeType NCsDamage::NRange::IRange
	

	public:

		static const FECsDamageModifier& GetTypeChecked(const FString& Context, const ModifierType* Modifier);

		/**
		* Copy the values from From to To with checks.
		* Currently supports To types of:
		*  
		*
		* @param Context	The calling context.
		* @param From		What to copy.
		* @param To			What to copy to.
		* return			Whether the copy was performed successfully.
		*/
		static bool CopyChecked(const FString& Context, const ModifierType* From, ModifierType* To);

		/**
		*
		*
		* @param Context	The calling context.
		* @param Modifier
		* @param Data
		* @param Value
		* return			Whether the Modify was "attempted" (a Modify method was called) successfully.
		*/
		static bool ModifyChecked(const FString& Context, const ModifierType* Modifier, const DataType* Data, ValueType* Value);

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

	#define ModifierResourceType NCsDamage::NModifier::FResource

		static void ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<ModifierResourceType*>& Modifiers, const DataType* Data, ValueType* Value);

	#undef ModifierResourceType

	#define AllocatedModifierType NCsDamage::NModifier::FAllocated

		static void ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value, RangeType* Range);

		static void ModifyChecked(const FString& Context, const TArray<AllocatedModifierType>& Modifiers, const DataType* Data, ValueType* Value);

	#undef AllocatedModifierType

		struct CSCORE_API FModify
		{
			enum class ECheck : int32
			{
				// Check if Modifier is NULL
				Modifier = 1 << 0,
				// Check if Modifier implements the appropriate interface for Modify
				Modifier_ImplementsInterface = 1 << 1,
				// Check if Modifiers is Empty
				Modifiers_Empty = 1 << 2,
				// Check if ANY element in Modifiers is NULL
				Modifiers_AnyNull = 1 << 3,
				// Check at LEAST one element in Modifiers implements the appropriate interface for Modify
				Modifiers_AnyImplmentsInterface = 1 << 4,
				// Check ALL the elements in Modifiers implement the appropriate interface for Modify
				Modifiers_AllImplementInterface = 1 << 5,
				// check if Value is NULL
				Value = 1 << 6
			};

			// const FName NCsDamage::NModifier::IModifier::Name = FName("NCsDamage::NModifier::IModifier");

			static const int32 SafeModifierImplementsInterface;
			static const int32 SafeModifiersImplementsInterface;
		};

		static void ConditionalModifyChecked(const FString& Context, const ModifierType* Modifier, ValueType* Value, const int32& CheckMask = FModify::SafeModifierImplementsInterface);

		static void ConditionalModifyChecked(const FString& Context, const TArray<ModifierType*>& Modifiers, ValueType* Value, const int32& CheckMask = FModify::SafeModifiersImplementsInterface);

	#undef DataType
	#undef ValueType
	#undef RangeType
	};

	#undef ModifierType
	}
}