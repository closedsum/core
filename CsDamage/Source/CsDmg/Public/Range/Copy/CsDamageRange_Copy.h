// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Macro/CsMacro_Namespace.h"

// NCsDamage::NRange::IRange
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NRange, IRange)

namespace NCsDamage
{
	namespace NRange
	{
		namespace NCopy
		{
			/**
			* Interface for a Damage Range, object that implements the interface: NCsDamage::NRange::IRange,
			* performing various Copy commands.
			*/
			struct CSDMG_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define RangeType NCsDamage::NRange::IRange

			public:

				virtual ~ICopy(){}

				virtual void Copy(const RangeType* From) = 0;

			#undef RangeType
			};
		}
	}
}