// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/SkeletalMesh/CsLibrary_Manager_SkeletalMeshActor.h"

// Managers
#include "Managers/SkeletalMesh/CsManager_SkeletalMeshActor.h"
// Library
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

#if WITH_EDITOR
// Library
	// Common
#include "Game/CsLibrary_GameState.h"
#include "Library/CsLibrary_World.h"
// Managers
#include "Managers/Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

namespace NCsSkeletalMeshActor
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NManager::FLibrary, GetSafe);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsSkeletalMeshActor::NManager::FLibrary, SafeSpawn);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsSkeletalMesh::FLog::Warning*/
		#define WorldLibrary NCsWorld::FLibrary
		#define GameStateLibrary NCsGameState::FLibrary

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}
			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafeContextRoot);

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_SkeletalMeshActor* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
		#if UE_BUILD_SHIPPING
			return UCsManager_SkeletalMeshActor::Get(nullptr);
		#else
			UObject* ContextRoot									= GetContextRootChecked(Context, WorldContext);
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = UCsManager_SkeletalMeshActor::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_SkeletalMeshActor)
			return Manager_SkeletalMeshActor;
		#endif // #if UE_BUILD_SHIPPING
		}

		UCsManager_SkeletalMeshActor* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = UCsManager_SkeletalMeshActor::Get(ContextRoot);

			if (!Manager_SkeletalMeshActor)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_SkeletalMeshActor."), *Context));
			}
			return Manager_SkeletalMeshActor;
		}

		UCsManager_SkeletalMeshActor* FLibrary::GetSafe(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Payload
		#pragma region

		#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload
		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsSkeletalMeshActor& Type)
		{
		#undef PayloadType

			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}

		#pragma endregion Payload

		// Spawn
		#pragma region

		#define PayloadType NCsSkeletalMeshActor::NPayload::IPayload

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsSkeletalMeshActor& Type, PayloadType* Payload)
		{
			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform3f& Transform /*=FTransform3f::Identity*/)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetChecked(Context, WorldContext);

			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_SkeletalMeshActor->AllocatePayload<PayloadImplType>(Shot.GetType());

			checkf(Transform.GetScale3D() != FVector3f::ZeroVector, TEXT("%s: Transform.GetScale3D() == FVector3f::ZeroVector is NOT Valid."), *Context);

			Payload->Transform = Transform;
			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Shot);

			return Manager_SkeletalMeshActor->Spawn(Shot.GetType(), Payload);
			
			return nullptr;
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform3f& Transform /*=FTransform3f::Identity*/, LogLevel)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetSafe(Context, WorldContext, Log);

			if (!Manager_SkeletalMeshActor)
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Shot.IsValid(Context))
				return nullptr;

			if (Transform.GetScale3D() == FVector3f::ZeroVector)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Transform.GetScale3D() == FVector3f::ZeroVector is NOT Valid."), *Context));
				return nullptr;
			}
			return SpawnChecked(Context, WorldContext, PooledPayload, Shot, Transform);
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			SET_CONTEXT(SafeSpawn);

			return SafeSpawn(Context, WorldContext, PooledPayload, Shot, FTransform3f::Identity, nullptr);
		}

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform3f& Transform /*=FTransform3f::Identity*/)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetChecked(Context, WorldContext);
			// Allocate Payload
			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_SkeletalMeshActor->AllocatePayload<PayloadImplType>(Shot.GetType());
			
			// Set Payload
			checkf(Transform.GetScale3D() != FVector3f::ZeroVector, TEXT("%s: Transform.GetScale3D() == FVector3f::ZeroVector is NOT Valid."), *Context);

			Payload->Transform = Transform;
			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Shot);

			return Manager_SkeletalMeshActor->Spawn(Shot.GetType(), Payload);
			
			return nullptr;
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform3f& Transform /*=FTransform3f::Identity*/, LogLevel)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetSafe(Context, WorldContext, Log);

			if (!Manager_SkeletalMeshActor)
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Shot.IsValid(Context))
				return nullptr;

			if (Transform.GetScale3D() == FVector3f::ZeroVector)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Transform.GetScale3D() == FVector3f::ZeroVector is NOT Valid."), *Context));
				return nullptr;
			}
			return SpawnChecked(Context, WorldContext, PooledPayload, Shot, Transform);
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			SET_CONTEXT(SafeSpawn);

			return SafeSpawn(Context, WorldContext, PooledPayload, Shot, FTransform3f::Identity, nullptr);
		}

		#undef ShotType

		#undef PooledPayloadType

		#undef PayloadType

		#pragma endregion Spawn

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
		#undef WorldLibrary
		#undef GameStateLibrary
	}
}