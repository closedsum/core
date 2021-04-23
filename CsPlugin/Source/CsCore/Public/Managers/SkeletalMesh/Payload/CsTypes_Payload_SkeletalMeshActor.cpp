// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Managers/SkeletalMesh/Payload/CsTypes_Payload_SkeletalMeshActor.h"

// Library
#include "Managers/SkeletalMesh/Payload/CsLibrary_Payload_SkeletalMeshActor.h"
#include "Library/CsLibrary_Valid.h"
// Pool
#include "Managers/Pool/Payload/CsPayload_PooledObjectImplSlice.h"

// FCsPayload_SkeletalMesh_AnimSequence_OneShot
#pragma region

void FCsPayload_SkeletalMesh_AnimSequence_OneShot::UpdateInternalPtrs()
{
	Shot.UpdateInternalPtrs();
}

#define PayloadType NCsSkeletalMeshActor::NPayload::FImpl
#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
void FCsPayload_SkeletalMesh_AnimSequence_OneShot::CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload, ShotType* InShot) const
{
#undef PayloadType
#undef ShotType

	CS_IS_PTR_NULL_CHECKED(Payload)

	typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

	PooledPayloadType PooledPayload;
	PooledPayload.Instigator					 = Instigator;
	PooledPayload.Owner							 = Owner;
	PooledPayload.Parent						 = Parent;
	PooledPayload.Time							 = Time;
	PooledPayload.PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	typedef NCsSkeletalMeshActor::NPayload::FLibrary SkeletalMeshPayloadLibrary;

	CS_IS_PTR_NULL_CHECKED(InShot)

	Shot.CopyToShotAsValue(InShot);

	SkeletalMeshPayloadLibrary::SetChecked(Context, Payload, &PooledPayload, *InShot);
}

bool FCsPayload_SkeletalMesh_AnimSequence_OneShot::IsValidChecked(const FString& Context) const
{
	check(Shot.IsValidChecked(Context));
	return true;
}

bool FCsPayload_SkeletalMesh_AnimSequence_OneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Shot.IsValid(Context, Log))
		return false;
	return true;
}

#pragma endregion FCsPayload_SkeletalMesh_AnimSequence_OneShot

// FCsPayload_SkeletalMesh_AnimMontage_OneShot
#pragma region

void FCsPayload_SkeletalMesh_AnimMontage_OneShot::UpdateInternalPtrs()
{
	Shot.UpdateInternalPtrs();
}

#define PayloadType NCsSkeletalMeshActor::NPayload::FImpl
#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
void FCsPayload_SkeletalMesh_AnimMontage_OneShot::CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload, ShotType* InShot) const
{
#undef PayloadType
#undef ShotType

	CS_IS_PTR_NULL_CHECKED(Payload)

	typedef NCsPooledObject::NPayload::FImplSlice PooledPayloadType;

	PooledPayloadType PooledPayload;
	PooledPayload.Instigator					 = Instigator;
	PooledPayload.Owner							 = Owner;
	PooledPayload.Parent						 = Parent;
	PooledPayload.Time							 = Time;
	PooledPayload.PreserveChangesFromDefaultMask = PreserveChangesFromDefaultMask;

	typedef NCsSkeletalMeshActor::NPayload::FLibrary SkeletalMeshPayloadLibrary;

	CS_IS_PTR_NULL_CHECKED(InShot)

	Shot.CopyToShotAsValue(InShot);

	SkeletalMeshPayloadLibrary::SetChecked(Context, Payload, &PooledPayload, *InShot);
}

bool FCsPayload_SkeletalMesh_AnimMontage_OneShot::IsValidChecked(const FString& Context) const
{
	check(Shot.IsValidChecked(Context));
	return true;
}

bool FCsPayload_SkeletalMesh_AnimMontage_OneShot::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (!Shot.IsValid(Context, Log))
		return false;
	return true;
}

#pragma endregion FCsPayload_SkeletalMesh_AnimSequence_OneShot