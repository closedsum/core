// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Containers/CsGetInterfaceMap.h"
// Types
#include "Spawner/Params/CsTypes_SpawnerParams.h"

struct CSCORE_API ICsSpawnerParams : public ICsGetInterfaceMap
{
public:

	static const FName Name;

public:

	virtual ~ICsSpawnerParams(){}
	
	/**
	*
	*
	* return Count Params
	*/
	virtual const FCsSpawnerCountParams& GetCountParams() const = 0;

	virtual const FCsSpawnerFrequencyParams& GetFrequencyParams() const = 0;

	virtual const float& GetTotalTime() const = 0;
};