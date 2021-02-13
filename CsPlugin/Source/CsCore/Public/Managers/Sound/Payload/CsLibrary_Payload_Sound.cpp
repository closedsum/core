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


		#define PayloadImplType NCsSound::NPayload::FImpl
		void FLibrary::SetPayload(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound)
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
	}
}