// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectDamageEventImpl.h"

const FName FCsStatusEffectDamageEventImpl::Name = FName("FCsStatusEffectDamageEventImpl");;

FCsStatusEffectDamageEventImpl::FCsStatusEffectDamageEventImpl() :
	InterfaceMap(),
	// ICsStatusEffectEvent
	StatusEffect(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	DamageEvent(nullptr)
{
	InterfaceMap.SetRootName(FCsStatusEffectDamageEventImpl::Name);

	InterfaceMap.Add<ICsStatusEffectEvent>(static_cast<ICsStatusEffectEvent*>(this));
	InterfaceMap.Add<ICsStatusEffectDamageEvent>(static_cast<ICsStatusEffectDamageEvent*>(this));
}

void FCsStatusEffectDamageEventImpl::Reset()
{
	StatusEffect = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	DamageEvent = nullptr;
}