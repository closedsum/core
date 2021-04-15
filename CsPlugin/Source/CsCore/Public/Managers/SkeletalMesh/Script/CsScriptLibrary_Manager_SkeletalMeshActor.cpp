// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Script/CsScriptLibrary_Manager_SkeletalMeshActor.h"
#include "CsCore.h"

// Library
#include "Managers/SkeletalMesh/CsLibrary_Manager_SkeletalMeshActor.h"
// Managers
#include "Managers/SkeletalMesh/CsManager_SkeletalMeshActor.h"
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

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;

	UObject* ContextRoot = SkeletalMeshManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return nullptr;
#endif // #if WITH_EDITOR

	if (!EMCsSkeletalMeshActor::Get().IsValidEnum(Type))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Type: %s is NOT Valid."), *Context, Type.ToChar());
		return nullptr;
	}

	UCsManager_SkeletalMeshActor* Manager_SkeletalMesh = UCsManager_SkeletalMeshActor::Get(ContextRoot);

	if (Index < 0 || Index >= Manager_SkeletalMesh->GetPoolSize(Type))
	{
		UE_LOG(LogCs, Warning, TEXT("%s: Index: %d is NOT [0, %d] Inclusive."), *Context, Index, Manager_SkeletalMesh->GetPoolSize(Type));
		return nullptr;
	}
	
	const FCsSkeletalMeshActorPooled* SkeletalMeshPooled = Manager_SkeletalMesh->FindObject(Type, Index);

	if (SkeletalMeshPooled)
	{
		return SkeletalMeshPooled->GetSafeObject();
	}
	return nullptr;
}

#pragma endregion Pool

int32 UCsScriptLibrary_Manager_SkeletalMeshActor::SpawnByAnimSequenceOneShot(const FString& Context, UObject* WorldContextObject, const FCsPayload_SkeletalMesh_AnimSequence_OneShot& Payload)
{
	using namespace NCsScriptLibraryManagerSkeletalMeshActor::NCached;

	const FString& Ctxt = Context.IsEmpty() ? Str::SpawnByAnimSequenceOneShot : Context;

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UObject* ContextRoot = SkeletalMeshManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return INDEX_NONE;
#endif // #if WITH_EDITOR

	UCsManager_SkeletalMeshActor* Manager_SkeletalMesh = UCsManager_SkeletalMeshActor::Get(ContextRoot);

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

	typedef NCsSkeletalMeshActor::NManager::FLibrary SkeletalMeshManagerLibrary;

	// Check Payload is Valid
	if (!Payload.IsValid(Ctxt))
		return INDEX_NONE;

	// Try to allocate a native payload
	UObject* ContextRoot = SkeletalMeshManagerLibrary::GetSafeContextRoot(Ctxt, WorldContextObject);

#if WITH_EDITOR
	if (!ContextRoot)
		return INDEX_NONE;
#endif // #if WITH_EDITOR

	UCsManager_SkeletalMeshActor* Manager_SkeletalMesh = UCsManager_SkeletalMeshActor::Get(ContextRoot);

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