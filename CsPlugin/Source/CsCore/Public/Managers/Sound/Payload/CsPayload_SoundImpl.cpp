// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

#include "Containers/CsInterfaceMap.h"

const FName NCsSound::NPayload::FImpl::Name = FName("NCsSound::NPayload::FImpl");;

namespace NCsSound
{
	namespace NPayload
	{
		FImpl::FImpl() :
			InterfaceMap(nullptr),
			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			bAllocated(false),
			UpdateType(NCsPooledObject::EUpdate::Manager),
			Instigator(nullptr),
			Owner(nullptr),
			Parent(nullptr),
			Time(),
			// SoundPayloadType (NCsSound::NPayload::IPayload)
			Sound(nullptr),
			SoundAttenuation(nullptr),
			DeallocateMethod(EDeallocateMethod::Complete),
			LifeTime(0.0f),
			DurationMultiplier(1.0f),
			AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform::Identity),
			VolumeMultiplier(1.0f),
			PitchMultiplier(1.0f)
		{
			InterfaceMap = new FCsInterfaceMap();

			InterfaceMap->SetRoot<FImpl>(this);

			typedef NCsPooledObject::NPayload::IPayload PooledPayloadType;
			typedef NCsSound::NPayload::IPayload SoundPayloadType;

			InterfaceMap->Add<PooledPayloadType>(static_cast<PooledPayloadType*>(this));
			InterfaceMap->Add<SoundPayloadType>(static_cast<SoundPayloadType*>(this));
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

			// SoundPayloadType (NCsSound::NPayload::IPayload)
			Sound = nullptr;
			SoundAttenuation = nullptr;
			DeallocateMethod = EDeallocateMethod::Complete;
			LifeTime = 0.0f;
			DurationMultiplier = 1.0f;
			AttachmentTransformRules = ECsAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform::Identity;
			VolumeMultiplier = 1.0f;
			PitchMultiplier = 1.0f;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}