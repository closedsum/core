// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"

// Types
#include "Managers/FX/CsTypes_FX.h"
// FX
#include "Managers/FX/Payload/CsPayload_FXImpl.h"

namespace NCsFX
{
	namespace NPayload
	{
		#define PayloadType NCsFX::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		#undef PayloadType

			// Check FX System is Valid.
			checkf(Payload->GetFXSystem(), TEXT("%s: FX System is NULL."), *Context);

			return true;
		}

		#define PayloadImplType NCsFX::NPayload::FImpl
		void FLibrary::SetPayload(const FString& Context, PayloadImplType* Payload, const FCsFX& FX)
		{
		#undef PayloadImplType

			checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

			Payload->FXSystem				  = FX.GetChecked(Context);
			Payload->DeallocateMethod		  = FX.GetDeallocateMethod();
			Payload->LifeTime				  = FX.LifeTime;
			Payload->AttachmentTransformRules = FX.AttachmentTransformRules;
			Payload->Bone					  = FX.Bone;
			Payload->TransformRules			  = FX.TransformRules;
			Payload->Transform				  = FX.Transform;
		}
	}
}