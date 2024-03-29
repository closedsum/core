// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsProjectile::NPayload::FImplSlice::Name = FName("NCsProjectile::NPayload::FImplSlice");;

namespace NCsProjectile
{
	namespace NPayload
	{
		FImplSlice::FImplSlice() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// IPayload
			Type(),
			Generation(0),
			Direction(0.0f),
			Location(0.0f)
		{
		}

		void FImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
		{
			checkf(InInterfaceMap, TEXT("FCsPayload_ProjectileImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

			checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_ProjectileImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

			InterfaceMap = InInterfaceMap;

			InterfaceMap->Add<IPayload>(FImplSlice::Name, static_cast<IPayload*>(this));
		}


		// ICsReset
		#pragma region

		void FImplSlice::Reset()
		{
			// IPayload
			Type		= EMCsProjectile::Get().GetMAX();
			Generation  = 0;
			Direction	= FVector3f::ZeroVector;
			Location	= FVector3f::ZeroVector;
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