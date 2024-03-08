// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Spawner/Point/CsSpawnerPointImpl.h"

// Library
#include "Library/CsLibrary_Math.h"
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

		FTransform3f FImpl::GetCenterTransform() const
		{
			typedef NCsMath::FLibrary MathLibrary;

			if (CenterAsActor)
				return MathLibrary::Convert(CenterAsActor->GetActorTransform());
			return CenterAsTransform;
		}

		#pragma endregion ImplType (NCsSpawner::NPoint::IImpl)
	}
}