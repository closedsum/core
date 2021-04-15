// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Time/CsTypes_Time.h"
// SkeletalMesh
#include "Managers/SkeletalMesh/Params/CsParams_SkeletalMeshActor.h"

#include "CsTypes_Payload_SkeletalMeshActor.generated.h"
#pragma once

// FCsSkeletalMeshAnimSequenceOneShot
#pragma region

// NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsSkeletalMeshActor, NAnim, NSequence, FOnShot)
// NCsSkeletalMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsSkeletalMeshActor, NPayload, FImpl)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_SkeletalMesh_AnimSequence_OneShot
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/** The owner of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Owner;

	/** The parent of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsSkeletalMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// SkeletalMeshPayloadType (NCsSkeletalMeshActor::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSkeletalMeshAnimSequenceOneShot Shot;

	FCsPayload_SkeletalMesh_AnimSequence_OneShot() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Shot()
	{
	}

	void UpdateInternalPtrs();

#define PayloadType NCsSkeletalMeshActor::NPayload::FImpl
#define ShotType NCsSkeletalMeshActor::NAnim::NSequence::FOneShot
	void CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload, ShotType* InShot) const;
#undef PayloadType
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
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
struct CSCORE_API FCsPayload_SkeletalMesh_AnimMontage_OneShot
{
	GENERATED_USTRUCT_BODY()

public:

// PooledPayloadType (NCsPooledObject::NPayload::IPayload)

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Instigator;

	/** The owner of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Owner;

	/** The parent of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsSkeletalMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// SkeletalMeshPayloadType (NCsSkeletalMeshActor::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSkeletalMeshAnimMontageOneShot Shot;

	FCsPayload_SkeletalMesh_AnimMontage_OneShot() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Shot()
	{
	}

	void UpdateInternalPtrs();

#define PayloadType NCsSkeletalMeshActor::NPayload::FImpl
#define ShotType NCsSkeletalMeshActor::NAnim::NMontage::FOneShot
	void CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload, ShotType* InShot) const;
#undef PayloadType
#undef ShotType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsSkeletalMeshAnimMontageOneShot