// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Range/CsDamageRange.h"
#include "Containers/CsLibrary_InterfaceMap.h"

namespace NCsDamage
{
	namespace NRange
	{
	#define RangeType NCsDamage::NRange::IRange

		/**
		* Library for interface: RangeType (NCsDamage::NRange::IRange)
		*/
		struct CSDMG_API FLibrary final : public NCsInterfaceMap::TLibrary<RangeType>
		{
			/**
			* Copy the values from From to To with checks.
			* Currently supports To types of:
			*  NCsDamage::NRange::FImpl (NCsDamage::NRange::IRange)
			*
			* @param Context	The calling context.
			* @param From		What to copy.
			* @param To			What to copy to.
			*/
			static bool CopyChecked(const FString& Context, const RangeType* From, RangeType* To);
		};

	#undef RangeType
	}
}