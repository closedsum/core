// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

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