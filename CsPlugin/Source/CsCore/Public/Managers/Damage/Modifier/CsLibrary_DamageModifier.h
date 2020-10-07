// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Modifier/CsDamageModifier.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

// NCsDamage::NValue::IValue
namespace NCsDamage {
	namespace NValue {
		struct IValue; } }

// NCsDamage::NRange::IRange
namespace NCsDamage {
	namespace NRange {
		struct IRange; } }

// NCsDamage::NData::IData
namespace NCsDamage {
	namespace NData {
		struct IData; } }

#define ModifierType NCsDamage::NModifier::IModifier
#define ValueType NCsDamage::NValue::IValue
#define RangeType NCsDamage::NRange::IRange
#define DataType NCsDamage::NData::IData

/**
* Library for interface: ICsDamageModifier
*/
struct CSCORE_API FCsLibrary_DamageModifier : public TCsLibrary_InterfaceMap<ModifierType>
{
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
};

#undef ModifierType
#undef ValueType
#undef RangeType
#undef DataType