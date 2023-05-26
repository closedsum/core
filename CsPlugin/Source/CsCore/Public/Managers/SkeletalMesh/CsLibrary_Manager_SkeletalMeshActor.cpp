// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
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

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}

			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			typedef NCsWorld::FLibrary WorldLibrary;

			if (WorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				if (const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST(WorldContext, UObject, ICsGetManagerSingleton))
				{
					return GetManagerSingleton->_getUObject();
				}
				return nullptr;
			}

			typedef NCsGameState::FLibrary GameStateLibrary;

			return GameStateLibrary::GetSafeAsObject(Context, WorldContext, Log);
		}

		UObject* FLibrary::GetSafeContextRoot(const UObject* WorldContext)
		{
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafeContextRoot;

			return GetSafeContextRoot(Context, WorldContext, nullptr);
		}

		#endif // #if WITH_EDITOR

		#pragma endregion ContextRoot

		// Get
		#pragma region

		UCsManager_SkeletalMeshActor* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
			UObject* ContextRoot									= GetContextRootChecked(Context, WorldContext);
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = UCsManager_SkeletalMeshActor::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_SkeletalMeshActor)
			return Manager_SkeletalMeshActor;
		}

		UCsManager_SkeletalMeshActor* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
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
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::GetSafe;

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

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform /*=FTransform::Identity*/)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetChecked(Context, WorldContext);
			// Allocate Payload
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_SkeletalMeshActor->AllocatePayload<PayloadImplType>(Shot.GetType());
			// Set Payload
			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;

			checkf(Transform.GetScale3D() != FVector::ZeroVector, TEXT("%s: Transform.GetScale3D() == FVector::ZeroVector is NOT Valid."), *Context);

			Payload->Transform = Transform;
			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Shot);

			return Manager_SkeletalMeshActor->Spawn(Shot.GetType(), Payload);
			
			return nullptr;
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform /*=FTransform::Identity*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetSafe(Context, WorldContext, Log);

			if (!Manager_SkeletalMeshActor)
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Shot.IsValid(Context))
				return nullptr;

			if (Transform.GetScale3D() == FVector::ZeroVector)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Transform.GetScale3D() == FVector::ZeroVector is NOT Valid."), *Context));
				return nullptr;
			}
			return SpawnChecked(Context, WorldContext, PooledPayload, Shot, Transform);
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, PooledPayload, Shot, FTransform::Identity, nullptr);
		}

		#undef ShotType

		#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot

		const FCsSkeletalMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform /*=FTransform::Identity*/)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetChecked(Context, WorldContext);
			// Allocate Payload
			typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_SkeletalMeshActor->AllocatePayload<PayloadImplType>(Shot.GetType());
			// Set Payload
			typedef NCsSkeletalMeshActor::NPayload::FLibrary PayloadLibrary;

			checkf(Transform.GetScale3D() != FVector::ZeroVector, TEXT("%s: Transform.GetScale3D() == FVector::ZeroVector is NOT Valid."), *Context);

			Payload->Transform = Transform;
			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Shot);

			return Manager_SkeletalMeshActor->Spawn(Shot.GetType(), Payload);
			
			return nullptr;
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot, const FTransform& Transform /*=FTransform::Identity*/, void(*Log)(const FString&) /*=&FCsLog::Warning*/)
		{
			UCsManager_SkeletalMeshActor* Manager_SkeletalMeshActor = GetSafe(Context, WorldContext, Log);

			if (!Manager_SkeletalMeshActor)
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Shot.IsValid(Context))
				return nullptr;

			if (Transform.GetScale3D() == FVector::ZeroVector)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Transform.GetScale3D() == FVector::ZeroVector is NOT Valid."), *Context));
				return nullptr;
			}
			return SpawnChecked(Context, WorldContext, PooledPayload, Shot, Transform);
		}

		const FCsSkeletalMeshActorPooled* FLibrary::SafeSpawn(const UObject* WorldContext, const PooledPayloadType* PooledPayload, const ShotType& Shot)
		{
			using namespace NCsSkeletalMeshActor::NManager::NLibrary::NCached;

			const FString& Context = Str::SafeSpawn;

			return SafeSpawn(Context, WorldContext, PooledPayload, Shot, FTransform::Identity, nullptr);
		}

		#undef ShotType

		#undef PooledPayloadType

		#undef PayloadType

		#pragma endregion Spawn
	}
}