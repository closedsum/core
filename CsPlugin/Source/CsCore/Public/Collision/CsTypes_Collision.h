// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Types/CsTypes_Physics.h"
#include "CollisionShape.h"
#include "Engine/EngineTypes.h"
// Log
#include "Utility/CsLog.h"

#include "CsTypes_Collision.generated.h"

// TraceTypeQuery
#pragma region

/**
*/
struct CSCORE_API EMCsTraceTypeQuery final : public TCsEnumMap<ETraceTypeQuery>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsTraceTypeQuery, ETraceTypeQuery)
};

namespace NCsTraceTypeQuery
{
	typedef ETraceTypeQuery Type;

	namespace Ref
	{
		extern CSCORE_API const Type TraceTypeQuery1;
		extern CSCORE_API const Type TraceTypeQuery2;
		extern CSCORE_API const Type TraceTypeQuery3;
		extern CSCORE_API const Type TraceTypeQuery4;
		extern CSCORE_API const Type TraceTypeQuery5;
		extern CSCORE_API const Type TraceTypeQuery6;
		extern CSCORE_API const Type TraceTypeQuery7;
		extern CSCORE_API const Type TraceTypeQuery8;
		extern CSCORE_API const Type TraceTypeQuery9;
		extern CSCORE_API const Type TraceTypeQuery10;
		extern CSCORE_API const Type TraceTypeQuery11;
		extern CSCORE_API const Type TraceTypeQuery12;
		extern CSCORE_API const Type TraceTypeQuery13;
		extern CSCORE_API const Type TraceTypeQuery14;
		extern CSCORE_API const Type TraceTypeQuery15;
		extern CSCORE_API const Type TraceTypeQuery16;
		extern CSCORE_API const Type TraceTypeQuery17;
		extern CSCORE_API const Type TraceTypeQuery18;
		extern CSCORE_API const Type TraceTypeQuery19;
		extern CSCORE_API const Type TraceTypeQuery20;
		extern CSCORE_API const Type TraceTypeQuery21;
		extern CSCORE_API const Type TraceTypeQuery22;
		extern CSCORE_API const Type TraceTypeQuery23;
		extern CSCORE_API const Type TraceTypeQuery24;
		extern CSCORE_API const Type TraceTypeQuery25;
		extern CSCORE_API const Type TraceTypeQuery26;
		extern CSCORE_API const Type TraceTypeQuery27;
		extern CSCORE_API const Type TraceTypeQuery28;
		extern CSCORE_API const Type TraceTypeQuery29;
		extern CSCORE_API const Type TraceTypeQuery30;
		extern CSCORE_API const Type TraceTypeQuery31;
		extern CSCORE_API const Type TraceTypeQuery32;

		extern CSCORE_API const Type TraceTypeQuery_MAX;
	}
}

#pragma endregion TraceTypeQuery

// CollisionEnabled
#pragma region

/**
*/
struct CSCORE_API EMCollisionEnabled final : public TCsEnumMap<ECollisionEnabled::Type>
{
	CS_ENUM_MAP_BODY(EMCollisionEnabled, ECollisionEnabled::Type)
};

namespace ECollisionEnabled
{
	namespace Ref
	{
		extern CSCORE_API const Type NoCollision;
		extern CSCORE_API const Type QueryOnly;
		extern CSCORE_API const Type PhysicsOnly;
		extern CSCORE_API const Type QueryAndPhysics;
	}
}

#pragma endregion CollisionEnabled

// CollisionChannel
#pragma region

/**
*/
struct CSCORE_API EMCsCollisionChannel final : public TCsEnumMap<ECollisionChannel>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsCollisionChannel, ECollisionChannel)
};

namespace NCsCollisionChannel
{
	typedef ECollisionChannel Type;

