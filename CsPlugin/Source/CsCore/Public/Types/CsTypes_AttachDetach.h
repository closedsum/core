// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Engine/EngineTypes.h"

#include "CsTypes_AttachDetach.generated.h"

// AttachmentRule
#pragma region

/** Rules for attaching components - needs to be kept synced to EDetachmentRule */
UENUM(BlueprintType)
enum class ECsAttachmentRule : uint8
{
	/** Keeps current relative transform as the relative transform to the new parent. */
	KeepRelative	UMETA(DisplayName = "Keep Relative"),
	/** Automatically calculates the relative transform such that the attached component maintains the same world transform. */
	KeepWorld		UMETA(DisplayName = "Keep World"),
	/** Snaps transform to the attach point */
	SnapToTarget	UMETA(DisplayName = "Snap to Target"),
};

struct CSCORE_API EMCsAttachmentRule : public TCsEnumMap<ECsAttachmentRule>
{
	CS_ENUM_MAP_BODY(EMCsAttachmentRule, ECsAttachmentRule)
};

namespace NCsAttachmentRule
{
	typedef ECsAttachmentRule Type;

	namespace Ref
	{
		extern CSCORE_API const Type KeepRelative;
		extern CSCORE_API const Type KeepWorld;
		extern CSCORE_API const Type SnapToTarget;
	}

	FORCEINLINE EAttachmentRule ToRule(const Type& InType)
	{
		if (InType == Type::KeepRelative)
			return EAttachmentRule::KeepRelative;
		if (InType == Type::KeepWorld)
			return EAttachmentRule::KeepWorld;
		if (InType == Type::SnapToTarget)
			return EAttachmentRule::SnapToTarget;
		return EAttachmentRule::KeepRelative;
	}
}

#pragma endregion AttachmentRule

// FCsAttachmentTransformRules
#pragma region

/** 
* Rules for attaching components.
*/
USTRUCT(BlueprintType)
struct CSCORE_API FCsAttachmentTransformRules
{
	GENERATED_USTRUCT_BODY()

	/** Various preset attachment rules. Note that these default rules do NOT by default weld simulated bodies */
	static FCsAttachmentTransformRules KeepRelativeTransform;
	static FCsAttachmentTransformRules KeepWorldTransform;
	static FCsAttachmentTransformRules SnapToTargetNotIncludingScale;
	static FCsAttachmentTransformRules SnapToTargetIncludingScale;

	/** The rule to apply to location when attaching */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore")
	ECsAttachmentRule LocationRule;

	/** The rule to apply to rotation when attaching */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore")
	ECsAttachmentRule RotationRule;

	/** The rule to apply to scale when attaching */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore")
	ECsAttachmentRule ScaleRule;

	/** Whether to weld simulated bodies together when attaching */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CsCore")
	bool bWeldSimulatedBodies;

	FCsAttachmentTransformRules() :
		LocationRule(ECsAttachmentRule::KeepRelative),
		RotationRule(ECsAttachmentRule::KeepRelative),
		ScaleRule(ECsAttachmentRule::SnapToTarget),
		bWeldSimulatedBodies(false)
	{
	}

	FCsAttachmentTransformRules(const ECsAttachmentRule& InRule, const bool& bInWeldSimulatedBodies) : 
		LocationRule(InRule), 
		RotationRule(InRule), 
		ScaleRule(InRule), 
		bWeldSimulatedBodies(bInWeldSimulatedBodies)
	{
	}

	FCsAttachmentTransformRules(const ECsAttachmentRule& InLocationRule, const ECsAttachmentRule& InRotationRule, const ECsAttachmentRule& InScaleRule, const bool& bInWeldSimulatedBodies) : 
		LocationRule(InLocationRule), 
		RotationRule(InRotationRule), 
		ScaleRule(InScaleRule), 
		bWeldSimulatedBodies(bInWeldSimulatedBodies)
	{
	}

	FORCEINLINE operator FAttachmentTransformRules() const
	{
		return FAttachmentTransformRules(NCsAttachmentRule::ToRule(LocationRule), NCsAttachmentRule::ToRule(RotationRule), NCsAttachmentRule::ToRule(ScaleRule), bWeldSimulatedBodies);
	}

	FORCEINLINE bool operator==(const FCsAttachmentTransformRules& B) const
	{
		return LocationRule == B.LocationRule && RotationRule == B.RotationRule && ScaleRule == B.ScaleRule && bWeldSimulatedBodies ==B.bWeldSimulatedBodies;
	}

	FORCEINLINE bool operator!=(const FCsAttachmentTransformRules& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE bool operator==(const FAttachmentTransformRules& B) const
	{
		return LocationRule == (ECsAttachmentRule)B.LocationRule && RotationRule == (ECsAttachmentRule)B.RotationRule && ScaleRule == (ECsAttachmentRule)B.ScaleRule && bWeldSimulatedBodies == B.bWeldSimulatedBodies;
	}

	FORCEINLINE bool operator!=(const FAttachmentTransformRules& B) const
	{
		return !(*this == B);
	}

	FORCEINLINE FAttachmentTransformRules ToRule() const 
	{ 
		return FAttachmentTransformRules(NCsAttachmentRule::ToRule(LocationRule), NCsAttachmentRule::ToRule(RotationRule), NCsAttachmentRule::ToRule(ScaleRule), bWeldSimulatedBodies);
	}

	FORCEINLINE static bool IsEqual(const FAttachmentTransformRules& Lhs, const FAttachmentTransformRules& Rhs) 
	{
		return Lhs.LocationRule == Rhs.LocationRule && Lhs.RotationRule == Rhs.RotationRule && Lhs.ScaleRule == Rhs.ScaleRule && Lhs.bWeldSimulatedBodies == Rhs.bWeldSimulatedBodies;
	}
};

#pragma endregion FCsAttachmentTransformRules

// DetachmentTransformRules
#pragma region

UENUM(BlueprintType)
enum class ECsDetachmentTransformRules : uint8
{
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),
	ECsDetachmentTransformRules_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsDetachmentTransformRules : public TCsEnumMap<ECsDetachmentTransformRules>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsDetachmentTransformRules, ECsDetachmentTransformRules)
};

namespace NCsDetachmentTransformRules
{
	typedef ECsDetachmentTransformRules Type;

	namespace Ref
	{
		extern CSCORE_API const Type KeepRelativeTransform;
		extern CSCORE_API const Type KeepWorldTransform;
		extern CSCORE_API const Type ECsDetachmentTransformRules_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FDetachmentTransformRules& ToRule(const Type& EType)
	{
		if (EType == Type::KeepRelativeTransform) { return FDetachmentTransformRules::KeepRelativeTransform; }
		if (EType == Type::KeepWorldTransform) { return FDetachmentTransformRules::KeepWorldTransform; }
		return FDetachmentTransformRules::KeepRelativeTransform;
	}
}

#define ECS_DETACHMENT_TRANSFORM_RULES_MAX NCsDetachmentTransformRules::MAX

#pragma endregion DetachmentTransformRules