// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsSpawnerParamsImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsSpawnerParamsImpl::Name = FName("FCsSpawnerParamsImpl");;

FCsSpawnerParamsImpl::FCsSpawnerParamsImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsSpawnerParams
	CountParams(),
	FrequencyParams(),
	TotalTime(0.0f)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRoot<FCsSpawnerParamsImpl>(this);

	InterfaceMap->Add<ICsSpawnerParams>(static_cast<ICsSpawnerParams*>(this));
}

FCsSpawnerParamsImpl::~FCsSpawnerParamsImpl()
{
	delete InterfaceMap;
}