// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
#pragma once

// NCsDamage::NValue::IValue
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NValue, IValue)
// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)
// NCsDamage::NData::IData
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NData, IData)

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

	#undef DataType
	#undef ValueType
	#undef RangeType
	};

	#undef ModifierType
	}
}