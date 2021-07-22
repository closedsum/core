// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Spawner/Point/CsSpawnerPointImpl.h"

// Spawner
#include "Spawner/CsSpawner.h"
// Actor
#include "GameFramework/Actor.h"

namespace NCsSpawner
{
	namespace NPoint
	{
		// ImplType (NCsSpawner::NPoint::IImpl)
		#pragma region

		void FImpl::SetSpawner(ICsSpawner* InSpawner)
		{
			Spawner		   = InSpawner;
			SpawnerAsActor = Cast<AActor>(InSpawner->_getUObject());
		}


		void FImpl::Advance(const int32& Count, const int32& Group, const int32& CountPerGroup)
		{
			Index = Count;
			CurrentGroup = Group;
		}

		#pragma endregion ImplType (NCsSpawner::NPoint::IImpl)
	}
}