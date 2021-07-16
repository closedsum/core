// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Params/CsSpawnerParamsImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsSpawner::NParams::FImpl::Name = FName("NCsSpawner::NParams::FImpl");;

namespace NCsSpawner
{
	namespace NParams
	{
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// ParamsType (NCsSpawner::NParams::IParams)
			CountParams(),
			FrequencyParams(),
			TotalTime(0.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsSpawner::NParams::IParams ParamsType;

			InterfaceMap->Add<ParamsType>(static_cast<ParamsType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}
	}
}