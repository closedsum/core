// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsSound::NPayload::FImpl::Name = FName("NCsSound::NPayload::FImpl");;

namespace NCsSound
{
	namespace NPayload
	{
		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// NCsPooledObject::NPayload::IPayload
			bAllocated(false),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// NCsSound::NPayload::IPayload
			Sound(nullptr),
			SoundAttenuation(nullptr),
			DeallocateMethod(ECsSoundDeallocateMethod::Complete),
			LifeTime(0.0f),
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRootName(FImpl::Name);

			InterfaceMap->Add<NCsPooledObject::NPayload::IPayload>(static_cast<NCsPooledObject::NPayload::IPayload*>(this));
			InterfaceMap->Add<NCsSound::NPayload::IPayload>(static_cast<NCsSound::NPayload::IPayload*>(this));
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

			// NCsSound::NPayload::IPayload
			Sound = nullptr;
			SoundAttenuation = nullptr;
			DeallocateMethod = ECsSoundDeallocateMethod::Complete;
			LifeTime = 0.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;
		}

		#pragma endregion NCsPooledObject::NPayload::IPayload
	}
}