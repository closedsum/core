// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsWidgetActor::NPayload::FImpl::Name = FName("NCsWidgetActor::NPayload::FImpl");;

namespace NCsWidgetActor
{
	namespace NPayload
	{ 
		FImpl::FImpl() :
			// ICsGetInterfaceMap
			InterfaceMap(nullptr),
			// NCsPooledObject::NPayload::IPayload
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// NCsWidgetActor::NPayload::IPayload
			UserWidget(nullptr),
			DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity),
			// NCsWidgetActor::NPayload::IUserWidget
			UserWidgetPooledType(),
			UserWidgetPayload(nullptr)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsWidgetActor::NPayload::IPayload WidgetPayloadType;
			typedef NCsWidgetActor::NPayload::IUserWidget UserWidgetType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<WidgetPayloadType>(static_cast<WidgetPayloadType*>(this));
			InterfaceMap->Add<UserWidgetType>(static_cast<UserWidgetType*>(this));
		}

		FImpl::~FImpl()
		{
			delete InterfaceMap;
		}

		// NCsPooledObject::NPayload::IPayload
		#pragma region

		void FImpl::Reset()
		{
			// NCsPooledObject::NPayload::IPayload
			bAllocated = false;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();

			PreserveChangesFromDefaultMask = 0;

			// NCsWidgetActor::NPayload::IPayload
			UserWidget = nullptr;
			DeallocateMethod = ECsWidgetActorDeallocateMethod::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;

			// NCsWidgetActor::NPayload::IUserWidget
			UserWidgetPooledType = EMCsUserWidgetPooled::Get().GetMAX();
			UserWidgetPayload = nullptr;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}