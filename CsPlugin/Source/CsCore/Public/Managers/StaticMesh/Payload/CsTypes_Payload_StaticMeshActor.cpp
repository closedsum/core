// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsTypes_Payload_StaticMeshActor.h"

// Library
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Library/CsLibrary_Valid.h"
#include "Library/CsLibrary_Array.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"
// StaticMesh
#include "Managers/StaticMesh/Payload/CsPayload_StaticMeshActorImpl.h"

// FCsPayload_StaticMesh
#pragma region

void FCsPayload_StaticMesh::UpdateInternalPtrs()
{
	Mesh.UpdateInternalPtrs();
}

#define PayloadType NCsStaticMeshActor::NPayload::FImpl
void FCsPayload_StaticMesh::CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload) const
{
#undef PayloadType

	CS_IS_PTR_NULL_CHECKED(Payload)

	typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

	PooledPayloadType PooledPayload;
	PooledPayload.UpdateType					 = (NCsPooledObject::EUpdate)UpdateType;
	PooledPayload.Instigator					 = Instigator;
	PooledPayload.Owner							 = Owner;
	PooledPayload.Parent						 = Parent;
	PooledPayload.Time							 = Time;
	PooledPayload.PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	Payload->Mesh = Mesh.Mesh.GetChecked(Context);

	if (Mesh.Materials.Materials.Num() > CS_EMPTY)
	{
		typedef NCsArray::FLibrary ArrayLibrary;

		ArrayLibrary::Copy<UMaterialInterface>(Payload->Materials, Mesh.Materials.GetChecked(Context));
	}

	Payload->DeallocateMethod			= Mesh.GetDeallocateMethod();
	Payload->LifeTime					= Mesh.LifeTime;
	Payload->AttachmentTransformRules	= Mesh.AttachmentTransformRules;
	Payload->Bone						= Mesh.Bone;
	Payload->TransformRules				= Mesh.TransformRules;
	Payload->Transform					= Mesh.Transform;
	Payload->bCastShadow				= Mesh.bCastShadow;
	Payload->bReceivesDecals			= Mesh.bReceivesDecals;
	Payload->bUseAsOccluder				= Mesh.bUseAsOccluder;

	typedef NCsStaticMeshActor::NPayload::FLibrary StaticMeshPayloadLibrary;

	StaticMeshPayloadLibrary::SetChecked(Context, Payload, &PooledPayload);
}

bool FCsPayload_StaticMesh::IsValidChecked(const FString& Context) const
{
	check(Mesh.IsValidChecked(Context));
	return true;
}

bool FCsPayload_StaticMesh::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Mesh.IsValid(Context, Log))
		return false;
	return true;
}

#pragma endregion FCsPayload_StaticMesh