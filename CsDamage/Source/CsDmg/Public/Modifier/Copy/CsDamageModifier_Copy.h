// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsDamage
{
	namespace NModifier
	{
		namespace NCopy
		{
			struct CSDMG_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define ModifierType NCsDamage::NModifier::IModifier

			public:

				virtual ~ICopy() {}

				virtual void Copy(const ModifierType* From) = 0;

			#undef ModifierType 
			};
		}
	}
}