// Copyright 2017-2024 Closed Sum Games, LLC. All Rights Reserved.
// MIT License: https://opensource.org/license/mit/
// Free for use and distribution: https://github.com/closedsum/core
#include "Types/CsTypes_AttachDetach.h"

// Library
#include "Library/CsLibrary_Valid.h"

// AttachmentRule
#pragma region

namespace NCsAttachmentRule
{
	namespace Ref
	{
		typedef EMCsAttachmentRule EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KeepRelative, "Keep Relative");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KeepWorld, "Keep World");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(SnapToTarget, "Snap to Target");
	}
}

#pragma endregion AttachmentRule

// AttachmentTransformRules
#pragma region

FCsAttachmentTransformRules FCsAttachmentTransformRules::KeepRelativeTransform(ECsAttachmentRule::KeepRelative, false);
FCsAttachmentTransformRules FCsAttachmentTransformRules::KeepWorldTransform(ECsAttachmentRule::KeepWorld, false);
FCsAttachmentTransformRules FCsAttachmentTransformRules::SnapToTargetNotIncludingScale(ECsAttachmentRule::SnapToTarget, ECsAttachmentRule::SnapToTarget, ECsAttachmentRule::KeepWorld, false);
FCsAttachmentTransformRules FCsAttachmentTransformRules::SnapToTargetIncludingScale(ECsAttachmentRule::SnapToTarget, false);

bool FCsAttachmentTransformRules::IsValidChecked(const FString& Context) const
{
	if (bAbsoluteLocation)
	{
		checkf(LocationRule == ECsAttachmentRule::KeepWorld, TEXT("%s: If bAbsoluteLocation == TRUE, then LocationRule MUST = ECsAttachmentRule::KeepWorld."), *Context);
	}

	if (bAbsoluteRotation)
	{
		checkf(RotationRule == ECsAttachmentRule::KeepWorld, TEXT("%s: If bAbsoluteRotation == TRUE, then RotationRule MUST = ECsAttachmentRule::KeepWorld."), *Context);
	}

	if (bAbsoluteScale)
	{
		checkf(ScaleRule == ECsAttachmentRule::KeepWorld, TEXT("%s: If bAbsoluteScale == TRUE, then ScaleRule MUST = ECsAttachmentRule::KeepWorld."), *Context);
	}
	return true;
}

bool FCsAttachmentTransformRules::IsValid(const FString& Context, void(*Log)(const FString&) /*=&FCsLog::Warning*/) const
{
	if (bAbsoluteLocation)
	{
		if (LocationRule != ECsAttachmentRule::KeepWorld)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If bAbsoluteLocation == TRUE, then LocationRule MUST = ECsAttachmentRule::KeepWorld."), *Context));
			return false;
		}
	}

	if (bAbsoluteRotation)
	{
		if (RotationRule != ECsAttachmentRule::KeepWorld)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If bAbsoluteRotation == TRUE, then RotationRule MUST = ECsAttachmentRule::KeepWorld."), *Context));
			return false;
		}
	}

	if (bAbsoluteScale)
	{
		if (ScaleRule != ECsAttachmentRule::KeepWorld)
		{
			CS_CONDITIONAL_LOG(FString::Printf(TEXT("%s: If bAbsoluteScale == TRUE, then ScaleRule MUST = ECsAttachmentRule::KeepWorld."), *Context));
			return false;
		}
	}
	return true;
}

#pragma endregion AttachmentTransformRules

// DetachmentTransformRules
#pragma region

namespace NCsDetachmentTransformRules
{
	namespace Ref
	{
		typedef EMCsDetachmentTransformRules EnumMapType;

		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KeepRelativeTransform, "Keep Relative Transform");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(KeepWorldTransform, "Keep World Transform");
		CSCORE_API CS_ADD_TO_ENUM_MAP_CUSTOM(ECsDetachmentTransformRules_MAX, "MAX");
	}

	CSCORE_API const uint8 MAX = (uint8)Type::ECsDetachmentTransformRules_MAX;
}

#pragma endregion DetachmentTransformRules