	namespace Ref
	{
		extern CSCORE_API const Type ECC_WorldStatic;
		extern CSCORE_API const Type ECC_WorldDynamic;
		extern CSCORE_API const Type ECC_Pawn;
		extern CSCORE_API const Type ECC_Visibility;
		extern CSCORE_API const Type ECC_Camera;
		extern CSCORE_API const Type ECC_PhysicsBody;
		extern CSCORE_API const Type ECC_Vehicle;
		extern CSCORE_API const Type ECC_Destructible;

		extern CSCORE_API const Type ECC_EngineTraceChannel1;
		extern CSCORE_API const Type ECC_EngineTraceChannel2;
		extern CSCORE_API const Type ECC_EngineTraceChannel3;
		extern CSCORE_API const Type ECC_EngineTraceChannel4;
		extern CSCORE_API const Type ECC_EngineTraceChannel5;
		extern CSCORE_API const Type ECC_EngineTraceChannel6;

		extern CSCORE_API const Type ECC_GameTraceChannel1;
		extern CSCORE_API const Type ECC_GameTraceChannel2;
		extern CSCORE_API const Type ECC_GameTraceChannel3;
		extern CSCORE_API const Type ECC_GameTraceChannel4;
		extern CSCORE_API const Type ECC_GameTraceChannel5;
		extern CSCORE_API const Type ECC_GameTraceChannel6;
		extern CSCORE_API const Type ECC_GameTraceChannel7;
		extern CSCORE_API const Type ECC_GameTraceChannel8;
		extern CSCORE_API const Type ECC_GameTraceChannel9;
		extern CSCORE_API const Type ECC_GameTraceChannel10;
		extern CSCORE_API const Type ECC_GameTraceChannel11;
		extern CSCORE_API const Type ECC_GameTraceChannel12;
		extern CSCORE_API const Type ECC_GameTraceChannel13;
		extern CSCORE_API const Type ECC_GameTraceChannel14;
		extern CSCORE_API const Type ECC_GameTraceChannel15;
		extern CSCORE_API const Type ECC_GameTraceChannel16;
		extern CSCORE_API const Type ECC_GameTraceChannel17;
		extern CSCORE_API const Type ECC_GameTraceChannel18;

		extern CSCORE_API const Type ECC_MAX;
	}
}

#pragma endregion CollisionChannel

// CollisionResponse
#pragma region

/**
*/
struct CSCORE_API EMCollisionResponse final : public TCsEnumMap<ECollisionResponse>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCollisionResponse, ECollisionResponse)
};

namespace NCsCollisionResponse
{
	typedef ECollisionResponse Type;

	namespace Ref
	{
		extern CSCORE_API const Type ECR_Ignore;
		extern CSCORE_API const Type ECR_Overlap;
		extern CSCORE_API const Type ECR_Block;
		extern CSCORE_API const Type ECR_MAX;
	}
};

#pragma endregion CollisionResponse

// CollisionShape
#pragma region

/**
*/
struct CSCORE_API EMCsCollisionShape final : public TCsEnumMap<ECollisionShape::Type>
{
	CS_ENUM_MAP_BODY(EMCsCollisionShape, ECollisionShape::Type)
};

namespace NCsCollisionShape
{
	typedef ECollisionShape::Type Type;

	namespace Ref
	{
		extern CSCORE_API const Type Line;
		extern CSCORE_API const Type Box;
		extern CSCORE_API const Type Sphere;
		extern CSCORE_API const Type Capsule;
	}
}

UENUM(BlueprintType)
enum class ECsCollisionShapeType : uint8
{
	Line						UMETA(DisplayName = "Line"),
	Box							UMETA(DisplayName = "Box"),
	Sphere						UMETA(DisplayName = "Sphere"),
	Capsule						UMETA(DisplayName = "Capsule"),
	ECsCollisionShapeType_MAX	UMETA(Hidden),
};

#pragma endregion CollisionShape

