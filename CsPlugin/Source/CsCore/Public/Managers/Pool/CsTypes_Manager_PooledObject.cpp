// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Pool/CsTypes_Manager_PooledObject.h"

namespace NCsPooledObject
{
	namespace NManager
	{
		FConstructParams::FConstructParams() :
			Outer(nullptr),
			Class(nullptr),
			TypeName(NAME_None),
			ClassTypeName(NAME_None),
			ConstructionType(NCsPooledObject::EConstruction::Object),
			ConstructionInfo(),
			bReplicates(false)
		{
		}

		FPoolParams::FPoolParams() :
			Name(),
			World(nullptr),
			LogType(),
			ConstructParams(),
			bConstructPayloads(false),
			PayloadSize(0),
			bCreatePool(false),
			PoolSize(0),
			ScopedGroup(),
			CreatePoolScopedTimerCVar(),
			UpdateScopedTimerCVar(),
			UpdateObjectScopedTimerCVar(),
			AllocateScopedTimerCVar(),
			AllocateObjectScopedTimerCVar(),
			DeallocateScopedTimerCVar(),
			DeallocateObjectScopedTimerCVar(),
			SpawnScopedTimerCVar(),
			DestroyScopedTimerCVar()
		{
		}
	}
}