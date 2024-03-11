// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#pragma once
#include "Types/Enum/CsEnum_uint8.h"
#include "Types/Enum/CsEnumStructMap.h"
#include "Types/Enum/CsEnumMap.h"
#include "Types/Enum/CsEnumFlagMap.h"
#include "Types/CsTypes_AttachDetach.h"
#include "Types/CsTypes_StaticMesh.h"
#include "Material/CsTypes_Material.h"

#include "CsTypes_StaticMeshActor.generated.h"

// StaticMeshActor
#pragma region

USTRUCT(BlueprintType)
struct CSSTATICMESH_API FECsStaticMeshActor : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStaticMeshActor)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStaticMeshActor)

struct CSSTATICMESH_API EMCsStaticMeshActor : public TCsEnumStructMap<FECsStaticMeshActor, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStaticMeshActor, FECsStaticMeshActor, uint8)
};

namespace NCsStaticMeshActor
{
	typedef EMCsStaticMeshActor EnumMapType;
	typedef FECsStaticMeshActor Type;

	FORCEINLINE void Create(const FString& Name, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, UserDefinedEnum); }
	FORCEINLINE void CreateCustom(const FString& Name, const FString& DisplayName, const bool& UserDefinedEnum) { EnumMapType::Get().Create(Name, DisplayName, UserDefinedEnum); }
	FORCEINLINE bool IsValidEnum(const FString& Name) { return EnumMapType::Get().IsValidEnum(Name); }
	FORCEINLINE bool IsValidEnumByDisplayName(const FString& DisplayName) { return EnumMapType::Get().IsValidEnumByDisplayName(DisplayName); }

	CSSTATICMESH_API void FromEnumSettings(const FString& Context);

	CSSTATICMESH_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);

	CSSTATICMESH_API const FECsStaticMeshActor& GetDefault();
}

#pragma endregion StaticMeshActor

// StaticMeshActorClass
#pragma region

USTRUCT(BlueprintType)
struct CSSTATICMESH_API FECsStaticMeshActorClass : public FECsEnum_uint8
{
	GENERATED_USTRUCT_BODY()

	CS_ENUM_UINT8_BODY(FECsStaticMeshActorClass)
};

CS_DEFINE_ENUM_UINT8_GET_TYPE_HASH(FECsStaticMeshActorClass)

struct CSSTATICMESH_API EMCsStaticMeshActorClass : public TCsEnumStructMap<FECsStaticMeshActorClass, uint8>
{
	CS_ENUM_STRUCT_MAP_BODY(EMCsStaticMeshActorClass, FECsStaticMeshActorClass, uint8)
};

namespace NCsStaticMeshActorClass
{
	typedef FECsStaticMeshActorClass Type;

	namespace Ref
	{
	}

	CSSTATICMESH_API void PopulateEnumMapFromSettings(const FString& Context, UObject* ContextRoot);
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

struct CSSTATICMESH_API EMCsStaticMeshActorDeallocateMethod final : public TCsEnumMap<ECsStaticMeshActorDeallocateMethod>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsStaticMeshActorDeallocateMethod, ECsStaticMeshActorDeallocateMethod)
};

namespace NCsStaticMeshActorDeallocateMethod
{
	typedef ECsStaticMeshActorDeallocateMethod Type;

	namespace Ref
	{
		extern CSSTATICMESH_API const Type LifeTime;
		extern CSSTATICMESH_API const Type Complete;
		extern CSSTATICMESH_API const Type ECsStaticMeshActorDeallocateMethod_MAX;
	}

	extern CSSTATICMESH_API const uint8 MAX;
}

namespace NCsStaticMeshActor
{
	enum class EDeallocateMethod : uint8
	{
		/** If a StaticMeshActor is attached to a parent object,
			  LifeTime == 0.0f means the StaticMeshActor will be deallocated immediately
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

// NCsStaticMeshActor::NPayload::FImpl
CS_FWD_DECLARE_STRUCT_NAMESPACE_2(NCsStaticMeshActor, NPayload, FImpl)

/**
* Container holding general information for a Static Mesh Actor.
*  This is mostly used by object pooled by a Manager
*/
USTRUCT(BlueprintType)
struct CSSTATICMESH_API FCsStaticMeshActorPooledInfo
{
	GENERATED_USTRUCT_BODY()

	/** Mesh */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FCsStaticMesh Mesh;

	/** Materials */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FCsTArrayMaterialInterface Materials;

