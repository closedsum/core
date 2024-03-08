// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_Macro.h"

// NCsDamage::NModifier::IModifier
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsDamage, NModifier, IModifier)

namespace NCsBeam
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				/**
				*/
				struct CSBEAM_API IDamage : public ICsGetInterfaceMap
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