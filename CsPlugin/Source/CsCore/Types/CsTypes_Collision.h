// Copyright 2017-2019 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_Physics.h"
#include "Engine/EngineTypes.h"
#include "Types/Enum/CsEnumMap.h"

#include "CsTypes_Collision.generated.h"
#pragma once

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

// FCsCollisionPreset
#pragma region

/**
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsCollisionPreset
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	bool bSimulationGeneratesHitEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	FCsPhysicalMaterial PhysMaterialOverride;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	bool bGenerateOverlapEvents;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TEnumAsByte<ECollisionEnabled::Type> CollisionEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
	TEnumAsByte<ECollisionChannel> ObjectType;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collision")
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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* OverlappedComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* OtherActor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UPrimitiveComponent* OtherComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 OtherBodyIndex;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bFromSweep;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
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