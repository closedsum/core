// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_SkeletalMesh.h"
#include "Types/CsTypes_Material.h"

#include "CsTypes_SkeletalMeshActor.generated.h"
#pragma once

// SkeletalMeshActor
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSkeletalMeshActor : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSkeletalMeshActor)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSkeletalMeshActor)

struct CSCORE_API EMCsSkeletalMeshActor : public TCsEnumStructMap<FECsSkeletalMeshActor, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSkeletalMeshActor, FECsSkeletalMeshActor, uint8)
};

namespace NCsSkeletalMeshActor
{
	typedef FECsSkeletalMeshActor Type;

	CSCORE_API void FromEnumSettings(const FString& Context);

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion SkeletalMeshActor

// SkeletalMeshActorClass
#pragma region

USTRUCT(BlueprintType)
struct CSCORE_API FECsSkeletalMeshActorClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsSkeletalMeshActorClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsSkeletalMeshActorClass)

struct CSCORE_API EMCsSkeletalMeshActorClass : public TCsEnumStructMap<FECsSkeletalMeshActorClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsSkeletalMeshActorClass, FECsSkeletalMeshActorClass, uint8)
};

namespace NCsSkeletalMeshActorClass
{
	typedef FECsSkeletalMeshActorClass Type;

	namespace Ref
	{
	}

	CSCORE_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
}

#pragma endregion SkeletalMeshActor

// SkeletalMeshActorDeallocateMethod
#pragma region

/**
* Type for different ways to deallocate a Sound.
*/
UENUM(BlueprintType)
enum class ECsSkeletalMeshActorDeallocateMethod : uint8
{
	/** If a SkeletalMeshActor is attached to a parent object,
		  LifeTime == 0.of means the SkeletalMeshActor will be deallocated immediately
		   when the parent has been destroyed / deallocated.
		  LifeTime > 0.0f will be the time after the parent object has been
		   destroyed / deallocated to deallocate the SkeletalMeshActor.
		If a SkeletalMeshActor is NOT attached to a parent object,
		  LifeTime == 0.0f means the SkeletalMeshActor will stay active forever.
		  LifeTime > 0.0f means the SkeletalMeshActor will be deallocated after LifeTime amount of time after
		   the SkeletalMeshActor has been allocated. */
	LifeTime								UMETA(DisplayName = "LifeTime"),
	/** */
	Complete								UMETA(DisplayName = "Complete"),
	ECsSkeletalMeshActorDeallocateMethod_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsSkeletalMeshActorDeallocateMethod final : public TCsEnumMap<ECsSkeletalMeshActorDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsSkeletalMeshActorDeallocateMethod, ECsSkeletalMeshActorDeallocateMethod)
};

namespace NCsSkeletalMeshActorDeallocateMethod
{
	typedef ECsSkeletalMeshActorDeallocateMethod Type;

	namespace Ref
	{
		extern CSCORE_API const Type LifeTime;
		extern CSCORE_API const Type Complete;
		extern CSCORE_API const Type ECsSkeletalMeshActorDeallocateMethod_MAX;
	}

	extern CSCORE_API const uint8 MAX;
}

namespace NCsSkeletalMeshActor
{
	enum class EDeallocateMethod : uint8
	{
		/** If a SkeletalMeshActor is attached to a parent object,
			  LifeTime == 0.of means the SkeletalMeshActor will be deallocated immediately
			   when the parent has been destroyed / deallocated.
			  LifeTime > 0.0f will be the time after the parent object has been
			   destroyed / deallocated to deallocate the SkeletalMeshActor.
			If a SkeletalMeshActor is NOT attached to a parent object,
			  LifeTime == 0.0f means the SkeletalMeshActor will stay active forever.
			  LifeTime > 0.0f means the SkeletalMeshActor will be deallocated after LifeTime amount of time after
			   the SkeletalMeshActor has been allocated. */
		LifeTime,
		/** */
		Complete,
		EDeallocateMethod_MAX
	};
}

#pragma endregion SkeletalMeshActorDeallocateMethod

// FCsSkeletalMeshActorPooledInfo
#pragma region

class USkeletalMesh;

