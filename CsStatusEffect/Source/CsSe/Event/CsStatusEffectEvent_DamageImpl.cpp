// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEvent_DamageImpl.h"

const FName FCsStatusEffectEvent_DamageImpl::Name = FName("FCsStatusEffectEvent_DamageImpl");;

FCsStatusEffectEvent_DamageImpl::FCsStatusEffectEvent_DamageImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(),
	// ICsStatusEffectEvent
	StatusEffect(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	// ICsStatusEffectEvent_Damage
	DamageEvent(nullptr),
	DamageEventContainer(nullptr)
{
	InterfaceMap.SetRootName(FCsStatusEffectEvent_DamageImpl::Name);

	InterfaceMap.Add<ICsStatusEffectEvent>(static_cast<ICsStatusEffectEvent*>(this));
	InterfaceMap.Add<ICsStatusEffectEvent_Damage>(static_cast<ICsStatusEffectEvent_Damage*>(this));
}

void FCsStatusEffectEvent_DamageImpl::Reset()
{
	StatusEffect = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	DamageEvent = nullptr;
}