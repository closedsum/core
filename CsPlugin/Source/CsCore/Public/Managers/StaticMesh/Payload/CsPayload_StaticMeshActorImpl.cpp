// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_StaticMeshActorImpl::Name = FName("FCsPayload_StaticMeshActorImpl");;

FCsPayload_StaticMeshActorImpl::FCsPayload_StaticMeshActorImpl() :
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	// ICsPayload_StaticMeshActor
	Mesh(nullptr),
	DeallocateMethod(ECsStaticMeshActorDeallocateMethod::Complete),
	LifeTime(0.0f),
	AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
	Bone(NAME_None),
	TransformRules(0),
	Transform(FTransform::Identity)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_StaticMeshActorImpl::Name);

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
	InterfaceMap->Add<ICsPayload_StaticMeshActor>(static_cast<ICsPayload_StaticMeshActor*>(this));
}

FCsPayload_StaticMeshActorImpl::~FCsPayload_StaticMeshActorImpl()
{
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_StaticMeshActorImpl::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();

	// ICsPayload_StaticMeshActor
	Mesh = nullptr;
	DeallocateMethod = ECsStaticMeshActorDeallocateMethod::Complete;
	LifeTime = 0.0f;
	AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules = 0;
	Transform = FTransform::Identity;
}

#pragma endregion ICsPayload_PooledObject