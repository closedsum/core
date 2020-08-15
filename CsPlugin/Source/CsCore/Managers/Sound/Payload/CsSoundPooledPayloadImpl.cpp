// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsSoundPooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsSoundPooledPayloadImpl::Name = FName("FCsSoundPooledPayloadImpl");;

FCsSoundPooledPayloadImpl::FCsSoundPooledPayloadImpl() :
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	// ICsSoundPooledPayload
	Sound(nullptr),
	SoundAttenuation(nullptr),
	DeallocateMethod(ECsSoundDeallocateMethod::Complete),
	LifeTime(0.0f),
	AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
	Bone(NAME_None),
	TransformRules(0),
	Transform(FTransform::Identity)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsSoundPooledPayloadImpl::Name);

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
	InterfaceMap->Add<ICsSoundPooledPayload>(static_cast<ICsSoundPooledPayload*>(this));
}

FCsSoundPooledPayloadImpl::~FCsSoundPooledPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsSoundPooledPayloadImpl::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();

	// ICsSoundPooledPayload
	Sound = nullptr;
	SoundAttenuation = nullptr;
	DeallocateMethod = ECsSoundDeallocateMethod::Complete;
	LifeTime = 0.0f;
	AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules = 0;
	Transform = FTransform::Identity;
}

#pragma endregion ICsPayload_PooledObject