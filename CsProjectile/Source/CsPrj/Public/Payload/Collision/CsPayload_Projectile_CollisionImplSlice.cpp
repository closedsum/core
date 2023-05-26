// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Collision/CsPayload_Projectile_CollisionImplSlice.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::NCollision::FImplSlice::Name = FName("NCsProjectile::NPayload::NCollision::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NCollision
		{
			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// ICollision
				IgnoreActorsOnHit(),
				IgnoreComponentsOnHit()
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NCollision::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NCollision::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<ICollision>(FImplSlice::Name, static_cast<ICollision*>(this));
			}

			// ICsReset
			#pragma region

			void FImplSlice::Reset()
			{	
				IgnoreActorsOnHit.Reset(IgnoreActorsOnHit.Max());
				IgnoreComponentsOnHit.Reset(IgnoreComponentsOnHit.Max());
			}

			#pragma endregion ICsReset
		}
	}
}