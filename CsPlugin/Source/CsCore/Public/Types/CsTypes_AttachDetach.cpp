// Copyright 2017-2023 Closed Sum Games, LLC. All Rights Reserved.
#include "Types/CsTypes_AttachDetach.h"

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