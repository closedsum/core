// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsFXPooledPayloadImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsFXPooledPayloadImpl::Name = FName("FCsFXPooledPayloadImpl");;

FCsFXPooledPayloadImpl::FCsFXPooledPayloadImpl() :
	InterfaceMap(nullptr),
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	FXSystem(nullptr),
	DeallocateMethod(ECsFXDeallocateMethod::Complete),
	LifeTime(0.0f),
	AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
	Bone(NAME_None),
	TransformRules(0),
	Transform(FTransform::Identity)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsFXPooledPayloadImpl::Name);

	InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
	InterfaceMap->Add<ICsFXPooledPayload>(static_cast<ICsFXPooledPayload*>(this));
}

FCsFXPooledPayloadImpl::~FCsFXPooledPayloadImpl()
{
	delete InterfaceMap;
}

// NCsPooledObject::NPayload::IPayload
#pragma region

void FCsFXPooledPayloadImpl::Reset()
{
	// NCsPooledObject::NPayload::IPayload
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();

	// ICsFXPooledPayload
	FXSystem = nullptr;
	DeallocateMethod = ECsFXDeallocateMethod::Complete;
	LifeTime = 0.0f;
	AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules = 0;
	Transform = FTransform::Identity;
}

#pragma endregion NCsPooledObject::NPayload::IPayload