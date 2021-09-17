// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

// Managers
#include "Managers/FX/Actor/CsManager_FX_Actor.h"
// Containers
#include "Containers/CsInterfaceMap.h"

const FName NCsFX::NPayload::FImpl::Name = FName("NCsFX::NPayload::FImpl");;

namespace NCsFX
{
	namespace NPayload
	{
		#define DeallocateMethodType NCsFX::EDeallocateMethod

		FImpl::FImpl() :
			Root(nullptr),
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
			// FXPayloadType (NCsFX::Payload::IPayload)
			FXSystem(nullptr),
			DeallocateMethod(DeallocateMethodType::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity),
			Parameters()
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsFX::NPayload::IPayload FXPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<FXPayloadType>(static_cast<FXPayloadType*>(this));
		}

		#undef DeallocateMethodType

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

			// FXPayloadType (NCsFX::NPayload::IPayload)
			typedef NCsFX::EDeallocateMethod DeallocateMethodType;

			FXSystem = nullptr;
			DeallocateMethod = DeallocateMethodType::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;

			UCsManager_FX_Actor* Manager_FX = UCsManager_FX_Actor::Get(Root);

			typedef NCsFX::NParameter::IParameter ParameterType;

			for (ParameterType* Param : Parameters)
			{
				Manager_FX->DeallocateValue(Param);
			}
			Parameters.Reset(Parameters.Max());
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}