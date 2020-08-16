// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Payload/CsPayload_ProjectilePooledImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_ProjectilePooledImpl::Name = FName("FCsPayload_ProjectilePooledImpl");;

FCsPayload_ProjectilePooledImpl::FCsPayload_ProjectilePooledImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	// ICsPayload_Projectile
	Direction(0.0f),
	Location(0.0f)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_ProjectilePooledImpl::Name);

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
	InterfaceMap->Add<ICsPayload_Projectile>(static_cast<ICsPayload_Projectile*>(this));
}

FCsPayload_ProjectilePooledImpl::~FCsPayload_ProjectilePooledImpl()
{
	// ICsGetInterfaceMap
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_ProjectilePooledImpl::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();
	// ICsPayload_Projectile
	Direction = FVector::ZeroVector;
	Location = FVector::ZeroVector;
}

#pragma endregion ICsPayload_PooledObject