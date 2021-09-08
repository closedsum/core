// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Damage/CsPayload_ProjectileModifierDamageImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::NModifier::NDamage::FImplSlice::Name = FName("NCsProjectile::NPayload::NModifier::NDamage::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NDamage
			{
				FImplSlice::FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// IPayload
					Modifiers()
				{
				}

				void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
				{
					checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NModifier::NDamage::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

					checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NModifier::NDamage::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

					InterfaceMap = InInterfaceMap;

					InterfaceMap->Add<IDamage>(FImplSlice::Name, static_cast<IDamage*>(this));
				}

				// ICsReset
				#pragma region

				void FImplSlice::Reset()
				{	
					Modifiers.Reset(Modifiers.Max());
				}

				#pragma endregion ICsReset

				bool FImplSlice::CopyFrom(const FImplSlice* From)
				{
					return true;
				}
			}
		}
	}
}