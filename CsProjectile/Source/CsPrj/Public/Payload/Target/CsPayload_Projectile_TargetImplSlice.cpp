// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Target/CsPayload_Projectile_TargetImplSlice.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::NTarget::FImplSlice::Name = FName("NCsProjectile::NPayload::NTarget::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NTarget
		{
			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// ITarget
				bTarget(false),
				Component(nullptr),
				Location(0.0f),
				Bone(NAME_None),
				ID(INDEX_NONE)
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NCollision::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NCollision::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<ITarget>(FImplSlice::Name, static_cast<ITarget*>(this));
			}

			// ICsReset
			#pragma region

			void FImplSlice::Reset()
			{	
				bTarget  = false;
				Component = nullptr;
				Location = FVector3f::ZeroVector;
				Bone	 = NAME_None;
				ID		 = INDEX_NONE;
			}

			#pragma endregion ICsReset
		}
	}
}