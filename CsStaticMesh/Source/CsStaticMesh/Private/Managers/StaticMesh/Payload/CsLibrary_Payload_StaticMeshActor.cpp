// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"

// Types
#include "CsMacro_Misc.h"
// Library
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObject.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

CS_START_CACHED_FUNCTION_NAME_NESTED_3(NCsStaticMeshActor, NPayload, NLibrary, Library)
	CS_DEFINE_CACHED_FUNCTION_NAME(NCsStaticMeshActor::NPayload::NLibrary::FLibrary, SetSafe)
CS_END_CACHED_FUNCTION_NAME_NESTED_3

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		namespace NLibrary
		{
			using LogClassType = NCsCore::NLibrary::FLog;

			CS_DEFINE_STATIC_LOG_LEVEL(FLibrary, LogClassType::Warning);

			using PayloadImplType = NCsStaticMeshActor::NPayload::NImpl::FImpl;
			using PooledPayloadType = NCsPooledObject::NPayload::IPayload;

			bool FLibrary::IsValidChecked(const FString& Context, PayloadType* Payload)
			{
				checkf(Payload->GetStaticMesh(), TEXT("%s: GetStaticMesh() is NULL."), *Context);
				return true;
			}

			void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload)
			{
				Payload->Instigator						= PooledPayload->GetInstigator();
				Payload->Owner							= PooledPayload->GetOwner();
				Payload->Parent							= PooledPayload->GetParent();
				Payload->Time							= PooledPayload->GetTime();
				Payload->PreserveChangesFromDefaultMask = PooledPayload->GetPreserveChangesFromDefaultMask();
			}

			bool FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				CS_IS_PTR_NULL(Payload)
				CS_IS_PTR_NULL(PooledPayload)

				SetChecked(Context, Payload, PooledPayload);
				return true;
			}

			bool FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(SetSafe);

				return SetSafe(Context, Payload, PooledPayload, nullptr);
			}

			void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info)
			{
				SetChecked(Context, Payload, PooledPayload);
				Info.SetPayloadChecked(Context, Payload);
			}

			bool FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, CS_FN_PARAM_DEFAULT_LOG_LEVEL_COMMENT)
			{
				if (!SetSafe(Context, Payload, PooledPayload))
					return false;
				return Info.SetSafePayload(Context, Payload, Log);
			}

			bool FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info)
			{
				CS_SET_CONTEXT_AS_FUNCTION_NAME(SetSafe);

				return SetSafe(Context, Payload, PooledPayload, Info, nullptr);
			}
		}
	}
}