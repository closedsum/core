// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"

// Library
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
#include "Library/CsLibrary_Valid.h"
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
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsFX::NPayload::FLibrary, SetSafe);
				}
			}
		}

		#define PayloadType NCsFX::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
			// Check Payload is Valid
			CS_IS_PTR_NULL_CHECKED(Payload)
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

		bool FLibrary::IsValid(const FString& Context, PayloadType* Payload, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			// Check Payload is Valid
			CS_IS_PTR_NULL(Payload)
			// Check FX System is Valid.
			if (!Payload->GetFXSystem())
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get FX System from Payload."), *Context));
				return false;
			}
			// Check Parameters are Valid
			typedef NCsFX::NParameter::IParameter ParameterType;

			const TArray<ParameterType*>& Parameters = Payload->GetParameters();

			if (Parameters.Num() > CS_EMPTY)
			{
				typedef NCsFX::NParameter::FLibrary ParameterLibrary;

				for (ParameterType* Param : Parameters)
				{
					if (!ParameterLibrary::IsValid(Context, Param, Log))
						return false;
				}
			}
			return true;
		}

		#undef PayloadType

		#define PayloadImplType NCsFX::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX)
		{
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

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX)
		{
			SetChecked(Context, Payload, FX);

			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			if (!FX.IsValid(Context))
				return;

			SetChecked(Context, Payload, FX);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const FCsFX& FX)
		{
			using namespace NCsFX::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, FX, nullptr);
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			CS_IS_PTR_NULL_EXIT(PooledPayload)

			if (!FX.IsValid(Context))
				return;

			SetChecked(Context, Payload, PooledPayload, FX);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX)
		{
			using namespace NCsFX::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, PooledPayload, FX, nullptr);
		}

		#undef PayloadImplType
		#undef PooledPayloadType
	}
}