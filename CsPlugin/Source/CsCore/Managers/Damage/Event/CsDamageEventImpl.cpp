// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Event/CsDamageEventImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsDamageEventImpl::Name = FName("FCsDamageEventImpl");;

FCsDamageEventImpl::FCsDamageEventImpl() :
	InterfaceMap(nullptr),
	// ICsDamageEvent
	Expression(nullptr),
	Instigator(nullptr),
	Causer(nullptr),
	HitType(),
	HitResult()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageEventImpl::Name);

	InterfaceMap->Add<ICsDamageEvent>(static_cast<ICsDamageEvent*>(this));
}

FCsDamageEventImpl::~FCsDamageEventImpl()
{
	delete InterfaceMap;
}

void FCsDamageEventImpl::Reset()
{
	Expression = nullptr;
	Instigator = nullptr;
	Causer = nullptr;
	HitType = EMCsHitType::Get().GetMAX();
	HitResult.Reset(0.0f, false);
}