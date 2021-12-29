// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Modifier/CsPayload_Projectile_ModifierImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::NModifier::FImplSlice::Name = FName("NCsProjectile::NPayload::NModifier::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NModifier
		{
			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// IModifier
				Modifiers(),
				Root(nullptr)
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NModifier::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NModifier::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<IModifier>(FImplSlice::Name, static_cast<IModifier*>(this));
			}

			// ICsReset
			#pragma region

			void FImplSlice::Reset()
			{	
				// TODO: Deallocate Modifiers
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