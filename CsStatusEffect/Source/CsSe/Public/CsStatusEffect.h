// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Types/CsTypes_StatusEffect.h"

namespace NCsStatusEffect
{
	/**
	* Interface for describing a Status Effect
	*/
	struct CSSE_API IStatusEffect : public ICsGetInterfaceMap
	{
	public:

		static const FName Name;

	public:

		virtual ~IStatusEffect(){}

		virtual const FECsStatusEffect& GetStatusEffectType() const = 0;
	};
}