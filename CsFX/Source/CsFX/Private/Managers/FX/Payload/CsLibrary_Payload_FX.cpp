// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/FX/Payload/CsLibrary_Payload_FX.h"

// Library
#include "Managers/FX/Params/CsLibrary_Params_FX.h"
#include "Library/CsLibrary_Valid.h"
// Types
#include "CsMacro_Misc.h"
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

			using LogClassType = NCsFX::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			using DeallocateMethodMapType = NCsFX::EMDeallocateMethod;
			using DeallocateMethodType = NCsFX::EDeallocateMethod;
			using ParameterType = NCsFX::NParameter::IParameter;

			bool FLibrary::IsValidChecked(const FString& Context, CsFXPayloadType* Payload)
			{
				CS_IS_PTR_NULL_CHECKED(Payload)
				// Check FX System is Valid.
				checkf(Payload->GetFXSystem(), TEXT("%s: FX System is NULL."), *Context);

				CS_IS_ENUM_VALID_CHECKED(DeallocateMethodMapType, Payload->GetDeallocateMethod());
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Payload->GetLifeTime(), 0.0f)

				if (Payload->GetDeallocateMethod() == DeallocateMethodType::LifeTime)
				{
					CS_IS_FLOAT_GREATER_THAN_CHECKED(Payload->GetLifeTime(), 0.0f)
				}
				// Check DeathTime is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL_CHECKED(Payload->GetDeathTime(), 0.0f)
				// Check bAbsoluteLocation
				if (Payload->GetbAbsoluteLocation())
				{
					checkf(Payload->GetAttachmentTransformRule().LocationRule == EAttachmentRule::KeepWorld, TEXT("%s: If GetbAbsoluteLocation() == TRUE, then GetAttachmentTransformRule().LocationRule  MUST = EAttachmentRule::KeepWorld."), *Context);
				}
				// Check bAbsoluteRotation
				if (Payload->GetbAbsoluteRotation())
				{
					checkf(Payload->GetAttachmentTransformRule().RotationRule == EAttachmentRule::KeepWorld, TEXT("%s: If GetbAbsoluteRotation() == TRUE, then GetAttachmentTransformRule().RotationRule  MUST = EAttachmentRule::KeepWorld."), *Context);
				}
				// Check bAbsoluteScale
				if (Payload->GetbAbsoluteScale())
				{
					checkf(Payload->GetAttachmentTransformRule().ScaleRule == EAttachmentRule::KeepWorld, TEXT("%s: If GetbAbsoluteScale() == TRUE, then GetAttachmentTransformRule().ScaleRule  MUST = EAttachmentRule::KeepWorld."), *Context);
				}
				// Check Parameters are Valid.
				const TArray<ParameterType*>& Parameters = Payload->GetParameters();

				if (Parameters.Num() > CS_EMPTY)
				{
					for (ParameterType* Param : Parameters)
					{
						check(CsFXParameterLibrary::IsValidChecked(Context, Param));
					}
				}
				return true;
			}

			bool FLibrary::IsValid(const FString& Context, PayloadType* Payload, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL(Payload)
				// Check FX System is Valid.
				if (!Payload->GetFXSystem())
				{
					CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get FX System from Payload."), *Context));
					return false;
				}

				CS_IS_ENUM_VALID(DeallocateMethodMapType, DeallocateMethodType, Payload->GetDeallocateMethod())
				// Check LifeTime is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Payload->GetLifeTime(), 0.0f)

				if (Payload->GetDeallocateMethod() == DeallocateMethodType::LifeTime)
				{
					CS_IS_FLOAT_GREATER_THAN(Payload->GetLifeTime(), 0.0f)
				}
				// Check DeathTime is Valid
				CS_IS_FLOAT_GREATER_THAN_OR_EQUAL(Payload->GetDeathTime(), 0.0f)
				// Check bAbsoluteLocation
				if (Payload->GetbAbsoluteLocation())
				{
					if (Payload->GetAttachmentTransformRule().LocationRule != EAttachmentRule::KeepWorld)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If GetbAbsoluteLocation() == TRUE, then LocationRule MUST = EAttachmentRule::KeepWorld."), *Context));
						return false;
					}
				}
				// Check bAbsoluteRotation
				if (Payload->GetbAbsoluteRotation())
				{
					if (Payload->GetAttachmentTransformRule().RotationRule != EAttachmentRule::KeepWorld)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If GetbAbsoluteRotation() == TRUE, then RotationRule MUST = EAttachmentRule::KeepWorld."), *Context));
						return false;
					}
				}
				// Check bAbsoluteScale
				if (Payload->GetbAbsoluteScale())
				{
					if (Payload->GetAttachmentTransformRule().ScaleRule != EAttachmentRule::KeepWorld)
					{
						CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If GetbAbsoluteScale() == TRUE, then ScaleRule MUST = EAttachmentRule::KeepWorld."), *Context));
						return false;
					}
				}
				// Check Parameters are Valid
				const TArray<ParameterType*>& Parameters = Payload->GetParameters();

				if (Parameters.Num() > CS_EMPTY)
				{
					for (ParameterType* Param : Parameters)
					{
						if (!CsFXParameterLibrary::IsValid(Context, Param, Log))
							return false;
					}
				}
				return true;
			}

			void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/)
			{
				CS_IS_PTR_NULL_CHECKED(Payload)
				CS_IS_VALID_CHECKED(FX);

				Payload->FXSystem				  = FX.GetChecked(Context);
				Payload->DeallocateMethod		  = FX.GetDeallocateMethod();
				Payload->LifeTime				  = FX.LifeTime;
				Payload->DeathTime				  = FX.DeathTime;
				Payload->bHideOnQueueDeallocate	  = FX.bHideOnQueueDeallocate;
				Payload->AttachmentTransformRules = FX.AttachmentTransformRules;
				Payload->Bone					  = FX.Bone;
				Payload->TransformRules			  = FX.TransformRules;

				Payload->Transform.SetTranslation(Transform.GetTranslation() + FX.Transform.GetTranslation());

				FRotator3f Rotation = Transform.GetRotation().Rotator() + FX.Transform.GetRotation().Rotator();

				Payload->Transform.SetRotation(Rotation.Quaternion());
				Payload->Transform.SetScale3D(Transform.GetScale3D() * FX.Transform.GetScale3D());

				Payload->bAbsoluteLocation    = FX.AttachmentTransformRules.bAbsoluteLocation;
				Payload->bAbsoluteRotation	  = FX.AttachmentTransformRules.bAbsoluteRotation;
				Payload->bAbsoluteScale		  = FX.AttachmentTransformRules.bAbsoluteScale;
				Payload->bApplyTransformScale = FX.bApplyTransformScale;
			}

			void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL_EXIT(Payload)
				CS_IS_VALID_EXIT(FX);

				SetChecked(Context, Payload, FX, Transform);
			}

			void FLibrary::SetSafe(PayloadImplType* Payload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/)
			{
				using namespace NCsFX::NPayload::NLibrary::NCached;

				const FString& Context = Str::SetSafe;

				SetSafe(Context, Payload, FX, Transform, nullptr);
			}

			void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, const FTransform3f& Transform)
			{
				// NOTE: For now only PayloadImplType (PayloadImplType NCsFX::NPayload::FImpl) is supported
				PayloadImplType* PayloadImpl = StaticCastChecked<PayloadImplType>(Context, Payload);

				PayloadImpl->Transform = Transform;
			}

			void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/)
			{
				SetChecked(Context, Payload, FX, Transform);
				SetChecked(Context, Payload, PooledPayload);
			}

			void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL_EXIT(Payload)
				CS_IS_PTR_NULL_EXIT(PooledPayload)
				CS_IS_VALID_EXIT(FX)

				SetChecked(Context, Payload, PooledPayload, FX, Transform);
			}

			void FLibrary::SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/)
			{
				using namespace NCsFX::NPayload::NLibrary::NCached;

				const FString& Context = Str::SetSafe;

				SetSafe(Context, Payload, PooledPayload, FX, Transform, nullptr);
			}

			void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsFX& FX, const FTransform3f& Transform /*=FTransform3f::Identity*/)
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

			void FLibrary::ApplyAsOffsetChecked(const FString& Context, PayloadType* Payload, const FTransform3f& Transform)
			{
				// NOTE: For now only PayloadImplType (PayloadImplType NCsFX::NPayload::FImpl) is supported
				PayloadImplType* PayloadImpl = StaticCastChecked<PayloadImplType>(Context, Payload);

				PayloadImpl->Transform.SetTranslation(Transform.GetTranslation() + PayloadImpl->Transform.GetTranslation());

				FRotator3f Rotation = Transform.GetRotation().Rotator() + PayloadImpl->Transform.GetRotation().Rotator();

				PayloadImpl->Transform.SetRotation(Rotation.Quaternion());

				PayloadImpl->Transform.SetRotation(Transform.GetRotation() + PayloadImpl->Transform.GetRotation());
				PayloadImpl->Transform.SetScale3D(Transform.GetScale3D() * PayloadImpl->Transform.GetScale3D());
			}
		}
	}
}