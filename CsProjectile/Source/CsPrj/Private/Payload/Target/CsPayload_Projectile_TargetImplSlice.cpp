// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Target/CsPayload_Projectile_TargetImplSlice.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_INTERFACE_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NPayload::NTarget::NImplSlice::FImplSlice);

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NTarget
		{
			namespace NImplSlice
			{
				FImplSlice::FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// TargetPayloadType (NCsProjectile::NPayload::NTarget::ITarget)
					bTarget(false),
					Component(nullptr),
					Location(0.0f),
					Bone(NAME_None),
					ID(INDEX_NONE)
				{
				}

				void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
				{
					checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NCollision::NImplSlice::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));
					checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NCollision::NImplSlice::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

					InterfaceMap = InInterfaceMap;

					InterfaceMap->Add<TargetPayloadType>(FImplSlice::Name, static_cast<TargetPayloadType*>(this));
				}

				// ICsReset
				#pragma region

				void FImplSlice::Reset()
				{	
					bTarget  = false;
					Component = nullptr;
					Location = FVector::ZeroVector;
					Bone	 = NAME_None;
					ID		 = INDEX_NONE;
				}

				#pragma endregion ICsReset
			}
		}
	}
}