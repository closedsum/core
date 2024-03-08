// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

// NCsWeapon::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsWeapon, NModifier, IModifier)

namespace NCsWeapon
{
	namespace NModifier
	{
		namespace NCopy
		{
			/**
			* Interface for a Weapon Modifier performing various Copy commands.
			*/
			struct CSWP_API ICopy : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define ModifierType NCsWeapon::NModifier::IModifier

			public:

				virtual ~ICopy() {}

				virtual void Copy(const ModifierType* From) = 0;

			#undef ModifierType
			};
		}
	}
}