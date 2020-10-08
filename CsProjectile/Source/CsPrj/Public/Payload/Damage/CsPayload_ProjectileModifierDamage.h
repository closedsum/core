// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

				public:

					virtual ~IDamage(){}

					virtual const TArray<NCsDamage::NModifier::IModifier*>& GetDamageModifiers() const = 0;
				};
			}
		}
	}
}