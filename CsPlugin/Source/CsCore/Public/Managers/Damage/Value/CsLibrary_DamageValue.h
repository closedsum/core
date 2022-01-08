// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Managers/Damage/Value/CsTypes_DamageValue.h"
// Damage
#include "Managers/Damage/Value/CsDamageValue.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
	#define ValueType NCsDamage::NValue::IValue

		/**
		* Library for interface: ValueType (NCsDamage::NValue::IValue)
		*/
		struct CSCORE_API FLibrary final : public NCsInterfaceMap::TLibrary<ValueType>
		{
		public:

			static const FECsDamageValue& GetTypeChecked(const FString& Context, const ValueType* Value);

			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsDamage::NValue::NPoint::Impl (NCsDamage::NValue::NPoint::IPoint)
			*  NCsDamage::NValue::NRange::Impl (NCsDamage::NValue::NRange::IRange)
			*
			* @param Context	The calling context.
			* @param From		What to copy.
			* @param To			What to copy to.
			*/
			static bool CopyChecked(const FString& Context, const ValueType* From, ValueType* To);
		};

	#undef ValueType
	}
}