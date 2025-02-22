// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

// Types
#include "CsMacro_Interface.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Container
#include "Containers/CsInterfaceMap.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsPayload_SoundImpl)

using PayloadType = NCsSound::NPayload::NImpl::FImpl;

void FCsPayload_Sound::CopyToPayloadAsValueChecked(const FString& Context, UObject* WorldContext, PayloadType* Payload) const
{
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

CS_STRUCT_DEFINE_STATIC_CONST_FNAME(NCsSound::NPayload::NImpl::FImpl);

namespace NCsSound
{
	namespace NPayload
	{
		namespace NImpl
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
				// PayloadType (NCsSound::NPayload::IPayload)
				Sound(nullptr),
				SoundAttenuation(nullptr),
				DeallocateMethod(EDeallocateMethod::Complete),
				LifeTime(0.0f),
				DurationMultiplier(1.0f),
				FadeInTime(0.0f),
				AttachmentTransformRules(FAttachmentTransformRules::SnapToTargetNotIncludingScale),
				Bone(NAME_None),
				TransformRules(0),
				Transform(FTransform::Identity),
				VolumeMultiplier(1.0f),
				PitchMultiplier(1.0f)
			{
				InterfaceMap = new FCsInterfaceMap();

				CS_INTERFACE_MAP_SET_ROOT(FImpl);

				CS_INTERFACE_MAP_ADD(PooledPayloadType);
				CS_INTERFACE_MAP_ADD(PayloadType);
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
				Transform = FTransform::Identity;
				VolumeMultiplier = 1.0f;
				PitchMultiplier = 1.0f;
			}

			#pragma endregion PooledPayloadType (NCsPooledObject::NPayload::IPayload)
		}
	}
}