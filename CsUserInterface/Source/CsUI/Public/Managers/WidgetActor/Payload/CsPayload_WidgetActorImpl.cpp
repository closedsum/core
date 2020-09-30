// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
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

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsWidgetActor::NPayload::IPayload>(static_cast<NCsWidgetActor::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsWidgetActor::NPayload::IUserWidget>(static_cast<NCsWidgetActor::NPayload::IUserWidget*>(this));
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