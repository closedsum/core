// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsDamage {
	namespace NModifier {
		struct IModifier; } }

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
				struct CSPRJ_API IDamage : virtual public ICsGetInterfaceMap
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