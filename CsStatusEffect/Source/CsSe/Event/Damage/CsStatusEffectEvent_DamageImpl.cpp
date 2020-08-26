// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/Damage/CsStatusEffectEvent_DamageImpl.h"

const FName FCsStatusEffectEvent_DamageImpl::Name = FName("FCsStatusEffectEvent_DamageImpl");;

FCsStatusEffectEvent_DamageImpl::FCsStatusEffectEvent_DamageImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(),
	// ICsStatusEffectEvent
	Data(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	Receiver(nullptr),
	IgnoreObjects(),
	// ICsStatusEffectEvent_Damage
	DamageEvent(nullptr),
	DamageEventContainer(nullptr)
{
	InterfaceMap.SetRootName(FCsStatusEffectEvent_DamageImpl::Name);

	InterfaceMap.Add<ICsStatusEffectEvent>(static_cast<ICsStatusEffectEvent*>(this));
	InterfaceMap.Add<ICsStatusEffectEvent_Damage>(static_cast<ICsStatusEffectEvent_Damage*>(this));
	InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
}

// ICsReset
#pragma region

void FCsStatusEffectEvent_DamageImpl::Reset()
{
	Data = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	Receiver = nullptr;
	IgnoreObjects.Reset(IgnoreObjects.Max());
	DamageEvent = nullptr;
	DamageEventContainer = nullptr;
}

#pragma endregion ICsReset