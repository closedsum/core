// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"

// Library
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// StaticMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NPayload::FLibrary, SetSafe);
				}
			}
		}

		#define PayloadType NCsStaticMeshActor::NPayload::IPayload
		bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
		{
		#undef PayloadType

			// Check StaticMesh is Valid
			checkf(Payload->GetStaticMesh(), TEXT("%s: GetStaticMesh() is NULL."), *Context);
			return true;
		}

		#define PayloadImplType NCsStaticMeshActor::NPayload::FImpl
		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload)
		{
			Payload->Instigator						= PooledPayload->GetInstigator();
			Payload->Owner							= PooledPayload->GetOwner();
			Payload->Parent							= PooledPayload->GetParent();
			Payload->Time							= PooledPayload->GetTime();
			Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
		}

		void FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			CS_IS_PTR_NULL_CHECKED(Payload)

			CS_IS_PTR_NULL_CHECKED(PooledPayload)

			SetChecked(Context, Payload, PooledPayload);
		}

		void FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload)
		{
			using namespace NCsStaticMeshActor::NPayload::NLibrary::NCached;

			const FString& Context = Str::SetSafe;

			SetSafe(Context, Payload, PooledPayload, nullptr);
		}

		#undef PayloadImplType
		#undef PooledPayloadType
	}
}