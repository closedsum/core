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

		#define USING_NS_CACHED using namespace NCsStaticMeshActor::NPayload::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsStaticMeshActor::NPayload::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsStaticMesh::FLog::Warning*/

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

		bool FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, LogLevel)
		{
			CS_IS_PTR_NULL(Payload)
			CS_IS_PTR_NULL(PooledPayload)

			SetChecked(Context, Payload, PooledPayload);
			return true;
		}

		bool FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload)
		{
			SET_CONTEXT(SetSafe);

			return SetSafe(Context, Payload, PooledPayload, nullptr);
		}

		void FLibrary::SetChecked(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info)
		{
			SetChecked(Context, Payload, PooledPayload);
			Info.SetPayloadChecked(Context, Payload);
		}

		bool FLibrary::SetSafe(const FString& Context, PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, LogLevel)
		{
			if (!SetSafe(Context, Payload, PooledPayload))
				return false;

			return Info.SetSafePayload(Context, Payload, Log);
		}

		bool FLibrary::SetSafe(PayloadImplType* Payload, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info)
		{
			SET_CONTEXT(SetSafe);

			return SetSafe(Context, Payload, PooledPayload, Info, nullptr);
		}

		#undef PayloadImplType
		#undef PooledPayloadType

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
	}
}