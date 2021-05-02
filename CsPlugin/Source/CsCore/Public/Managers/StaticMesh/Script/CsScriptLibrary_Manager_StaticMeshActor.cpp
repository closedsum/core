// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Script/CsScriptLibrary_Manager_StaticMeshActor.h"
#include "CsCore.h"

// Library
#include "Managers/StaticMesh/CsLibrary_Manager_StaticMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/StaticMesh/CsManager_StaticMeshActor.h"
// Log
#include "Utility/CsLog.h"
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

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_StaticMeshActor::FindObject(const FString& Context, const UObject* WorldContextObject, const FECsStaticMeshActor& Type, const int32& Index)
{
	using namespace NCsScriptLibraryManagerStaticMeshActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FindObject : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	typedef NCsStaticMeshActor::NManager::FLibrary StaticMeshManagerLibrary;

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
	UE_LOG(LogCs, Warning, TEXT("%s, Failed to Find Object of Type: %s at Index: %d."), Type.ToChar(), Index);
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_StaticMeshActor::Spawn(const FString& Context, const UObject* WorldContextObject, const FCsPayload_StaticMesh& Payload)
{
	using namespace NCsScriptLibraryManagerStaticMeshActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::Spawn : Context;
	
	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	typedef NCsStaticMeshActor::NManager::FLibrary StaticMeshManagerLibrary;

	// Try to allocate a native payload
	UCsManager_StaticMeshActor* Manager_StaticMesh = StaticMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_StaticMesh)
		return INDEX_NONE;

	typedef NCsStaticMeshActor::NPayload::FImpl PayloadImplType;

	const FECsStaticMeshActor& Type	= Payload.Mesh.Type;
	PayloadImplType* PayloadImpl	= Manager_StaticMesh->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	const_cast<FCsPayload_StaticMesh&>(Payload).UpdateInternalPtrs();

	Payload.CopyToPayloadAsValueChecked(Ctxt, PayloadImpl);

	const FCsStaticMeshActorPooled* SkeletalMeshPooled = Manager_StaticMesh->Spawn(Type, PayloadImpl);

	return SkeletalMeshPooled->GetCache()->GetIndex();
}