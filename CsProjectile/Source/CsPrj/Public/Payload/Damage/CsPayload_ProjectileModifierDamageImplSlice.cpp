// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/Damage/CsPayload_ProjectileModifierDamageImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_ProjectileModifierDamageImplSlice::Name = FName("FCsPayload_ProjectileModifierDamageImplSlice");;

FCsPayload_ProjectileModifierDamageImplSlice::FCsPayload_ProjectileModifierDamageImplSlice() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_Projectile
	Modifiers()
{
}

void FCsPayload_ProjectileModifierDamageImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
{
	checkf(InInterfaceMap, TEXT("FCsPayload_ProjectileModifierDamageImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

	checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_ProjectileModifierDamageImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

	InterfaceMap = InInterfaceMap;

	InterfaceMap->Add<ICsPayload_ProjectileModifierDamage>(FCsPayload_ProjectileModifierDamageImplSlice::Name, static_cast<ICsPayload_ProjectileModifierDamage*>(this));
}


// ICsReset
#pragma region

void FCsPayload_ProjectileModifierDamageImplSlice::Reset()
{	
	Modifiers.Reset(Modifiers.Max());
}

#pragma endregion ICsReset

bool FCsPayload_ProjectileModifierDamageImplSlice::CopyFrom(const FCsPayload_ProjectileModifierDamageImplSlice* From)
{
	return true;
}