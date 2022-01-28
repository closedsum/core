// Copyright 2017-2022 Closed Sum Games, LLC. All Rights Reserved.
#pragma once
#include "Types/Enum/CsEnumMap.h"
#include "Engine/EngineTypes.h"

#include "CsTypes_AttachDetach.generated.h"

// AttachmentTransformRules
#pragma region

UENUM(BlueprintType)
enum class ECsAttachmentTransformRules : uint8
{
	KeepRelativeTransform			UMETA(DisplayName = "Keep Relative Transform"),
	KeepWorldTransform				UMETA(DisplayName = "Keep World Transform"),
	SnapToTargetNotIncludingScale	UMETA(DisplayName = "Snap To Target Not Including Scale"),
	SnapToTargetIncludingScale		UMETA(DisplayName = "Snap To Target Including Scale"),
	ECsAttachmentTransformRules_MAX	UMETA(Hidden),
};

struct CSCORE_API EMCsAttachmentTransformRules : public TCsEnumMap<ECsAttachmentTransformRules>
{
	CS_ENUM_MAP_BODY_WITH_EXPLICIT_MAX(EMCsAttachmentTransformRules, ECsAttachmentTransformRules)
};

namespace NCsAttachmentTransformRules
{
	typedef ECsAttachmentTransformRules Type;

	namespace Ref
	{
		extern CSCORE_API const Type KeepRelativeTransform;
		extern CSCORE_API const Type KeepWorldTransform;
		extern CSCORE_API const Type SnapToTargetNotIncludingScale;
		extern CSCORE_API const Type SnapToTargetIncludingScale;
		extern CSCORE_API const Type ECsAttachmentTransformRules_MAX;
	}

	extern CSCORE_API const uint8 MAX;

	FORCEINLINE const FAttachmentTransformRules& ToRule(const Type& EType)
	{
		if (EType == Type::KeepRelativeTransform) { return FAttachmentTransformRules::KeepRelativeTransform; }
		if (EType == Type::KeepWorldTransform) { return FAttachmentTransformRules::KeepWorldTransform; }
		if (EType == Type::SnapToTargetNotIncludingScale) { return FAttachmentTransformRules::SnapToTargetNotIncludingScale; }
		if (EType == Type::SnapToTargetIncludingScale) { return FAttachmentTransformRules::SnapToTargetIncludingScale; }
		return FAttachmentTransformRules::KeepRelativeTransform;
	}
}

#define ECS_ATTACHMENT_TRANSFORM_RULES_MAX NCsAttachmentTransformRules::MAX

#pragma endregion AttachmentTransformRules

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