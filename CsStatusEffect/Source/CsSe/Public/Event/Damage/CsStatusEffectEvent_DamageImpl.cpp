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
	DamageEvent()
{
	InterfaceMap.SetRootName(FCsStatusEffectEvent_DamageImpl::Name);

	InterfaceMap.Add<ICsStatusEffectEvent>(static_cast<ICsStatusEffectEvent*>(this));
	InterfaceMap.Add<ICsStatusEffectEvent_Damage>(static_cast<ICsStatusEffectEvent_Damage*>(this));
	InterfaceMap.Add<ICsReset>(static_cast<ICsReset*>(this));
}

void FCsStatusEffectEvent_DamageImpl::CopyFrom(const FCsStatusEffectEvent_DamageImpl* From)
{
	// ICsStatusEffectEvent

	Data = From->Data;
	Instigator = From->Instigator;
	Causer = From->Causer;
	Receiver = From->Receiver;

	IgnoreObjects.Reset(FMath::Max(IgnoreObjects.Max(), From->IgnoreObjects.Max()));

	for (TWeakObjectPtr<UObject> O : From->IgnoreObjects)
	{
		IgnoreObjects.Add(O);
	}

	// ICsStatusEffectEvent_Damage

	DamageEvent.CopyFrom(&(From->DamageEvent));
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
	DamageEvent.Reset();
}

#pragma endregion ICsReset