// FCsCollisionShape
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionShape
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	ECsCollisionShapeType Type;

	/** Only Valid if Type == ECsCollisionShapeType::Box. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	FVector HalfExtent;

	/** Only Valid if 
		 Type == ECsCollisionShapeType::Sphere
		 Type == ECsCollisionShapeType::Capsule */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float Radius;

	/** Only Valid if Type == ECsCollisionShapeType::Capsule */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision", meta = (UIMin = "0.0", ClampMin = "0.0"))
	float HalfHeight;

	FCsCollisionShape() :
		Type(ECsCollisionShapeType::Line),
		HalfExtent(FVector::ZeroVector),
		Radius(0.0f),
		HalfHeight(0.0f)
	{
	}

	FCollisionShape ToShape() const;

	FORCEINLINE bool IsLine() const { return Type == ECsCollisionShapeType::Line; }
	FORCEINLINE bool IsBox() const { return Type == ECsCollisionShapeType::Box; }
	FORCEINLINE bool IsSphere() const { return Type == ECsCollisionShapeType::Sphere; }
	FORCEINLINE bool IsCapsule() const { return Type == ECsCollisionShapeType::Capsule; }

	void Reset()
	{
		Type = ECsCollisionShapeType::Line;
		HalfExtent = FVector::ZeroVector;
		Radius = 0.0f;
		HalfHeight = 0.0f;
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsCollisionShape

namespace NCsCollisionResponseContainer
{
	static bool IsValid(const FString& Context, const FCollisionResponseContainer& CollisionResponses, void(*Log)(const FString&) = &FCsLog::Warning)
	{
		bool bAllIgnore = true;

		for (const ECollisionChannel& Channel : EMCsCollisionChannel::Get())
		{
			const ECollisionResponse Response = CollisionResponses.GetResponse(Channel);

			if (Response != ECR_Ignore &&
				Response != ECR_MAX)
			{
				bAllIgnore = false;
				break;
			}
		}

		if (bAllIgnore)
		{
			if (Log)
				Log(FString::Printf(TEXT("%s: ALL channels in CollisionResponses are either ECollisionResponse::ECR_Ignore or ECollisionResponse::ECR_MAX. At least ONE channel must be ECollisionResponse::ECR_Overlap or ECollisionResponse::ECR_Block."), *Context));
		}
		return !bAllIgnore;
	}

	static uint32 GetBlockMask(const FCollisionResponseContainer& CollisionResponses)
	{
		uint32 Mask = 0;

		for (const ECollisionChannel& Channel : EMCsCollisionChannel::Get())
		{
			const ECollisionResponse Response = CollisionResponses.GetResponse(Channel);

			if (Response == ECR_Block)
			{
				Mask |= (1 << (uint8)Channel);
			}
		}
		return Mask;
	}
}

// FCsCollisionPreset
#pragma region

class UPrimitiveComponent;

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionPreset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bSimulationGeneratesHitEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	FCsPhysicalMaterial PhysMaterialOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bGenerateOverlapEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	TEnumAsByte<ECollisionEnabled::Type> CollisionEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	FCollisionResponseContainer CollisionResponses;

	FCsCollisionPreset() :
		bSimulationGeneratesHitEvents(false),
		bGenerateOverlapEvents(false),
		CollisionEnabled(ECollisionEnabled::NoCollision),
		ObjectType(ECollisionChannel::ECC_WorldStatic),
		CollisionResponses()
	{
		CollisionResponses.SetAllChannels(ECR_Ignore);
	}

	FORCEINLINE bool operator==(const FCsCollisionPreset& B) const
	{
		return bSimulationGeneratesHitEvents == B.bSimulationGeneratesHitEvents && 
			   bGenerateOverlapEvents == B.bGenerateOverlapEvents && 
			   PhysMaterialOverride == B.PhysMaterialOverride &&
			   CollisionEnabled == B.CollisionEnabled && 
			   ObjectType == B.ObjectType;
	}

	FORCEINLINE bool operator!=(const FCsCollisionPreset& B) const
	{
		return !(*this == B);
	}

	void SetChecked(const FString& Context, UPrimitiveComponent* Component) const;
	bool SetSafe(const FString& Context, UPrimitiveComponent* Component, void(*Log)(const FString&) = &FCsLog::Warning) const;

	bool IsValidChecked(const FString& Context) const;
	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;

	FORCEINLINE uint32 GetObjectMask() const { return (1 << (uint8)ObjectType); }
	FORCEINLINE uint32 GetBlockMask() const { return NCsCollisionResponseContainer::GetBlockMask(CollisionResponses); }
};

