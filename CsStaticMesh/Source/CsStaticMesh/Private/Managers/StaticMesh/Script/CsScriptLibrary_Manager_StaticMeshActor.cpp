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

// Cached
#pragma region

namespace NCsScriptLibraryManagerStaticMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_StaticMeshActor, FindObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_StaticMeshActor, Spawn);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_StaticMeshActor::UCsScriptLibrary_Manager_StaticMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

#define USING_NS_CACHED using namespace NCsScriptLibraryManagerStaticMeshActor::NCached;
#define CONDITIONAL_SET_CTXT(__FunctionName) using namespace NCsScriptLibraryManagerStaticMeshActor::NCached; \
	const FString& Ctxt = Context.IsEmpty() ? Str::__FunctionName : Context
#define LogWarning void(*Log)(const FString&) = &NCsStaticMesh::FLog::Warning;
#define StaticMeshManagerLibrary NCsStaticMeshActor::NManager::FLibrary

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_StaticMeshActor::FindObject(const FString& Context, const UObject* WorldContextObject, const FECsStaticMeshActor& Type, const int32& Index)
{
	CONDITIONAL_SET_CTXT(FindObject);

	LogWarning

	UCsManager_StaticMeshActor* Manager_StaticMesh = StaticMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

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
	UE_LOG(LogCsStaticMesh, Warning, TEXT("%s, Failed to Find Object of Type: %s at Index: %d."), Type.ToChar(), Index);
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_StaticMeshActor::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_StaticMesh& Payload)
{
	CONDITIONAL_SET_CTXT(Spawn);
	
	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UCsManager_StaticMeshActor* Manager_StaticMesh = StaticMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_StaticMesh)
		return INDEX_NONE;

	typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

	const FECsStaticMeshActor& Type	= Payload.Mesh.Type;
	PayloadImplType* PayloadImpl	= Manager_StaticMesh->AllocatePayload<PayloadImplType>(Type);

	// Copy script payload to native payload
	Payload.CopyToPayloadAsValueChecked(Ctxt, PayloadImpl);

	const FCsStaticMeshActorPooled* SkeletalMeshPooled = Manager_StaticMesh->Spawn(Type, PayloadImpl);

	return SkeletalMeshPooled->GetCache()->GetIndex();
}

#undef USING_NS_CACHED
#undef CONDITIONAL_SET_CTXT
#undef LogWarning
#undef StaticMeshManagerLibrary