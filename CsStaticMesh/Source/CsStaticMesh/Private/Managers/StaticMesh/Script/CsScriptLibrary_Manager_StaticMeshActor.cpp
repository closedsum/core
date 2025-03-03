// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Managers/StaticMesh/Script/CsScriptLibrary_Manager_StaticMeshActor.h"
#include "CsStaticMesh.h"

// Library
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/StaticMesh/CsManager_StaticMeshActor.h"
// Log
#include "Utility/CsStaticMeshLog.h"
// SkeletalMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(CsScriptLibrary_Manager_StaticMeshActor)

CS_START_CACHED_FUNCTION_NAME(CsScriptLibrary_Manager_StaticMeshActor)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_StaticMeshActor, FindObject)
	CS_DEFINE_CACHED_FUNCTION_NAME(UCsScriptLibrary_Manager_StaticMeshActor, Spawn)
CS_END_CACHED_FUNCTION_NAME

CS_DEFINE_STATIC_LOG_WARNING(UCsScriptLibrary_Manager_StaticMeshActor, NCsStaticMesh::FLog::Warning);

UCsScriptLibrary_Manager_StaticMeshActor::UCsScriptLibrary_Manager_StaticMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

using PayloadImplType = NCsStaticMeshActor::NPayload::NImpl::FImpl;

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_StaticMeshActor::FindObject(const FString& Context, const UObject* WorldContextObject, const FECsStaticMeshActor& Type, const int32& Index)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(FindObject);

	void(*Log)(const FString&) = LogWarning;

	UCsManager_StaticMeshActor* Manager_StaticMesh = CsStaticMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_StaticMesh)
		return nullptr;

	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID_RET_NULL(EMCsStaticMeshActor, FECsStaticMeshActor, Type)
	// Check Index is Valid
	CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_RET_NULL(Index, 0, Manager_StaticMesh->GetPoolSize(Type))

	const FCsStaticMeshActorPooled* StaticMeshPooled = Manager_StaticMesh->FindSafeObject(Type, Index);

	if (StaticMeshPooled)
	{
		return StaticMeshPooled->GetSafeObject();
	}
	UE_LOG(LogCsStaticMesh, Warning, TEXT("%s, Failed to Find Object of Type: %s at Index: %d."), *Context, Type.ToChar(), Index);
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_StaticMeshActor::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_StaticMesh& Payload)
{
	CS_CONDITIONAL_SET_CTXT_AS_FUNCTION_NAME(Spawn);
	
	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UCsManager_StaticMeshActor* Manager_StaticMesh = CsStaticMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_StaticMesh)
		return INDEX_NONE;

	const FECsStaticMeshActor& Type	= Payload.Mesh.Type;
	PayloadImplType* PayloadImpl	= Manager_StaticMesh->AllocatePayload<PayloadImplType>(Type);

	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, PayloadImpl);

	const FCsStaticMeshActorPooled* SkeletalMeshPooled = Manager_StaticMesh->Spawn(Type, PayloadImpl);

	return SkeletalMeshPooled->GetCache()->GetIndex();
}