// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"

// Library
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
// Types
#include "Managers/FX/CsTypes_FX.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
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
			// Check Parameters are Valid.
			typedef NCsFX::NParameter::IParameter ParameterType;

			const TArray<ParameterType*>& Parameters = Payload->GetParameters();

			if (Parameters.Num() > CS_EMPTY)
			{
				typedef NCsFX::NParameter::FLibrary ParameterLibrary;

				for (ParameterType* Param : Parameters)
				{
					check(ParameterLibrary::IsValidChecked(Context, Param));
				}
			}
			return true;
		}

		#define PayloadImplType NCsFX::NPayload::FImpl
		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX)
		{
		#undef PayloadImplType

			checkf(Payload, TEXT("%s: Payload is NULL."), *Context);

			check(FX.IsValidChecked(Context));

			Payload->FXSystem				  = FX.GetChecked(Context);
			Payload->DeallocateMethod		  = FX.GetDeallocateMethod();
			Payload->LifeTime				  = FX.LifeTime;
			Payload->AttachmentTransformRules = FX.AttachmentTransformRules;
			Payload->Bone					  = FX.Bone;
			Payload->TransformRules			  = FX.TransformRules;
			Payload->Transform				  = FX.Transform;
		}

		#define PayloadImplType NCsFX::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload
		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX)
		{
		#undef PayloadImplType
		#undef PooledPayloadType

			SetChecked(Context, Payload, FX);

			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
		}
	}
}