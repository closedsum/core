// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPayload_SoundImpl)

#define PayloadType NCsSound::NPayload::FImpl
void FCsPayload_Sound::CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadType* Payload) const
{
#undef PayloadType
	
	Payload->Instigator = Instigator;
	Payload->Owner		= Owner;
	Payload->Parent		= Parent;
	Payload->Time		= Time;
	Payload->PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	typedef NCsSound::EDeallocateMethod DeallocateMethodType;

	Payload->Sound						= Sound.GetChecked(Context);
	Payload->SoundAttenuation			= Sound.GetAttenuation();
	Payload->DeallocateMethod			= (DeallocateMethodType)Sound.DeallocateMethod;
	Payload->LifeTime					= Sound.LifeTime;
	Payload->DurationMultiplier			= Sound.DurationMultiplier;
	Payload->FadeInTime					= Sound.FadeInTime;
	Payload->AttachmentTransformRules	= Sound.AttachmentTransformRules;
	Payload->Bone						= Sound.Bone;
	Payload->TransformRules				= Sound.TransformRules;
	Payload->Transform					= Sound.Transform;
	Payload->VolumeMultiplier			= VolumeMultiplier;
	Payload->PitchMultiplier		    = PitchMultiplier;
}

bool FCsPayload_Sound::IsValidChecked(const FString& Context) const
{
	CS_IS_VALID_CHECKED(Sound);
	return true;
}

bool FCsPayload_Sound::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	CS_IS_VALID(Sound)
	return true;
}

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
			FadeInTime(0.0f),
			AttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
			Bone(NAME_None),
			TransformRules(0),
			Transform(FTransform3f::Identity),
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
			FadeInTime = 0.0f;
			AttachmentTransformRules = FAttachmentTransformRules::SnapToTargetNotIncludingScale;
			Bone = NAME_None;
			TransformRules = 0;
			Transform = FTransform3f::Identity;
			VolumeMultiplier = 1.0f;
			PitchMultiplier = 1.0f;
		}

		#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
	}
}