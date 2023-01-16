// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Spawner/Modifier/Types/CsTypes_SpawnerModifier.h"

/**
* Interface to get the Spawner Modifier "type".
* This is used to provide an easier way to access what the "type" is
* for a Spawner Modifier.
*  Spawner Modifier implements the interface: NCsSpawner::NModifier::IModifier.
*/
struct CSCORE_API ICsGetSpawnerModifierType : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsGetSpawnerModifierType() {}

	/**
	* Get the type of the Spawner Modifier.
	* 
	* return Type.
	*/
	virtual const FECsSpawnerModifier& GetSpawnerModifierType() const = 0;
};