#pragma endregion FCsCollisionPreset

// FCsOnComponentBeginOverlapInfo
#pragma region

class UPrimitiveComponent;
class AActor;

USTRUCT(Blueprintable, BlueprintType)
struct FCsOnComponentBeginOverlapInfo
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	UPrimitiveComponent* OverlappedComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	AActor* OtherActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	UPrimitiveComponent* OtherComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	int32 OtherBodyIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bFromSweep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	FHitResult SweepResult;

	FCsOnComponentBeginOverlapInfo() :
		OverlappedComponent(nullptr),
		OtherActor(nullptr),
		OtherComponent(nullptr),
		OtherBodyIndex(INDEX_NONE),
		bFromSweep(false),
		SweepResult()
	{
	}
};

#pragma endregion FCsOnComponentBeginOverlapInfo

// Collision
#pragma region

namespace NCsCollision
{
	namespace NHit
	{
		extern CSCORE_API const FHitResult Default;
	}
}

#pragma endregion Collision

// QueryMobilityType
#pragma region

UENUM(BlueprintType)
enum class ECsQueryMobilityType : uint8
{
	Any							UMETA(DisplayName = "Any"),
	/** Any shape that is considered static by physx (static mobility) */
	Static						UMETA(DisplayName = "Static"),
	/** Any shape that is considered dynamic by physx (movable/stationary mobility) */
	Dynamic						UMETA(DisplayName = "Dynamic"),
	ECsQueryMobilityType_MAX	UMETA(Hidden),
};

#pragma endregion QueryMobilityType

namespace NCsCollisionQueryParams
{
	CSCORE_API void ResetComponentListUnique(FCollisionQueryParams& Params);

	CSCORE_API TArray<uint32, TInlineAllocator<8>>& GetIgnoreComponents(FCollisionQueryParams& Params);

	CSCORE_API TArray<uint32, TInlineAllocator<4>>& GetIgnoreActors(FCollisionQueryParams& Params);

	CSCORE_API void ConditionalResetIgnoreComponents(FCollisionQueryParams& Params);

	CSCORE_API void ConditionalResetIgnoreActors(FCollisionQueryParams& Params);

	CSCORE_API void Reset(FCollisionQueryParams& Params);
}

// FCsCollisionQueryParams
#pragma region

class UPrimitiveComponent;
class AActor;

