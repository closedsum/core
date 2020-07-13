// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Damage/Result/CsDamageResultImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsDamageResultImpl::Name = FName("FCsDamageResultImpl");;

FCsDamageResultImpl::FCsDamageResultImpl() :
	InterfaceMap(nullptr),
	// ICsDamageResult
	Damage(0.0f),
	Instigator(nullptr),
	Causer(nullptr),
	Victim(nullptr),
	DamageType(),
	HitType(),
	bImpulse(false),
	HitResult()
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsDamageResultImpl::Name);

	InterfaceMap->Add<ICsDamageResult>(static_cast<ICsDamageResult*>(this));
}

FCsDamageResultImpl::~FCsDamageResultImpl()
{
	delete InterfaceMap;
}

void FCsDamageResultImpl::Reset()
{
	Damage = 0.0f;
	Instigator = nullptr;
	Causer = nullptr;
	Victim = nullptr;
	DamageType = EMCsDamageType::Get().GetMAX();
	HitType = EMCsHitType::Get().GetMAX();
	bImpulse = false;
	HitResult.Reset(0.0f, false);
}