// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/Sound/Payload/CsLibrary_Payload_Sound.h"

// Types
#include "Managers/Sound/CsTypes_Sound.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Sound
#include "Managers/Sound/Payload/CsPayload_SoundImpl.h"

namespace NCsSound
{
	namespace NPayload
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSound::NPayload::FLibrary, SetSafe);
				}
			}
		}

		#define PayloadType NCsSound::NPayload::IPayload

		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		
			
			// Check Payload is Valid
			CS_IS_PTR_NULL_CHECKED(Payload)
			// Check Sound is Valid
			checkf(Payload->GetSound(), TEXT("%s: Sound is NULL."), *Context);

			return true;
		}
		
		#undef PayloadType

		#define PayloadType NCsSound::NPayload::IPayload
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			typedef NCsSound::NPayload::FImpl PayloadImplType;

			if (PayloadImplType* PayloadImpl = SafeStaticCastChecked<PayloadImplType>(Context, Payload))
			{
				SetChecked(Context, PayloadImpl, PooledPayload, Sound, Transform);
			}
			else
			{
				checkf(0, TEXT("%s: Unsupported Payload Type."), *Context);
			}
		}
		
		void FLibrary::SetSafe(const FString& Context, PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			typedef NCsSound::NPayload::FImpl PayloadImplType;

			if (PayloadImplType* PayloadImpl = SafeStaticCastChecked<PayloadImplType>(Context, Payload))
			{
				SetChecked(Context, PayloadImpl, PooledPayload, Sound, Transform);
			}
			else
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Unsupported Payload Type."), *Context));
			}
		}

		void FLibrary::SetSafe(PayloadType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/)
		{
			using namespace NCsSound::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			return SetSafe(Context, Payload, PooledPayload, Sound, Transform, nullptr);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadType* Payload, const FCsSound& Sound)
		{
			typedef NCsSound::NPayload::FImpl PayloadImplType;

			if (PayloadImplType* PayloadImpl = SafeStaticCastChecked<PayloadImplType>(Context, Payload))
			{
				SetChecked(Context, PayloadImpl, Sound);
			}
			else
			{
				checkf(0, TEXT("%s: Unsupported Paylaod Type."), *Context);
			}
		}
		
		void FLibrary::SetSafe(const FString& Context, PayloadType* Payload, const FCsSound& Sound, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			typedef NCsSound::NPayload::FImpl PayloadImplType;

			if (PayloadImplType* PayloadImpl = SafeStaticCastChecked<PayloadImplType>(Context, Payload))
			{
				SetChecked(Context, PayloadImpl, Sound);
			}
			else
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Unsupported Payload Type."), *Context));
			}
		}

		void FLibrary::SetSafe(PayloadType* Payload, const FCsSound& Sound)
		{
			using namespace NCsSound::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			return SetSafe(Context, Payload, Sound, nullptr);
		}

		#define PayloadImplType NCsSound::NPayload::FImpl

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			CS_IS_PTR_NULL_CHECKED(PooledPayload)

			check(Sound.IsValidChecked(Context));

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

			Payload->Transform.SetTranslation(Transform.GetTranslation() + Sound.Transform.GetTranslation());
			Payload->Transform.SetRotation(Transform.GetRotation() + Sound.Transform.GetRotation());
			Payload->Transform.SetScale3D(Transform.GetScale3D() * Sound.Transform.GetScale3D());
		}
		
		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			CS_IS_PTR_NULL_EXIT(PooledPayload)

			if (!Sound.IsValid(Context, Log))
				return;

			SetChecked(Context, Payload, PooledPayload, Sound, Transform);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, PooledPayloadType* PooledPayload, const FCsSound& Sound, const FTransform& Transform /*=FTransform::Identity*/)
		{
			using namespace NCsSound::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			return SetSafe(Context, Payload, PooledPayload, Sound, Transform, nullptr);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			check(Sound.IsValidChecked(Context));

			Payload->Sound					  = Sound.GetChecked(Context);
			Payload->SoundAttenuation		  = Sound.GetAttenuation();
			Payload->DeallocateMethod		  = Sound.GetDeallocateMethod();
			Payload->LifeTime				  = Sound.LifeTime;
			Payload->AttachmentTransformRules = Sound.AttachmentTransformRules;
			Payload->Bone					  = Sound.Bone;
			Payload->TransformRules			  = Sound.TransformRules;
			Payload->Transform				  = Sound.Transform;
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const FCsSound& Sound, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			if (!Sound.IsValid(Context, Log))
				return;

			SetChecked(Context, Payload, Sound);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const FCsSound& Sound)
		{
			using namespace NCsSound::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			return SetSafe(Context, Payload, Sound, nullptr);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, USoundBase* Sound)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			CS_IS_PTR_NULL_CHECKED(Sound)

			Payload->Sound = Sound;

			typedef NCsSound::EDeallocateMethod DeallocateMethodType;

			Payload->DeallocateMethod = DeallocateMethodType::Complete;
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, USoundBase* Sound, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_EXIT(Payload)

			CS_IS_PTR_NULL_EXIT(Sound)

			Payload->Sound = Sound;

			typedef NCsSound::EDeallocateMethod DeallocateMethodType;

			Payload->DeallocateMethod = DeallocateMethodType::Complete;
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, USoundBase* Sound)
		{
			using namespace NCsSound::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			return SetSafe(Context, Payload, Sound, nullptr);
		}

		#undef PayloadImplType

		#undef PayloadType
		#undef PooledPayloadType
	}
}