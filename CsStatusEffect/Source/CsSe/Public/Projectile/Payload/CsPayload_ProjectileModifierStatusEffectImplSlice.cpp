// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Projectile/Payload/CsPayload_ProjectileModifierStatusEffectImplSlice.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_ProjectileModifierStatusEffectImplSlice::Name = FName("FCsPayload_ProjectileModifierStatusEffectImplSlice");;

FCsPayload_ProjectileModifierStatusEffectImplSlice::FCsPayload_ProjectileModifierStatusEffectImplSlice() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_Projectile
	Modifiers()
{
}

void FCsPayload_ProjectileModifierStatusEffectImplSlice::SetInterfaceMap(FCsInterfaceMap* InInterfaceMap)
{
	checkf(InInterfaceMap, TEXT("FCsPayload_ProjectileModifierStatusEffectImplSlice::SetInterfaceMap: InInterfaceMap is NULL."));

	checkf(InInterfaceMap->HasUniqueBasedSlices(), TEXT("FCsPayload_ProjectileModifierStatusEffectImplSlice::SetInterfaceMap: This only takes an InterfaceMap with bUniqueBasedSlices = true."));

	InterfaceMap = InInterfaceMap;

	InterfaceMap->Add<ICsPayload_ProjectileModifierStatusEffect>(FCsPayload_ProjectileModifierStatusEffectImplSlice::Name, static_cast<ICsPayload_ProjectileModifierStatusEffect*>(this));
}


// ICsReset
#pragma region

void FCsPayload_ProjectileModifierStatusEffectImplSlice::Reset()
{	
	Modifiers.Reset(Modifiers.Max());
}

#pragma endregion ICsReset

bool FCsPayload_ProjectileModifierStatusEffectImplSlice::CopyFrom(const FCsPayload_ProjectileModifierStatusEffectImplSlice* From)
{
	return true;
}