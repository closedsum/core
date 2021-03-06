// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
// Types
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsTypes_Payload_StaticMeshActor.generated.h"
#pragma once

// FCsPayload_StaticMesh
#pragma region

// NCsStaticMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, FImpl)

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsPayload_StaticMesh
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (Bitmask, BitmaskEnum = "ECsStaticMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// StaticMeshPayloadType (NCsStaticMeshActor::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsStaticMeshActorPooledInfo Mesh;

	FCsPayload_StaticMesh() :
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Mesh()
	{
	}

	void UpdateInternalPtrs();

#define PayloadType NCsStaticMeshActor::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsPayload_StaticMesh