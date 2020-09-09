// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsSpawnerParams.h"
#include "Containers/CsLibrary_InterfaceMap.h"

#pragma once

struct CSCORE_API FCsLibrary_SpawnerParams : public TCsLibrary_InterfaceMap<ICsSpawnerParams>
{
public:

	/**
	*
	*
	* @param Params
	* return
	*/
	static float CalculateTotalTime(const ICsSpawnerParams* Params);
};