	/** The StaticMeshActor Type. This is used to group StaticMeshActors into different categories 
	    and can be used by a Manager pooling StaticMeshActors to Spawn the correct
		StaticMeshActor. 
		NOTE: StaticMeshActor mostly acts as a "container" for a UStaticMesh. Unless there is a
		need from some special logic, only one StaticMeshActor class (i.e. ACsStatMeshActorPooledImpl) 
		that will be used. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FECsStaticMeshActor Type;

	/** Condition to determine when to deallocate the StaticMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	ECsStaticMeshActorDeallocateMethod DeallocateMethod;

	/** Valid if the DeallocateMethod == ECsStaticMeshActorDeallocateMethod::LifeTime.
		- If a Sound IS attached to a Parent object, 
		   LifeTime == 0.of means the Sound object will be deallocated immediately
	        when the Parent object has been destroyed / deallocated.
		   LifeTime > 0.0f will be the time after the Parent object has been 
		    destroyed / deallocated to deallocate the Sound object.
	    - If a Sound is NOT attached to a Parent object,
		   LifeTime == 0.0f means the StaticMeshActor object will stay active forever.
		   LifeTime > 0.0f means the StaticMeshActor will be deallocated after LifeTime amount of time after
	        the FX object has been allocated. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float LifeTime;

	/** Valid if the StaticMeshActor is attached to a Parent object or when an StaticMeshActor object is
		allocated, the Parent field of the payload is set. If the Parent object is NULL,
		the Sound will NOT be attached. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FCsAttachmentTransformRules AttachmentTransformRules;

	/** Valid only when the StaticMeshActor is attached to a Parent object. 
	    Bone or Socket to attach to. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FName Bone;

	/** Which of the components of Transform to apply to the StaticMeshActor. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (Bitmask, BitmaskEnum = "/Script.CsCore.ECsTransformRules"))
	int32 TransformRules;

	/** The Transform to apply to the StaticMeshActor.
		If the StaticMeshActor is attached to a parent object, the Transform is applied as a Relative Transform
		after the attachment.
	    Else, the Transform is applied as a World Transform. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	FTransform3f Transform;

	/** Controls whether the StaticMeshComponent should cast a shadow or not. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bCastShadow;

	/** Whether the StaticMeshComponent receives decals. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bReceivesDecals;

	/** Whether to render the StatisMeshComponent in the depth only pass.
		This should generally be true for all objects, and let the renderer make decisions about whether to render objects in the depth only pass. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bUseAsOccluder;

	/** If true, the StatisMeshComponent will be rendered in the CustomDepth pass (usually used for outlines) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh")
	bool bRenderCustomDepth;

	/** Optionally write this 0-255 value to the stencil buffer in CustomDepth pass (Requires project setting or r.CustomDepth == 3) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Static Mesh", meta = (UIMin = "0", ClampMin = "0", UIMax = "255", ClampMax = "255"))
	int32 CustomDepthStencilValue;

public:

	FCsStaticMeshActorPooledInfo() :
		Mesh(),
		Materials(),
		Type(),
		DeallocateMethod(ECsStaticMeshActorDeallocateMethod::Complete),
		LifeTime(0.0f),
		AttachmentTransformRules(FCsAttachmentTransformRules::SnapToTargetNotIncludingScale),
		Bone(NAME_None),
		TransformRules(7), // NCsTransformRules::All
		Transform(FTransform3f::Identity),
		bCastShadow(false),
		bReceivesDecals(false),
		bUseAsOccluder(false),
		bRenderCustomDepth(false),
		CustomDepthStencilValue(0)
	{
	}

#define DeallocateMethodType NCsStaticMeshActor::EDeallocateMethod

	FORCEINLINE FECsStaticMeshActor* GetTypePtr() { return &Type; }
	FORCEINLINE const DeallocateMethodType& GetDeallocateMethod() const { return *((NCsStaticMeshActor::EDeallocateMethod*)(&DeallocateMethod)); }
	FORCEINLINE DeallocateMethodType* GetDeallocateMethodPtr() const { return const_cast<DeallocateMethodType*>(&GetDeallocateMethod()); }
	FORCEINLINE float* GetLifeTimePtr() { return &LifeTime; }
	FORCEINLINE FCsAttachmentTransformRules* GetAttachmentTransformRulesPtr() { return &AttachmentTransformRules; }
	FORCEINLINE FName* GetBonePtr() { return &Bone; }
	FORCEINLINE int32* GetTransformRulesPtr() { return &TransformRules; }
	FORCEINLINE FTransform3f* GetTransformPtr() { return &Transform; }

#undef DeallocateMethodType

#define PayloadType NCsStaticMeshActor::NPayload::FImpl
	void SetPayloadChecked(const FString& Context, PayloadType* Payload) const;
	bool SetSafePayload(const FString& Context, PayloadType* Payload, void(*Log)(const FString&) = &FCsLog::Warning) const;
#undef PayloadType

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsStaticMeshActorPooledInfo

// NCsStaticMeshActor::NPayload::EChange
#pragma region

UENUM(BlueprintType, meta = (Bitflags))
enum class ECsStaticMeshPayloadChange : uint8
{
	StaticMesh						UMETA(DisplayName = "StaticMesh"),							// 0
	Materials						UMETA(DisplayName = "Materials"),							// 1
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),				// 2
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),				// 3
	SnapToTargetNotIncludingScale	UMETA(DisplayName = "Snap to Target not Including Scale"),	// 4
	SnapToTargetIncludingScale		UMETA(DisplayName = "Snap to Target Including Scale"),		// 5
	Transform						UMETA(DisplayName = "Transform"),							// 6
};

struct CSSTATICMESH_API EMCsStaticMeshPayloadChange : public TCsEnumFlagMap<ECsStaticMeshPayloadChange>
{
	CS_ENUM_FLAG_MAP_BODY(EMCsStaticMeshPayloadChange, ECsStaticMeshPayloadChange)
};

namespace NCsStaticMeshPayloadChange
{
	typedef ECsStaticMeshPayloadChange Type;

	namespace Ref
	{
		extern CSSTATICMESH_API const Type StaticMesh;
		extern CSSTATICMESH_API const Type Materials;
		extern CSSTATICMESH_API const Type KeepRelativeTransform;
		extern CSSTATICMESH_API const Type KeepWorldTransform;
		extern CSSTATICMESH_API const Type SnapToTargetNotIncludingScale;
		extern CSSTATICMESH_API const Type SnapToTargetIncludingScale;
		extern CSSTATICMESH_API const Type Transform;
	}

	extern CSSTATICMESH_API const int32 None;
	extern CSSTATICMESH_API const int32 All;
}

#define CS_STATIC_MESH_PAYLOAD_CHANGE_NONE 0

namespace NCsStaticMeshActor
{
	namespace NPayload
	{
		enum class EChange : uint32
		{
			StaticMesh						= 1 << 0,
			Materials						= 1 << 1,
			KeepRelativeTransform			= 1 << 2,
			KeepWorldTransform				= 1 << 3,
			SnapToTargetNotIncludingScale	= 1 << 4,
			SnapToTargetIncludingScale		= 1 << 5,
			Transform						= 1 << 6
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

			FORCEINLINE bool HasAttach(const uint32& Mask, const FCsAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					Rules == FCsAttachmentTransformRules::KeepRelativeTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					Rules == FCsAttachmentTransformRules::KeepWorldTransform)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					Rules == FCsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					Rules == FCsAttachmentTransformRules::SnapToTargetIncludingScale)
					return true;
				return false;
			}

			FORCEINLINE bool HasAttach(const uint32& Mask, const FAttachmentTransformRules& Rules)
			{
				if (CS_TEST_BITFLAG(Mask, EChange::KeepRelativeTransform) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepRelativeTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::KeepWorldTransform) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepWorldTransform))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetNotIncludingScale) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetNotIncludingScale))
					return true;
				if (CS_TEST_BITFLAG(Mask, EChange::SnapToTargetIncludingScale) &&
					FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetIncludingScale))
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

			FORCEINLINE EChange FromTransformAttachmentRule(const FCsAttachmentTransformRules& Rules)
			{
				if (Rules == FCsAttachmentTransformRules::KeepRelativeTransform)
					return EChange::KeepRelativeTransform;
				if (Rules == FCsAttachmentTransformRules::KeepWorldTransform)
					return EChange::KeepWorldTransform;
				if (Rules == FCsAttachmentTransformRules::SnapToTargetNotIncludingScale)
					return EChange::SnapToTargetNotIncludingScale;
				if (Rules == FCsAttachmentTransformRules::SnapToTargetIncludingScale)
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			FORCEINLINE EChange FromTransformAttachmentRule(const FAttachmentTransformRules& Rules)
			{
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepRelativeTransform))
					return EChange::KeepRelativeTransform;
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::KeepWorldTransform))
					return EChange::KeepWorldTransform;
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetNotIncludingScale))
					return EChange::SnapToTargetNotIncludingScale;
				if (FCsAttachmentTransformRules::IsEqual(Rules, FAttachmentTransformRules::SnapToTargetIncludingScale))
					return EChange::SnapToTargetIncludingScale;
				return EChange::KeepRelativeTransform;
			}

			struct CSSTATICMESH_API FCounter
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

#pragma endregion NCsStaticMeshActor::NPayload::EChange