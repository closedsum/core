// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
// Types
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsTypes_Payload_StaticMeshActor.generated.h"

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

	/** Describes how the pooled object should updated. Usually update for a
		pooled object (implements the interface: ICsPooledObject) is controlled
		by its manager.
		Usually the default value is UpdateType::Manager (NCsPooledObject::EUpdate). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload")
	ECsPooledObjectUpdate UpdateType;

	/** The object "instigating" or starting the spawn. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload")
	UObject* Instigator;

	/** The owner of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload")
	UObject* Owner;

	/** The parent of the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload")
	UObject* Parent;

	/** The current time. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload")
	FCsTime Time;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload", meta = (Bitmask, BitmaskEnum = "ECsStaticMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// StaticMeshPayloadType (NCsStaticMeshActor::Payload::IPayload)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore|Static Mesh|Payload")
	FCsStaticMeshActorPooledInfo Mesh;

	FCsPayload_StaticMesh() :
		UpdateType(ECsPooledObjectUpdate::Manager),
		Instigator(nullptr),
		Owner(nullptr),
		Parent(nullptr),
		Time(),
		PreserveChangesFromDefaultMask(0),
		Mesh()
	{
	}

#define PayloadType NCsStaticMeshActor::NPayload::FImpl
	void CopyToPayloadAsValueChecked(const FString& Context, PayloadType* Payload) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsPayload_StaticMesh