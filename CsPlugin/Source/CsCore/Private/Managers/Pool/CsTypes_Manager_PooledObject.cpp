// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
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
			ConstructionInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
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