// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Payload/Damage/CsPayload_BeamModifierDamageImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsBeam::NPayload::NModifier::NDamage::FImplSlice::Name = FName("NCsBeam::NPayload::NModifier::NDamage::FImplSlice");;

namespace NCsBeam
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
					checkf(InInterfaceMap, TEXT("NCsBeam::NPayload::NModifier::NDamage::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

					checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsBeam::NPayload::NModifier::NDamage::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

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