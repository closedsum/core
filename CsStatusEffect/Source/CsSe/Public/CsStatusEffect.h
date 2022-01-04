// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

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
	};
}