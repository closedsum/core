// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"

namespace NCsModifier
{
	/**
	* Interface for describing a Modifier.
	* Modifiers usually alter existing stats, members, ... etc on an object.
	*/
	struct CSCORE_API IModifier : public ICsGetInterfaceMap
	{
	public:

		static const FName Name;

	public:

		virtual ~IModifier(){}
	};
}