// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileImplSlice.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsProjectile::NPayload::NImplSlice::FImplSlice);

namespace NCsProjectile
{
	namespace NPayload
	{
		namespace NImplSlice
		{
			FImplSlice::FImplSlice() :
				// ICsGetInterfaceMap
				InterfaceMap(nullptr),
				// PaylaodType (NCsProjectile::NPayload::IPayload)
				Type(),
				Generation(0),
				Direction(0.0f),
				Location(0.0f)
			{
			}

			void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
			{
				checkf(InInterfaceMap, TEXT("NCsProjectile::NPayload::NImplSlice::FImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));
				checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("NCsProjectile::NPayload::NImplSlice::FImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

				InterfaceMap = InInterfaceMap;

				InterfaceMap->Add<PayloadType>(FImplSlice::Name, static_cast<PayloadType*>(this));
			}


			// ICsReset
			#pragma region

			void FImplSlice::Reset()
			{
				// PaylaodType (NCsProjectile::NPayload::IPayload)
				Type		= EMCsProjectile::Get().GetMAX();
				Generation  = 0;
				Direction	= FVector::ZeroVector;
				Location	= FVector::ZeroVector;
			}

			#pragma endregion ICsReset

			bool FImplSlice::CopyFrom(const FImplSlice* From)
			{
				Generation = From->Generation;
				Direction = From->Direction;
				Location = From->Location;
				return true;
			}
		}
	}
}