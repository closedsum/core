// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
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

				private:

					typedef NCsStatusEffect::NModifier::IModifier ModifierType;

				public:

					virtual ~IStatusEffect(){}

					virtual const TArray<ModifierType*>& GetStatusEffectModifiers() const = 0;
				};
			}
		}
	}
}