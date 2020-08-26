// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Event/CsStatusEffectEventImpl.h"

const FName FCsStatusEffectEventImpl::Name = FName("FCsStatusEffectEventImpl");;

FCsStatusEffectEventImpl::FCsStatusEffectEventImpl() :
	InterfaceMap(),
	// ICsStatusEffectEvent
	Data(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	Receiver(nullptr),
	IgnoreObjects()
{
	InterfaceMap.SetRootName(FCsStatusEffectEventImpl::Name);

	InterfaceMap.Add<ICsStatusEffectEvent>(static_cast<ICsStatusEffectEvent*>(this));
}

void FCsStatusEffectEventImpl::Reset()
{
	Data = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	Receiver = nullptr;
	IgnoreObjects.Reset(IgnoreObjects.Max());
}