/** 
* Structure that defines parameters passed into collision function 
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionQueryParams
{
	GENERATED_USTRUCT_BODY()

	/** Tag used to provide extra information or filtering for debugging of the trace (e.g. Collision Analyzer) */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	FName TraceTag;

	/** Tag used to indicate an owner for this trace */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	FName OwnerTag;

	/** Whether we should trace against complex collision */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bTraceComplex;

	/** Whether we want to find out initial overlap or not. If true, it will return if this was initial overlap. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bFindInitialOverlaps;

	/** Whether we want to return the triangle face index for complex static mesh traces */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bReturnFaceIndex;

	/** Whether we want to include the physical material in the results. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bReturnPhysicalMaterial;

	/** Whether to ignore blocking results. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bIgnoreBlocks;

	/** Whether to ignore touch/overlap results. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bIgnoreTouches;

	/** Whether to skip narrow phase checks (only for overlaps). */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	bool bSkipNarrowPhase;

	/** Filters query by mobility types (static vs stationary/movable)*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	ECsQueryMobilityType MobilityType;

	/** TArray typedef of components to ignore. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	TArray<UPrimitiveComponent*> IgnoreComponents;

	/** TArray typedef of actors to ignore. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	TArray<AActor*> IgnoreActors;

	FCsCollisionQueryParams() :
		TraceTag(NAME_None),
		OwnerTag(NAME_None),
		bTraceComplex(false),
		bFindInitialOverlaps(true),
		bReturnFaceIndex(false),
		bReturnPhysicalMaterial(false),
		bIgnoreBlocks(false),
		bIgnoreTouches(false),
		bSkipNarrowPhase(false),
		MobilityType(ECsQueryMobilityType::Any),
		IgnoreComponents(),
		IgnoreActors()
	{
	}

	void CopyToParams(FCollisionQueryParams& Params) const
	{
		Params.TraceTag = TraceTag;
		Params.OwnerTag = OwnerTag;
		Params.bTraceComplex = bTraceComplex;
		Params.bFindInitialOverlaps = bFindInitialOverlaps;
		Params.bReturnFaceIndex = bReturnFaceIndex;
		Params.bReturnPhysicalMaterial = bReturnPhysicalMaterial;
		Params.bIgnoreBlocks = bIgnoreBlocks;
		Params.bIgnoreTouches = bIgnoreTouches;
		Params.bSkipNarrowPhase = bSkipNarrowPhase;
		Params.MobilityType = (EQueryMobilityType)MobilityType;

		NCsCollisionQueryParams::ResetComponentListUnique(Params);
		NCsCollisionQueryParams::ConditionalResetIgnoreComponents(Params);
		Params.AddIgnoredComponents(IgnoreComponents);
		NCsCollisionQueryParams::ConditionalResetIgnoreActors(Params);
		Params.AddIgnoredActors(IgnoreActors);
	}

	void Reset()
	{
		TraceTag = NAME_None;
		OwnerTag = NAME_None;
		bTraceComplex = false;
		bFindInitialOverlaps = false;
		bReturnFaceIndex = false;
		bReturnPhysicalMaterial = false;
		bIgnoreBlocks = false;
		bIgnoreTouches = false;
		bSkipNarrowPhase = false;
		MobilityType = ECsQueryMobilityType::Any;
		IgnoreComponents.Reset(8);
		IgnoreActors.Reset(4);
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsCollisionQueryParams

// FCsCollisionObjectQueryParams
#pragma region

/** 
* Structure that contains list of object types the query is interested in.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionObjectQueryParams
{
	GENERATED_USTRUCT_BODY()

	/** Set of object type queries that it is interested in **/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CsCore|Collision")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypesToQuery;

	FCsCollisionObjectQueryParams() :
		ObjectTypesToQuery()
	{
	}

	void CopyToParams(FCollisionObjectQueryParams& Params) const
	{
		Params = FCollisionObjectQueryParams(ObjectTypesToQuery);
	}

	void Reset()
	{
		ObjectTypesToQuery.Reset(ObjectTypesToQuery.Max());
	}

	bool IsValid(const FString& Context, void(*Log)(const FString&) = &FCsLog::Warning) const;
};

#pragma endregion FCsCollisionObjectQueryParams

// FCsCollisionResponseParams
#pragma region

/** 
* Structure that defines response container for the query. Advanced option. 
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionResponseParams
{
	/** Collision Response container for trace filtering. If you'd like to ignore certain channel for this trace, use this struct.
		By default, every channel will be blocked. */
	GENERATED_USTRUCT_BODY()
	FCollisionResponseContainer CollisionResponse;

	FCsCollisionResponseParams() :
		CollisionResponse()
	{
	}

	void CopyToParams(FCollisionResponseParams& Params) const
	{
		Params = FCollisionResponseParams(CollisionResponse);
	}

	void Reset()
	{
		CollisionResponse = FCollisionResponseContainer::GetDefaultResponseContainer();
	}
};

#pragma endregion FCsCollisionResponseParams

namespace NCsHitResult
{
	CSCORE_API EPhysicalSurface GetPhysSurfaceType(const FHitResult& Hit);
}