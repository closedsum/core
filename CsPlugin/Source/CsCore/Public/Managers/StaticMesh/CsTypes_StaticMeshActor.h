// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_AttachDetach.h"

#include "CsTypes_StaticMeshActor.generated.h"
#pragma once

// StaticMeshActor
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsStaticMeshActor : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStaticMeshActor)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStaticMeshActor)

struct CSCORE_API EMCsStaticMeshActor : public TCsEnumStructMap<FECsStaticMeshActor, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStaticMeshActor, FECsStaticMeshActor, uint8)
};

namespace NCsStaticMeshActor
{
	typedef FECsStaticMeshActor Type;

	CSCORE_API void FromEnumSettings(const FString& Context);

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion StaticMeshActor

// StaticMeshActorClass
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsStaticMeshActorClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStaticMeshActorClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStaticMeshActorClass)

struct CSCORE_API EMCsStaticMeshActorClass : public TCsEnumStructMap<FECsStaticMeshActorClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStaticMeshActorClass, FECsStaticMeshActorClass, uint8)
};

namespace NCsStaticMeshActorClass
{
	typedef FECsStaticMeshActorClass Type;

	namespace Ref
	{
	}

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion StaticMeshActor

// StaticMeshActorDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate a Sound.
*/
UENUM(BlueprintType)
enum class ECsStaticMeshActorDeallocateMethod : uint8
{
	/** If a StaticMeshActor is attached to a parent object,
		  LifeTime == 0.of means the StaticMeshActor will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the StaticMeshActor.
		If a StaticMeshActor is NOT attached to a parent object,
		  LifeTime == 0.0f means the StaticMeshActor will stay active forever.
		  LifeTime > 0.0f means the StaticMeshActor will be deallocated after LifeTime amount of time after
		   the StaticMeshActor has been allocated. */
	LifeTime								UMETA(DisplayName = "LifeTime"),
	/** */
	Complete								UMETA(DisplayName = "Complete"),
	ECsStaticMeshActorDeallocateMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsStaticMeshActorDeallocateMethod final : public TCsEnumMap<ECsStaticMeshActorDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsStaticMeshActorDeallocateMethod, ECsStaticMeshActorDeallocateMethod)
};

namespace NCsStaticMeshActorDeallocateMethod
{
	typedef ECsStaticMeshActorDeallocateMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type LifeTime;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsStaticMeshActorDeallocateMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsStaticMeshActor
{
	enum class EDeallocateMethod : uint8
	{
		/** If a StaticMeshActor is attached to a parent object,
			  LifeTime == 0.of means the StaticMeshActor will be deallocated immediately
			   when the parent has been destroyed / deallocated.
			  LifeTime > 0.0f will be the time after the parent object has been
			   destroyed / deallocated to deallocate the StaticMeshActor.
			If a StaticMeshActor is NOT attached to a parent object,
			  LifeTime == 0.0f means the StaticMeshActor will stay active forever.
			  LifeTime > 0.0f means the StaticMeshActor will be deallocated after LifeTime amount of time after
			   the StaticMeshActor has been allocated. */
		LifeTime,
		/** */
		Complete,
		EDeallocateMethod_MAX
	};
}

#pragma endregion StaticMeshActorDeallocateMethod

// FCsStaticMeshActorPooledInfo
#pragma region

class UStaticMesh;

/**
* Container holding general information for a Sound Asset.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsStaticMeshActorPooledInfo
{
	GENERATED_USTRUCT_BODY()

	/** Soft reference to a UStaticMesh asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftObjectPtr<UStaticMesh> Mesh;

	/** */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsLoadFlags"))
	int32 Mesh_LoadFlags;

	/** Hard reference to a UStaticMesh asset. */
	UPROPERTY(Transient, BlueprintReadOnly)
	UStaticMesh* Mesh_Internal;

	/** The StaticMeshActor Type. This is used to group StaticMeshActors into different categories 
	    and can be used by a Manager pooling StaticMeshActors to Spawn the correct
		StaticMeshActor. 
		NOTE: StaticMeshActor mostly acts as a "container" for a UStaticMesh. Unless there is a
		need from some special logic, only one StaticMeshActor class (i.e. ACsStatMeshActorPooledImpl) 
		that will be used. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsStaticMeshActor Type;

	/** Condition to determine when to deallocate the StaticMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsStaticMeshActorDeallocateMethod DeallocateMethod;

private:

	NCsStaticMeshActor::EDeallocateMethod* DeallocateMethod_Internal;

public:

	/** Valid if the DeallocateMethod == ECsSoundDeallocateMethod::LifeTime.
		- If a Sound IS attached to a Parent object, 
		   LifeTime == 0.of means the Sound object will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the Sound object.
	    - If a Sound is NOT attached to a Parent object,
		   LifeTime == 0.0f means the Sound object will stay active forever.
		   LifeTime > 0.0f means the Sound will be deallocated after LifeTime amount of time after
	        the FX object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** Valid if the Sound is attached to a Parent object or when an Sound object is
		allocated, the Parent field of the payload is set.If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the Sound is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FName Bone;

	/** Which of the components of Transform to apply to the FX. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta = (Bitmask, BitmaskEnum = "ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the FX.
		If the Sound is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FTransform Transform;

public:

	FCsStaticMeshActorPooledInfo() :
		Mesh(nullptr),
		Mesh_LoadFlags(0),
		Mesh_Internal(nullptr),
		Type(),
		DeallocateMethod(ECsStaticMeshActorDeallocateMethod::Complete),
		DeallocateMethod_Internal(nullptr),
		LifeTime(0.0f),
		AttachmentTransformRules(ECsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform::Identity)
	{
	}
	
	FORCEINLINE void UpdateInternalPtrs()
	{
		UpdateDeallocateMethodPtr();
	}

	FORCEINLINE void UpdateDeallocateMethodPtr() { DeallocateMethod_Internal = (NCsStaticMeshActor::EDeallocateMethod*)&DeallocateMethod; }

#define DeallocateMethodType NCsStaticMeshActor::EDeallocateMethod
	FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *DeallocateMethod_Internal; }
#undef DeallocateMethodType

	/**
	* Get the Hard reference to the UStaticMesh asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UStaticMesh* Get() const { return Mesh_Internal; }

	/**
	* Get the Hard reference to the UStaticMesh asset.
	*
	* @param Context	The calling context.
	* return			Static Mesh
	*/
	FORCEINLINE UStaticMesh* GetChecked(const FString& Context) const 
	{ 
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("%s: Mesh is NULL."), *Context);

		checkf(Mesh_Internal, TEXT("%s: Mesh has NOT been loaded from Path @ %s."), *Context, *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal; 
	}

	/**
	* Get the Hard reference to the UStaticMesh asset.
	*
	* return Static Mesh
	*/
	FORCEINLINE UStaticMesh* GetChecked() const
	{
		checkf(Mesh.ToSoftObjectPath().IsValid(), TEXT("FCsStaticMeshActorPooledInfo::GetChecked: Mesh is NULL."));

		checkf(Mesh_Internal, TEXT("FCsStaticMeshActorPooledInfo::GetChecked: Mesh has NOT been loaded from Path @ %s."), *(Mesh.ToSoftObjectPath().ToString()));

		return Mesh_Internal;
	}

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsStaticMeshActorPooledInfo