// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Damage/CsPayload_Projectile_DamageImplSlice.h"

// Container
#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::NDamage::FImplSlice::Name = FName("NCsProjectile::NPayload::NDamage::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NDamage
		{
			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IDamage
				DataTypes()
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NDamage::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NDamage::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<IDamage>(FImplSlice::Name, static_cast<IDamage*>(this));
			}

			// ICsReset
			#pragma region

			void FImplSlice::Reset()
			{	
				DataTypes.Reset(DataTypes.Max());
			}

			#pragma endregion ICsReset
		}
	}
}