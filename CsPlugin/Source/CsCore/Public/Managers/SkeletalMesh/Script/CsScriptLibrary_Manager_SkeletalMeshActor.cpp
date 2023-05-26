// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Script/CsScriptLibrary_Manager_SkeletalMeshActor.h"
#include "CsCore.h"

// Library
#include "Managers/SkeletalMesh/CsLibrary_Manager_SkeletalMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// Managers
#include "Managers/SkeletalMesh/CsManager_SkeletalMeshActor.h"
// Log
#include "Utility/CsLog.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Payload/CsPayload_SkeletalMeshActorImpl.h"

// Cached
#pragma region

namespace NCsScriptLibraryManagerSkeletalMeshActor
{
	namespace NCached
	{
		namespace Str
		{
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_SkeletalMeshActor, FindObject);
			CS_DEFINE_CACHED_FUNCTION_NAME_AS_STRING(UCsScriptLibrary_Manager_SkeletalMeshActor, SpawnByAnimSequenceOneShot);
		}
	}
}

#pragma endregion Cached

UCsScriptLibrary_Manager_SkeletalMeshActor::UCsScriptLibrary_Manager_SkeletalMeshActor(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

// Pool
#pragma region

UObject* UCsScriptLibrary_Manager_SkeletalMeshActor::FindObject(const FString& Context, UObject* WorldContextObject, const FECsSkeletalMeshActor& Type, const int32& Index)
{
	using namespace NCsScriptLibraryManagerSkeletalMeshActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::FindObject : Context;

	void(*Log)(const FString&) = &FCsLog::Warning;

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;

	UCsManager_SkeletalMeshActor* Manager_SkeletalMesh = SkeletalMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_SkeletalMesh)
		return nullptr;

	// Check Type is Valid
	CS_IS_ENUM_STRUCT_VALID_RET_NULL(EMCsSkeletalMeshActor, FECsSkeletalMeshActor, Type)
	// Check Index is Valid
	CS_IS_INT_GREATER_THAN_AND_LESS_THAN_OR_EQUAL_RET_NULL(Index, 0, Manager_SkeletalMesh->GetPoolSize(Type))

	const FCsSkeletalMeshActorPooled* SkeletalMeshPooled = Manager_SkeletalMesh->FindSafeObject(Type, Index);

	if (SkeletalMeshPooled)
	{
		return SkeletalMeshPooled->GetSafeObject();
	}
	UE_LOG(LogCs, Warning, TEXT("%s, Failed to Find Object of Type: %s at Index: %d."), Type.ToChar(), Index);
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_SkeletalMeshActor::SpawnByAnimSequenceOneShot(const FString& Context, UObject* WorldContextObject, const FCsPayload_SkeletalMesh_AnimSequence_OneShot& Payload)
{
	using namespace NCsScriptLibraryManagerSkeletalMeshActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SpawnByAnimSequenceOneShot : Context;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;

	// Try to allocate a native payload
	UCsManager_SkeletalMeshActor* Manager_SkeletalMesh = SkeletalMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_SkeletalMesh)
		return INDEX_NONE;

	typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

	const FECsSkeletalMeshActor& Type	= Payload.Shot.Mesh.Type;
	PayloadImplType* PayloadImpl		= Manager_SkeletalMesh->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	const_cast<FCsPayload_SkeletalMesh_AnimSequence_OneShot&>(Payload).UpdateInternalPtrs();

	typedef NCsSkeletalMeshActor::NAnim::NSequence::FOneShot ShotType;

	static ShotType Shot;
	Shot.Reset();

	Payload.CopyToPayloadAsValueChecked(Ctxt, PayloadImpl, &Shot);

	const FCsSkeletalMeshActorPooled* SkeletalMeshPooled = Manager_SkeletalMesh->Spawn(Type, PayloadImpl);

	return SkeletalMeshPooled->GetCache()->GetIndex();
}

int32 UCsScriptLibrary_Manager_SkeletalMeshActor::SpawnByAnimMontageOneShot(const FString& Context, UObject* WorldContextObject, const FCsPayload_SkeletalMesh_AnimMontage_OneShot& Payload)
{
	using namespace NCsScriptLibraryManagerSkeletalMeshActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SpawnByAnimSequenceOneShot : Context;
	
	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;

	// Try to allocate a native payload
	UCsManager_SkeletalMeshActor* Manager_SkeletalMesh = SkeletalMeshManagerLibrary::GetSafe(Ctxt, WorldContextObject);

	if (!Manager_SkeletalMesh)
		return INDEX_NONE;

	typedef NCsSkeletalMeshActor::NPayload::FImpl PayloadImplType;

	const FECsSkeletalMeshActor& Type	= Payload.Shot.Mesh.Type;
	PayloadImplType* PayloadImpl		= Manager_SkeletalMesh->AllocatePayload<PayloadImplType>(Type);
	// Copy script payload to native payload
	const_cast<FCsPayload_SkeletalMesh_AnimMontage_OneShot&>(Payload).UpdateInternalPtrs();

	typedef NCsSkeletalMeshActor::NAnim::NMontage::FOneShot ShotType;

	static ShotType Shot;
	Shot.Reset();

	Payload.CopyToPayloadAsValueChecked(Ctxt, PayloadImpl, &Shot);

	const FCsSkeletalMeshActorPooled* SkeletalMeshPooled = Manager_SkeletalMesh->Spawn(Type, PayloadImpl);

	return SkeletalMeshPooled->GetCache()->GetIndex();
}