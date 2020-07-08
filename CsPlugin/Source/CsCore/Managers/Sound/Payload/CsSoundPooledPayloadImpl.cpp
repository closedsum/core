// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsSoundPooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsSoundPooledPayloadImpl::Name = FName("FCsSoundPooledPayloadImpl");;

FCsSoundPooledPayloadImpl::FCsSoundPooledPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	Sound(nullptr),
	DeallocateMethod(ECsSoundDeallocateMethod::Complete),
	LifeTime(0.0f),
	AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
	Bone(NAME_None),
	TransformRules(0),
	Transform(FTransform::Identity)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsSoundPooledPayloadImpl::Name);

	InterfaceMap->Add<ICsPooledObjectPayload>(static_cast<ICsPooledObjectPayload*>(this));
	InterfaceMap->Add<ICsSoundPooledPayload>(static_cast<ICsSoundPooledPayload*>(this));
}

FCsSoundPooledPayloadImpl::~FCsSoundPooledPayloadImpl()
{
	delete InterfaceMap;
}

// ICsPooledObjectPayload
#pragma region

void FCsSoundPooledPayloadImpl::Reset()
{
	// ICsPooledObjectPayload
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();

	// ICsFXPooledPayload
	Sound = nullptr;
	DeallocateMethod = ECsSoundDeallocateMethod::Complete;
	LifeTime = 0.0f;
	AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules = 0;
	Transform = FTransform::Identity;
}

#pragma endregion ICsPooledObjectPayload