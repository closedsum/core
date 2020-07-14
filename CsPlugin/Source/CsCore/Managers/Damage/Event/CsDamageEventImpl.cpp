// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEventImpl.h"

const FName FCsDamageEventImpl::Name = FName("FCsDamageEventImpl");;

FCsDamageEventImpl::FCsDamageEventImpl() :
	InterfaceMap(),
	// ICsDamageEvent
	Expression(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	HitType(),
	HitResult()
{
	InterfaceMap.SetRootName(FCsDamageEventImpl::Name);

	InterfaceMap.Add<ICsDamageEvent>(static_cast<ICsDamageEvent*>(this));
}

void FCsDamageEventImpl::Reset()
{
	Expression = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	HitType = EMCsHitType::Get().GetMAX();
	HitResult.Reset(0.0f, false);
}