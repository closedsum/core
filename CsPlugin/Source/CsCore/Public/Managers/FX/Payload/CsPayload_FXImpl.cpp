// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsFX::NPayload::FImpl::Name = FName("NCsFX::NPayload::FImpl");;

namespace NCsFX
{
	namespace NPayload
	{
		FImpl::FImpl() :
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

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsFX::NPayload::IPayload>(static_cast<NCsFX::NPayload::IPayload*>(this));
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

			// NCsFX::NPayload::IPayload
			FXSystem = nullptr;
			DeallocateMethod = ECsFXDeallocateMethod::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}