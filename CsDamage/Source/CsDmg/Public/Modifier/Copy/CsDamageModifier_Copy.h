// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

// ModifierType (NCsDamage::NModifier::IModifier)
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

			private:

				// Allow clearer names without name collisions
				struct _
				{
					using ModifierType = NCsDamage::NModifier::IModifier;
				};

			public:

				virtual ~ICopy() {}

				virtual void Copy(const _::ModifierType* From) = 0;
			};
		}
	}
}