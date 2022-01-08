// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Containers
#include "Containers/CsLibrary_InterfaceMap.h"
// Interface
#include "Modifier/CsModifier.h"

namespace NCsModifier
{
#define ModifierType NCsModifier::IModifier

	/**
	* Library for interface: ModifierType (NCsModifier::IModifier)
	*/
	struct CSCORE_API FLibrary final : public NCsInterfaceMap::TLibrary<ModifierType>
	{
	};

#undef ModifierType
}