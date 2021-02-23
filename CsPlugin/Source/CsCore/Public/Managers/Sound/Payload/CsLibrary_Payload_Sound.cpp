// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"

// Types
#include "Managers/Sound/CsTypes_Sound.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

namespace NCsSound
{
	namespace NPayload
	{
		#define PayloadType NCsSound::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		#undef PayloadType
			
			// Check Sound is Valid
			checkf(Payload->GetSound(), TEXT("%s: Sound is NULL."), *Context);

			return true;
		}
		
		#define PayloadType NCsSound::NPayload::IPayload
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FLibrary::Set(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound)
		{
		#undef PayloadType
		#undef PooledPayloadType

			typedef NCsSound::NPayload::FImpl PayloadImplType;

			if (PayloadImplType* PayloadImpl = SafeStaticCastChecked<PayloadImplType>(Context, Payload))
			{
				Set(Context, PayloadImpl, PooledPayload, Sound);
			}
			else
			{
				checkf(0, TEXT("%s: Unsupported Payload Type."), *Context);
			}
		}
		
		#define PayloadType NCsSound::NPayload::IPayload
		void FLibrary::Set(const FString& Context, PayloadType* Payload, const FCsSound& Sound)
		{
		#undef PayloadType

			typedef NCsSound::NPayload::FImpl PayloadImplType;

			if (PayloadImplType* PayloadImpl = SafeStaticCastChecked<PayloadImplType>(Context, Payload))
			{
				Set(Context, PayloadImpl, Sound);
			}
			else
			{
				checkf(0, TEXT("%s: Unsupported Paylaod Type."), *Context);
			}
		}
		
		#define PayloadImplType NCsSound::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FLibrary::Set(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound)
		{
		#undef PayloadImplType
		#undef PooledPayloadType

			checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

			checkf(PooledPayload, TEXT("%s: PooledPayload is NULL."), *Context);

			// PooledPayloadType (NCsPooledObject::NPayload::IPayload)
			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();

			// PayloadType (NCsSound::NPayload::IPayload)
			Payload->Sound					  = Sound.GetChecked(Context);
			Payload->SoundAttenuation		  = Sound.GetAttenuation();
			Payload->DeallocateMethod		  = Sound.GetDeallocateMethod();
			Payload->LifeTime				  = Sound.LifeTime;
			Payload->AttachmentTransformRules = Sound.AttachmentTransformRules;
			Payload->Bone					  = Sound.Bone;
			Payload->TransformRules			  = Sound.TransformRules;
			Payload->Transform				  = Sound.Transform;
		}
		
		#define PayloadImplType NCsSound::NPayload::FImpl
		void FLibrary::Set(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound)
		{
		#undef PayloadImplType

			checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

			Payload->Sound					  = Sound.GetChecked(Context);
			Payload->SoundAttenuation		  = Sound.GetAttenuation();
			Payload->DeallocateMethod		  = Sound.GetDeallocateMethod();
			Payload->LifeTime				  = Sound.LifeTime;
			Payload->AttachmentTransformRules = Sound.AttachmentTransformRules;
			Payload->Bone					  = Sound.Bone;
			Payload->TransformRules			  = Sound.TransformRules;
			Payload->Transform				  = Sound.Transform;
		}

		#define PayloadImplType NCsSound::NPayload::FImpl
		void FLibrary::Set(const FString& Context, PayloadImplType* Payload, USoundBase* Sound)
		{
		#undef PayloadImplType

			checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

			checkf(Sound, TEXT("%s: Sound is NULL."), *Context);

			Payload->Sound = Sound;

			typedef NCsSound::EDeallocateMethod DeallocateMethodType;

			Payload->DeallocateMethod = DeallocateMethodType::Complete;
		}
	}
}