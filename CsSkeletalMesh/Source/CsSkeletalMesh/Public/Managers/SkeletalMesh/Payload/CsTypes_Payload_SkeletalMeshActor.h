// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Time/CsTypes_Time.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

#include "CsTypes_Payload_SkeletalMeshActor.generated.h"

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

// NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NSequence, FOnShot)
// NCsSkeletalMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NPayload, FImpl)

/**
*/
USTRUCT(BlueprintType)
struct CSSKELETALMESH_API FCsPayload_SkeletalMesh_AnimSequence_OneShot
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	UObject* Instigator;

	/** The owner of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	UObject* Owner;

	/** The parent of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsSkeletalMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// SkeletalMeshPayloadType (NCsSkeletalMeshActor::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	FCsSkeletalMeshAnimSequenceOneShot Shot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	FTransform3f Transform;

	FCsPayload_SkeletalMesh_AnimSequence_OneShot() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Shot(),
		Transform(FTransform3f::Identity)
	{
	}

	void UpdateInternalPtrs();

#define PayloadType NCsSkeletalMeshActor::NPayload::FImpl
#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
	void CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload, ShotType* InShot) const;
#undef PayloadType
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkeletalMesh::FLog::Warning) const;
};

#pragma endregion FCsSkeletalMeshAnimSequenceOneShot

// FCsSkeletalMeshAnimMontageOneShot
#pragma region

// NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NMontage, FOnShot)
// NCsSkeletalMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NPayload, FImpl)

/**
*/
USTRUCT(BlueprintType)
struct CSSKELETALMESH_API FCsPayload_SkeletalMesh_AnimMontage_OneShot
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	UObject* Instigator;

	/** The owner of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	UObject* Owner;

	/** The parent of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsSkeletalMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// SkeletalMeshPayloadType (NCsSkeletalMeshActor::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	FCsSkeletalMeshAnimMontageOneShot Shot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Skeletal Mesh|Payload")
	FTransform3f Transform;

	FCsPayload_SkeletalMesh_AnimMontage_OneShot() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Shot(),
		Transform(FTransform3f::Identity)
	{
	}

	void UpdateInternalPtrs();

#define PayloadType NCsSkeletalMeshActor::NPayload::FImpl
#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
	void CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload, ShotType* InShot) const;
#undef PayloadType
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsSkeletalMesh::FLog::Warning) const;
};

#pragma endregion FCsSkeletalMeshAnimMontageOneShot