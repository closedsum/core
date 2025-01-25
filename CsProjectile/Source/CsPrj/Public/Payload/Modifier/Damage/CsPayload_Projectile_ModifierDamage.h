// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "CsMacro_Namespace.h"

// ModifierType (NCsDamage::NModifier::IModifier)
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				/**
				*/
				struct CSPRJ_API IDamage : public ICsGetInterfaceMap
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

					virtual ~IDamage(){}

					virtual const TArray<_::ModifierType*>& GetDamageModifiers() const = 0;
				};
			}
		}
	}
}