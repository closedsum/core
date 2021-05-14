// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Modifier/CsStatusEffectModifier.h"
#include "Containers/CsLibrary_InterfaceMap.h"
#pragma once

namespace NCsStatusEffect
{
	namespace NModifier
	{
	#define ModifierType NCsStatusEffect::NModifier::IModifier

		/**
		* Library for interface: ModifierType (NCsStatusEffect::NModifier::IModifier)
		*/
		struct CSSE_API FLibrary final : public TCsLibrary_InterfaceMap<ModifierType>
		{
		};

	#undef ModifierType
	}
}