// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
// Types
#include "Managers/Pool/CsTypes_Pool.h"
#include "Managers/Time/CsTypes_Time.h"
#include "Managers/StaticMesh/CsTypes_StaticMeshActor.h"

#include "CsTypes_Payload_StaticMeshActor.generated.h"

// FCsPayload_StaticMesh
#pragma region

// PayloadImplType (NCsStaticMeshActor::NPayload::NImpl::FImpl)
CS_FWD_DECLARE_STRUCT_NAMESPACE_3(NCsStaticMeshActor, NPayload, NImpl, FImpl)

/**
*/
USTRUCT(BlueprintType)
struct CSSTATICMESH_API FCsPayload_StaticMesh
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh|Payload", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsStaticMeshPayloadChange"))
	int32 PreserveChangesFromDefaultMask;

// PayloadType (NCsStaticMeshActor::Payload::IPayload)

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

	using PayloadImplType = NCsStaticMeshActor::NPayload::NImpl::FImpl;

	void CopyToPayloadAsValueChecked(const FString& Context, PayloadImplType* Payload) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &NCsStaticMesh::FLog::Warning) const;
};

#pragma endregion FCsPayload_StaticMesh