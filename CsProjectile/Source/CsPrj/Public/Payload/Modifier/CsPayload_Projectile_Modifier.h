// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

// NCsProjectile::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsProjectile, NModifier, IModifier)

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			/**
			*/
			struct CSPRJ_API IModifier : public ICsGetInterfaceMap
			{
			public:

				static const FName Name;

			#define ModifierType NCsProjectile::NModifier::IModifier

			public:

				virtual ~IModifier(){}

				virtual const TArray<ModifierType*>& GetModifiers() const = 0;

			#undef ModifierType
			};
		}
	}
}