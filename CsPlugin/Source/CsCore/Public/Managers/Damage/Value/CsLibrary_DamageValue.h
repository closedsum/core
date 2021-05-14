// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Value/CsDamageValue.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsDamage
{
	namespace NValue
	{
	#define ValueType NCsDamage::NValue::IValue

		/**
		* Library for interface: ValueType (NCsDamage::NValue::IValue)
		*/
		struct CSCORE_API FLibrary final : public TCsLibrary_InterfaceMap<ValueType>
		{
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