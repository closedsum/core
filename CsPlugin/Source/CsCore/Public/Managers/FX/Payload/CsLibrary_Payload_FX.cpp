// Copyright 2017-2021 Closed Sum Games, LLC. All Rights Reserved.
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

		#define PayloadImplType NCsFX::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			CS_IS_VALID_CHECKED(FX);

			Payload->FXSystem				  = FX.GetChecked(Context);
			Payload->DeallocateMethod		  = FX.GetDeallocateMethod();
			Payload->LifeTime				  = FX.LifeTime;
			Payload->AttachmentTransformRules = FX.AttachmentTransformRules;
			Payload->Bone					  = FX.Bone;
			Payload->TransformRules			  = FX.TransformRules;

			Payload->Transform.SetTranslation(Transform.GetTranslation() + FX.Transform.GetTranslation());
			Payload->Transform.SetRotation(Transform.GetRotation() + FX.Transform.GetRotation());
			Payload->Transform.SetScale3D(Transform.GetScale3D() * FX.Transform.GetScale3D());
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			CS_IS_VALID_EXIT(FX);

			SetChecked(Context, Payload, FX, Transform);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			using namespace NCsFX::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, FX, Transform, nullptr);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, const FTransform& Transform)
		{
			// NOTE: For now only PayloadImplType (PayloadImplType NCsFX::NPayload::FImpl) is supported
			PayloadImplType* PayloadImpl = StaticCastChecked<PayloadImplType>(Context, Payload);

			PayloadImpl->Transform = Transform;
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			SetChecked(Context, Payload, FX, Transform);
			SetChecked(Context, Payload, PooledPayload);
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			CS_IS_PTR_NULL_EXIT(PooledPayload)

			CS_IS_VALID_EXIT(FX)

			SetChecked(Context, Payload, PooledPayload, FX, Transform);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			using namespace NCsFX::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, PooledPayload, FX, Transform, nullptr);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform& Transform /*=FTransform::Identity*/)
		{
			// NOTE: For now only PayloadImplType (PayloadImplType NCsFX::NPayload::FImpl) is supported
			PayloadImplType* PayloadImpl = StaticCastChecked<PayloadImplType>(Context, Payload);

			SetChecked(Context, PayloadImpl, PooledPayload, FX, Transform);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			CS_IS_PTR_NULL_CHECKED(PooledPayload)

			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
		}

		void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload)
		{
			// NOTE: For now only PayloadImplType (PayloadImplType NCsFX::NPayload::FImpl) is supported
			PayloadImplType* PayloadImpl = StaticCastChecked<PayloadImplType>(Context, Payload);

			SetChecked(Context, PayloadImpl, PooledPayload);
		}

		void FLibrary::ApplyAsOffsetChecked(const FString& Context, PayloadType* Payload, const FTransform& Transform)
		{
			// NOTE: For now only PayloadImplType (PayloadImplType NCsFX::NPayload::FImpl) is supported
			PayloadImplType* PayloadImpl = StaticCastChecked<PayloadImplType>(Context, Payload);

			PayloadImpl->Transform.SetTranslation(Transform.GetTranslation() + PayloadImpl->Transform.GetTranslation());
			PayloadImpl->Transform.SetRotation(Transform.GetRotation() + PayloadImpl->Transform.GetRotation());
			PayloadImpl->Transform.SetScale3D(Transform.GetScale3D() * PayloadImpl->Transform.GetScale3D());
		}

		#undef PayloadImplType
		#undef PooledPayloadType

		#undef PayloadType
	}
}