// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Payload/CsPayload_ProjectileModifierStatusEffectImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::NModifier::NStatusEffect::FImplSlice::Name = FName("NCsProjectile::NPayload::NModifier::NStatusEffect::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			namespace NStatusEffect
			{
				FImplSlice::FImplSlice() :
					// ICsGetInterfaceMap
					InterfaceMap(nullptr),
					// IStatusEffect
					Modifiers()
				{
				}

				void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
				{
					checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NModifier::NStatusEffect::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

					checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NModifier::NStatusEffect::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

					InterfaceMap = InInterfaceMap;

					InterfaceMap->Add<IStatusEffect>(FImplSlice::Name, static_cast<IStatusEffect*>(this));
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