/**
* Container holding general information for a Sound Asset.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsSkeletalMeshActorPooledInfo
{
	GENERATED_USTRUCT_BODY()

	/** Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FCsSkeletalMesh Mesh;

	/** Materials */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FCsTArrayMaterialnterface Materials;

	/** The SkeletalMeshActor Type. This is used to group SkeletalMeshActors into different categories 
	    and can be used by a Manager pooling SkeletalMeshActors to Spawn the correct
		SkeletalMeshActor. 
		NOTE: SkeletalMeshActor mostly acts as a "container" for a USkeletalMesh. Unless there is a
		need from some special logic, only one SkeletalMeshActor class (i.e. ACsStatMeshActorPooledImpl) 
		that will be used. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FECsSkeletalMeshActor Type;

	/** Condition to determine when to deallocate the SkeletalMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	ECsSkeletalMeshActorDeallocateMethod DeallocateMethod;

private:

	NCsSkeletalMeshActor::EDeallocateMethod* DeallocateMethod_Internal;

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

	FCsSkeletalMeshActorPooledInfo() :
		Mesh(),
		Materials(),
		Type(),
		DeallocateMethod(ECsSkeletalMeshActorDeallocateMethod::Complete),
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

	FORCEINLINE void UpdateDeallocateMethodPtr() { DeallocateMethod_Internal = (NCsSkeletalMeshActor::EDeallocateMethod*)&DeallocateMethod; }

#define DeallocateMethodType NCsSkeletalMeshActor::EDeallocateMethod

	FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *DeallocateMethod_Internal; }

	FORCEINLINE DeallocateMethodType* GetDeallocateMethodPtr() const { return DeallocateMethod_Internal; }

#undef DeallocateMethodType

	bool IsValidChecked(const FString& Context) const;
};

#pragma endregion FCsSkeletalMeshActorPooledInfo

// NCsSkeletalMeshActor::NPayload::EChange
#pragma region

namespace NCsSkeletalMeshActor
{
	namespace NPayload
	{
		enum class EChange : uint32
		{
			SkeletalMesh					= 1 << 0,
			Materials						= 1 << 1,
			KeepRelativeTransform			= 1 << 2,
			KeepWorldTransform				= 1 << 3,
			SnapToTargetNotIncludingScale	= 1 << 4,
			SnapToTargetIncludingScale		= 1 << 5,
			Transform						= 1 << 6,
			AnimInstance					= 1 << 7
		};

		namespace NChange
		{
			FORCEINLINE bool HasAttach(const uint32& Mask)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale))
					return true;
				return false;
			}

			FORCEINLINE bool HasAttach(const uint32& Mask, const ECsAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					Rules == ECsAttachmentTransformRules::KeepRelativeTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					Rules == ECsAttachmentTransformRules::KeepWorldTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					Rules == ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					Rules == ECsAttachmentTransformRules::SnapToTargetIncludingScale)
					return true;
				return false;
			}

			FORCEINLINE uint32 GetAttachAsMask(const uint32& Mask)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform))
					return (uint32)EChange::KeepRelativeTransform;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform))
					return (uint32)EChange::KeepWorldTransform;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale))
					return (uint32)EChange::SnapToTargetNotIncludingScale;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale))
					return (uint32)EChange::SnapToTargetIncludingScale;
				return 0;
			}

			FORCEINLINE EChange FromTransformAttachmentRule(const ECsAttachmentTransformRules& Rules)
			{
				if (Rules == ECsAttachmentTransformRules::KeepRelativeTransform)
					return EChange::KeepRelativeTransform;
				if (Rules == ECsAttachmentTransformRules::KeepWorldTransform)
					return EChange::KeepWorldTransform;
				if (Rules == ECsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return EChange::SnapToTargetNotIncludingScale;
				if (Rules == ECsAttachmentTransformRules::SnapToTargetIncludingScale)
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			struct CSCORE_API FCounter
			{
			protected:
				FCounter() :
					Preserved(0),
					PreservedPercent(0.0f),
					Changed(0),
					ChangedPercent(0.0f),
					Cleared(0),
					ClearedPercent(0.0f),
					Total(0)
				{
				}
				FCounter(const FCounter&) = delete;
				FCounter(FCounter&&) = delete;
			public:
				virtual ~FCounter() {}
			private:
				uint32 Preserved;
				float PreservedPercent;
				uint32 Changed;
				float ChangedPercent;
				uint32 Cleared;
				float ClearedPercent;
				uint32 Total;
			public:
				static FCounter& Get()
				{
					static FCounter Instance;
					return Instance;
				}

			public:

				FORCEINLINE void AddPreserved()
				{
					++Preserved;
					++Total;
					PreservedPercent = (float)Preserved/(float)Total;
				}

				FORCEINLINE void AddChanged()
				{
					++Changed;
					++Total;
					ChangedPercent = (float)Changed/(float)Total;
				}

				FORCEINLINE void AddCleared()
				{
					++Cleared;
					++Total;
					ClearedPercent = (float)Cleared/(float)Total;
				}

				void Reset()
				{
					Preserved = 0;
					PreservedPercent = 0.0f;
					Changed = 0;
					ChangedPercent = 0.0f;
					Cleared = 0;
					ClearedPercent = 0.0f;
					Total = 0;
				}

				FORCEINLINE FString ToString() const
				{
					return FString::Printf(TEXT("Preserved: (%3.3f = %d/%d) Changed: (%3.3f = %d/%d) Cleared: (%3.3f = %d/%d)"), PreservedPercent, Preserved, Total, ChangedPercent, Changed, Total, ClearedPercent, Cleared, Total);
				}
			};
		}
	}
}

#pragma endregion NCsSkeletalMeshActor::NPayload::EChange