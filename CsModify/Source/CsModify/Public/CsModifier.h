// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsModifier
{
	/**
	* Interface for describing a Modifier.
	* Modifiers usually alter existing stats, members, ... etc on an object.
	*/
	struct CSMODIFY_API IModifier : public ICsGetInterfaceMap
	{
	public:

		static const FName Name;

	public:

		virtual ~IModifier(){}
	};
}