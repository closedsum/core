// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"
#pragma once

// NCsDamage::NModifier::IModifier
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

				#define DmgModifierType NCsDamage::NModifier::IModifier

				public:

					virtual ~IDamage(){}

					virtual const TArray<DmgModifierType*>& GetDamageModifiers() const = 0;

				#undef DmgModifierType
				};
			}
		}
	}
}