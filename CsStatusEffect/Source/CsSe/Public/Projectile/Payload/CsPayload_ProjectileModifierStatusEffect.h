// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Containers/CsGetInterfaceMap.h"
#pragma once

namespace NCsStatusEffect {
	namespace NModifier {
		struct IModifier; } }

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NStatusEffect
			{
				/**
				*/
				struct CSSE_API IStatusEffect : virtual public ICsGetInterfaceMap
				{
				public:

					static const FName Name;

				public:

					virtual ~IStatusEffect(){}

					virtual const TArray<NCsStatusEffect::NModifier::IModifier*>& GetStatusEffectModifiers() const = 0;
				};
			}
		}
	}
}