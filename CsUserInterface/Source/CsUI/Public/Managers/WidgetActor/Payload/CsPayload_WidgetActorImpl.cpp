// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/WidgetActor/Payload/CsPayload_WidgetActorImpl.h"

// Types
#include "CsMacro_Interface.h"
// Container
#include "Containers/CsInterfaceMap.h"

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsWidgetActor::NPayload::NImpl::FImpl);

namespace NCsWidgetActor
{
	namespace NPayload
	{
		namespace NImpl
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
}