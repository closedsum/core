// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			PreserveChangesFromDefaultMask(0),
			// WidgetPayloadType (NCsWidgetActor::NPayload::IPayload)
			UserWidget(nullptr),
			DeallocateMethod(ECsWidgetActorDeallocateMethod::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform3f::Identity),
			// UserWidgetPayloadType (NCsWidgetActor::NPayload::IUserWidget
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

		// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		#pragma region

		void FImpl::Reset()
		{
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated = false;
			UpdateType = NCsPooledObject::EUpdate::Manager;
			Instigator = nullptr;
			Owner = nullptr;
			Parent = nullptr;

			Time.Reset();

			PreserveChangesFromDefaultMask = 0;

			// WidgetPayloadType (NCsWidgetActor::NPayload::IPayload)
			UserWidget = nullptr;
			DeallocateMethod = ECsWidgetActorDeallocateMethod::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform3f::Identity;

			// UserWidgetType (NCsWidgetActor::NPayload::IUserWidget)
			UserWidgetPooledType = EMCsUserWidgetPooled::Get().GetMAX();
			UserWidgetPayload = nullptr;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}