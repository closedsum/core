// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"

// Managers
#include "Managers/StaticMesh/CsManager_StaticMeshActor.h"
// Library
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// StaticMeshActor
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#if WITH_EDITOR
// Library
	// Common
#include "Library/CsLibrary_World.h"
#include "Game/CsLibrary_GameState.h"
// Managers
#include "Singleton/CsGetManagerSingleton.h"
#endif // #if WITH_EDITOR

namespace NCsStaticMeshActor
{
	namespace NManager
	{
		namespace NLibrary
		{
			namespace NCached
			{
				namespace Str
				{
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NManager::FLibrary, GetSafeContextRoot);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NManager::FLibrary, SafeSpawn);
					CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(NCsStaticMeshActor::NManager::FLibrary, GetSafe);
				}
			}
		}

		#define USING_NS_CACHED using namespace NCsStaticMeshActor::NManager::NLibrary::NCached;
		#define SET_CONTEXT(__FunctionName) using namespace NCsStaticMeshActor::NManager::NLibrary::NCached; \
			const FString& Context = Str::__FunctionName
		#define LogLevel void(*Log)(const FString&) /*=&NCsStaticMesh::FLog::Warning*/
		#define GameStateLibrary NCsGameState::FLibrary

		// ContextRoot
		#pragma region

		#if WITH_EDITOR

		UObject* FLibrary::GetContextRootChecked(const FString& Context, const UObject* WorldContext)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
			{
				const ICsGetManagerSingleton* GetManagerSingleton = CS_CONST_INTERFACE_CAST_CHECKED(WorldContext, UObject, ICsGetManagerSingleton);

				return GetManagerSingleton->_getUObject();
			}
			return GameStateLibrary::GetAsObjectChecked(Context, WorldContext);
		}

		UObject* FLibrary::GetSafeContextRoot(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			if (CsWorldLibrary::IsPlayInEditorOrEditorPreview(WorldContext))
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

		UCsManager_StaticMeshActor* FLibrary::GetChecked(const FString& Context, const UObject* WorldContext)
		{
		#if UE_BUILD_SHIPPING
			return UCsManager_StaticMeshActor::Get(nullptr);
		#else
			UObject* ContextRoot								= GetContextRootChecked(Context, WorldContext);
			UCsManager_StaticMeshActor* Manager_StaticMeshActor = UCsManager_StaticMeshActor::Get(ContextRoot);

			CS_IS_PTR_NULL_CHECKED(Manager_StaticMeshActor)
			return Manager_StaticMeshActor;
		#endif // #if UE_BUILD_SHIPPING
		}

		UCsManager_StaticMeshActor* FLibrary::GetSafe(const FString& Context, const UObject* WorldContext, LogLevel)
		{
			UObject* ContextRoot = GetSafeContextRoot(Context, WorldContext, Log);

		#if WITH_EDITOR
			if (!ContextRoot)
				return nullptr;
		#endif // #if WITH_EDITOR

			UCsManager_StaticMeshActor* Manager_StaticMeshActor = UCsManager_StaticMeshActor::GetSafe(Context, ContextRoot, Log);

			if (!IsValid(Manager_StaticMeshActor))
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Failed to get Manager_StaticMeshActor."), *Context));
				return nullptr;
			}
			return Manager_StaticMeshActor;
		}

		UCsManager_StaticMeshActor* FLibrary::GetSafe(const UObject* WorldContext)
		{
			SET_CONTEXT(GetSafe);

			return GetSafe(Context, WorldContext, nullptr);
		}

		#pragma endregion Get

		// Payload
		#pragma region

		#define PayloadType NCsStaticMeshActor::NPayload::IPayload
		PayloadType* FLibrary::AllocatePayloadChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload(Type);
		}
		#undef PayloadType

		#define PayloadImplType NCsStaticMeshActor::NPayload::FImpl
		PayloadImplType* FLibrary::AllocatePayloadImplChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type)
		{
			return GetChecked(Context, WorldContext)->AllocatePayload<PayloadImplType>(Type);
		}
		#undef PayloadImplType

		#pragma endregion 

		// Spawn
		#pragma region

		#define PayloadType NCsStaticMeshActor::NPayload::IPayload

		const FCsStaticMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const FECsStaticMeshActor& Type, PayloadType* Payload)
		{
			return GetChecked(Context, WorldContext)->Spawn(Type, Payload);
		}

		#define PooledPayloadType NCsPooledObject::NPayload::IPayload

		const FCsStaticMeshActorPooled* FLibrary::SpawnChecked(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform3f& Transform /*=FTransform3f::Identity*/)
		{
			UCsManager_StaticMeshActor* Manager_StaticMeshActor = GetChecked(Context, WorldContext);
			// Allocate Payload
			typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

			PayloadImplType* Payload = Manager_StaticMeshActor->AllocatePayload<PayloadImplType>(Info.Type);
			// Set Payload
			typedef NCsStaticMeshActor::NPayload::FLibrary PayloadLibrary;

			checkf(Transform.GetScale3D() != FVector3f::ZeroVector, TEXT("%s: Transform.GetScale3D() == FVector3f::ZeroVector is NOT Valid."), *Context);

			Payload->Transform = Transform;
			PayloadLibrary::SetChecked(Context, Payload, PooledPayload, Info);
			
			return Manager_StaticMeshActor->Spawn(Info.Type, Payload);
		}

		const FCsStaticMeshActorPooled* FLibrary::SafeSpawn(const FString& Context, const UObject* WorldContext, const PooledPayloadType* PooledPayload, const FCsStaticMeshActorPooledInfo& Info, const FTransform3f& Transform /*=FTransform3f::Identity*/, LogLevel)
		{
			UCsManager_StaticMeshActor* Manager_StaticMeshActor = GetSafe(Context, WorldContext, Log);

			if (!Manager_StaticMeshActor)
				return nullptr;

			CS_IS_PTR_NULL_RET_NULL(PooledPayload)

			if (!Info.IsValid(Context, Log))
				return nullptr;

			if (Transform.GetScale3D() == FVector3f::ZeroVector)
			{
				CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: Transform.GetScale3D() == FVector3f::ZeroVector is NOT Valid."), *Context));
				return nullptr;
			}
			return SpawnChecked(Context, WorldContext, PooledPayload, Info, Transform);
		}

		#undef PooledPayloadType

		#undef PayloadType

		#pragma endregion Spawn

		#undef USING_NS_CACHED
		#undef SET_CONTEXT
		#undef LogLevel
		#undef GameStateLibrary
	}
}