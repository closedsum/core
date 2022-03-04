// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Types
#include "Value/Types/CsTypes_DamageValue.h"
// Damage
#include "Value/CsDamageValue.h"

namespace NCsDamage
{
	namespace NValue
	{
	#define ValueType NCsDamage::NValue::IValue

		/**
		* Library for interface: ValueType (NCsDamage::NValue::IValue)
		*/
		struct CSDMG_API FLibrary final : public NCsInterfaceMap::TLibrary<ValueType>
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