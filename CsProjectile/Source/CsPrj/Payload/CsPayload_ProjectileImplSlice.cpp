// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectileImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_ProjectileImplSlice::Name = FName("FCsPayload_ProjectileImplSlice");;

FCsPayload_ProjectileImplSlice::FCsPayload_ProjectileImplSlice() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_Projectile
	Direction(0.0f),
	Location(0.0f)
{
}

void FCsPayload_ProjectileImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
{
	checkf(InInterfaceMap, TEXT("FCsPayload_ProjectileImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

	checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_ProjectileImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

	InterfaceMap = InInterfaceMap;

	InterfaceMap->Add<ICsPayload_Projectile>(FCsPayload_ProjectileImplSlice::Name, static_cast<ICsPayload_Projectile*>(this));
}


// ICsReset
#pragma region

void FCsPayload_ProjectileImplSlice::Reset()
{
	// ICsPayload_Projectile
	Direction = FVector::ZeroVector;
	Location = FVector::ZeroVector;
}

#pragma endregion ICsReset