// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/StaticMesh/Payload/CsTypes_Payload_StaticMeshActor.h"

// Library
#include "Managers/StaticMesh/Payload/CsLibrary_Payload_StaticMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

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
	PooledPayload.Instigator					 = Instigator;
	PooledPayload.Owner							 = Owner;
	PooledPayload.Parent						 = Parent;
	PooledPayload.Time							 = Time;
	PooledPayload.PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

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