// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName FCsPayload_WidgetActorImpl::Name = FName("FCsPayload_WidgetActorImpl");;

FCsPayload_WidgetActorImpl::FCsPayload_WidgetActorImpl() :
	// ICsGetInterfaceMap
	InterfaceMap(nullptr),
	// ICsPayload_PooledObject
	bAllocated(false),
	Instigator(nullptr),
	Owner(nullptr),
	Parent(nullptr),
	Time(),
	// ICsPayload_WidgetActor
	UserWidget(nullptr),
	DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
	LifeTime(0.0f),
	AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
	Bone(NAME_None),
	TransformRules(0),
	Transform(FTransform::Identity),
	// ICsPayload_WidgetActorUserWidget
	UserWidgetPooledType(),
	UserWidgetPayload(nullptr)
{
	InterfaceMap = new FCsInterfaceMap();

	InterfaceMap->SetRootName(FCsPayload_WidgetActorImpl::Name);

	InterfaceMap->Add<ICsPayload_PooledObject>(static_cast<ICsPayload_PooledObject*>(this));
	InterfaceMap->Add<ICsPayload_WidgetActor>(static_cast<ICsPayload_WidgetActor*>(this));
	InterfaceMap->Add<ICsPayload_WidgetActorUserWidget>(static_cast<ICsPayload_WidgetActorUserWidget*>(this));
}

FCsPayload_WidgetActorImpl::~FCsPayload_WidgetActorImpl()
{
	delete InterfaceMap;
}

// ICsPayload_PooledObject
#pragma region

void FCsPayload_WidgetActorImpl::Reset()
{
	// ICsPayload_PooledObject
	bAllocated = false;
	Instigator = nullptr;
	Owner = nullptr;
	Parent = nullptr;

	Time.Reset();

	// ICsPayload_WidgetActor
	UserWidget = nullptr;
	DeallocateMethod = ECsWidgetActorDeallocateMethod::Complete;
	LifeTime = 0.0f;
	AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
	Bone = NAME_None;
	TransformRules = 0;
	Transform = FTransform::Identity;

	// ICsPayload_WidgetActorUserWidget
	UserWidgetPooledType = EMCsUserWidgetPooled::Get().GetMAX();
	UserWidgetPayload = nullptr;
}

#pragma endregion ICsPayload_PooledObject